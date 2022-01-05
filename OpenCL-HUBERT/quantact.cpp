//quantact.cpp, created by Hunter Messner for the HUBERT project

#include "HLS/hls.h"
#include "HLS/stdio.h"
#include "HLS/math.h"
#include "tensors.h" 
#include <iostream>
#include "quantact.h"
#include "hubertEnums.h"
#include "constant_headers/qa_pasf_softmax.h"
#include "constant_headers/qa_x_softmax.h"
#include <limits.h>
#include <float.h>

//TEMPORARY DEFINES. Eventually move these to a higher level and pass them in through function parameters
#define CHANNEL_LEN 1
const int x_minr = 1;
const int x_minc = CHANNEL_LEN;

const int x_maxr = 1;
const int x_maxc = CHANNEL_LEN;

const int asfr = 1;
const int asfc = CHANNEL_LEN;

void QuantAct(
	quantact_memory memory,
	int activation_bit_i, 
    float act_range_momentum_i,
    bool running_stat_i,
    bool per_channel_i,
    int channel_len,
    QuantMode quant_mode_i)
{
    memory.activation_bit = activation_bit_i;
	memory.act_range_momentum= act_range_momentum_i;
	memory.running_stat = running_stat_i;
	memory.quant_mode = quant_mode_i;
	memory.per_channel = per_channel_i;

	/*
    if(per_channel)
    {
		assert(channel_len > 0);
		fill(x_min, x_minr, x_minc, 0.0f);
		fill(x_max, x_maxr, x_maxc, 0.0f);
		fill(act_scaling_factor, asfr, asfc, 0.0f);
    }
	*/
	//loading xmin and xmax is done by the set param function
}

component scaled_tuple3d QuantAct_forward(
	quantact_memory memory,
	Tensor3d x, const int xr, const int xc, const int xd,//identity and x are 22x1x768 or 12x22x22.
	Tensor pre_act_scaling_factor, const int pasfr, const int pasfc,
	Tensor3d identity, const int identityr, const int identityc, const int identityd,
	Tensor identity_scaling_factor, const int isfr, const int isfc,
	Tensor specified_min,
	Tensor specified_max)
{
	copy(x, xr, xc, xd, memory.x_act);
	eq(x, xr, xc, xd, (const Tensor3d)qa_x_softmax, xr, xc, xd);
	if (!(identity == nullptr))
	{
		add(x, xr, xc, xd, identity, identityr, identityc, identityd, memory.x_act);
	}

	float local_xmin[] = { 0.f };
	float local_xmax[] = { 0.f };

	if (memory.running_stat)
	{
		if (!memory.per_channel)
		{
			copy(memory.x_act, xr, xc, xd, memory.temp);
			min(memory.temp, xr, xc, xd, memory.temp);
			toTwoD(memory.temp, xr, xc, xd, local_xmin);

			copy(memory.x_act, xr, xc, xd, memory.temp);
			max(memory.temp, xr, xc, xd, memory.temp);
			toTwoD(memory.temp, xr, xc, xd, local_xmax);
		}
		else
		{
			//assert(false);
		}

		//Initialization 
		if (eq(memory.x_min, x_minr, x_minc, memory.x_max, x_maxr, x_maxc))
		{
			add(memory.x_min, x_minr, x_minc, local_xmin, 1, 1, memory.x_min);
			add(memory.x_max, x_maxr, x_maxc, local_xmax, 1, 1, memory.x_max);
		}
		else if (memory.act_range_momentum == -1)
		{
			float obj_min = memory.x_min[0];
			float obj_max = memory.x_max[0];
			float localmin = local_xmin[0];
			float localmax = local_xmax[0];

			if (localmax > obj_max)
			{
				set(memory.x_max, x_maxr, x_maxc, 0, 0, localmax);
			}
			if (localmin < obj_min)
			{
				set(memory.x_min, x_minr, x_minc, 0, 0, localmin);
			}
		}
		else
		{
			//here I am assuming xmin and xmax are 1x1
			float objmin = memory.x_min[0];
			float localmin = local_xmin[0];
			set(memory.x_min, x_minr, x_minc, 0, 0, objmin*memory.act_range_momentum + localmin * (1 - memory.act_range_momentum));

			float objmax = memory.x_max[0];
			float localmax = local_xmax[0];
			set(memory.x_max, x_maxr, x_maxc, 0, 0, objmax*memory.act_range_momentum + localmax * (1 - memory.act_range_momentum));
		}
	}

	if (memory.quant_mode == QuantMode::none)
	{
		scaled_tuple3d returnme;
		returnme.matrix = memory.x_act;
		returnme.scaling_factor = nullptr;
		return returnme;
	}

	if (specified_min != nullptr)
		memory.x_min = specified_min;
	if (specified_max != nullptr)
		memory.x_min = specified_max;

	memory.act_scaling_factor = symmetric_linear_quantization_params(memory, memory.activation_bit, memory.x_min, x_minr, x_minc, memory.x_max, memory.per_channel);

	Tensor3d quant_act_int = nullptr; //TODO: size? I dont think i have to allocate this
	if (pre_act_scaling_factor == nullptr)
	{
		quant_act_int = symmetric_quant_forward(memory, x, xr, xc, xd, memory.activation_bit, memory.act_scaling_factor, asfr, asfc); //returns a modified x
	}
	else
	{
		quant_act_int = fixedpoint_mul(
			memory,
			x, xr, xc, xd, 
			pre_act_scaling_factor, pasfr, pasfc, 
			memory.activation_bit, 
			memory.quant_mode, 
			memory.act_scaling_factor, asfr, asfc,
			identity, identityr, identityc, identityd, 
			identity_scaling_factor, isfr, isfc);
	}

	float space[] = { 0.f };
	float correct_output_scale[] = { memory.act_scaling_factor[0] };
	//correct output scale has just one element while quant act int has 2
    mul_scalar(quant_act_int, xr, xc, xd, correct_output_scale[0], quant_act_int);
    scaled_tuple3d returnme;
    returnme.matrix = quant_act_int;
    returnme.scaling_factor = memory.act_scaling_factor;
    return returnme;
}

Tensor symmetric_linear_quantization_params(
	quantact_memory memory,
	unsigned num_bits,
    Tensor saturation_min,
	const int smr,
	const int smc,
    Tensor saturation_max,
    bool per_channel)
{
    /*
    Compute the scaling factor with the given quantization range for symmetric quantization.

    Parameters:
    ----------
    saturation_min: lower bound for quantization range
    saturation_max: upper bound for quantization range
    
    */
    fill(memory.slqp_scale, smr, smc, 0.0f);
    unsigned n =  (unsigned int)exp2( num_bits - 1 ) - 1;
    if (per_channel)
    { // saturation min and max are columns
		for (int i = 0; i < smc; i++)
		{//custom max loop
			float x = fabs(get(saturation_min, smr, smc, 0, i)); 
			float y = fabs(get(saturation_max, smr, smc, 0, i));
			if (x > y)
			{
				set(memory.slqp_scale, smr, smc, 0, i, x);
			}
			else
			{
				set(memory.slqp_scale, smr, smc, 0, i, y);
			}
		}
		clamp(memory.slqp_scale, smr, smc, 1e-8f, FLT_MAX, memory.slqp_scale);
		div_scalar(memory.slqp_scale, smr, smc, (float)n, memory.slqp_scale);
    }
    else
    {//saturation min and max are one element tensors
        set(memory.slqp_scale, smr, smc, 0,0, fmax(fabs(saturation_min[0]), fabs(saturation_max[0])));
        clamp(memory.slqp_scale, smr, smc, 1e-8f, FLT_MAX, memory.slqp_scale);
        div_scalar(memory.slqp_scale, smr, smc, (float)n, memory.slqp_scale);
    }
    return memory.slqp_scale;
}

Tensor3d symmetric_quant_forward(quantact_memory memory, Tensor3d x, const int xr, const int xc, const int xd, int k, Tensor specified_scale, const int ssr, const int ssc)
{
    if(specified_scale != nullptr)
    {
        copy(specified_scale,ssr,ssc, memory.sqf_scale);
    }
	float zero_point[] = { 0.f };
    float n = exp2f(float(k - 1)) - 1;

    Tensor3d new_quant_x = linear_quantize(memory, x, xr, xc, xd, memory.sqf_scale, ssr, ssc, zero_point, 1, 1);
    clamp(new_quant_x, xr, xc, xd, -n, n-1, new_quant_x);
    return new_quant_x;
}

Tensor3d linear_quantize(quantact_memory memory, Tensor3d x, const int xr, const int xc, const int xd, Tensor scale_c, const int sr, const int sc, Tensor zero_point, const int zr, const int zc)
{
    //scale is 1 when x is truely 3d. When x is 2d, scale is also 2d (or at least broadcastable.)
	copy(scale_c, sr, sc, memory.lq_scale);
    reciprocal(memory.lq_scale, sr, sc, memory.lq_scale);
	if (xd != 1)
	{
		mul_scalar(x, xr, xc, xd, memory.lq_scale[0], x);
	}
	else
	{
		mul_dot(x, xr, xc, xd, memory.lq_scale, sr, sc, x);
	}
    add_scalar(x, xr, xc, xd, zero_point[0], x);
    roundTensor(x, xr, xc, xd, x);
    return x;
}

Tensor3d fixedpoint_mul(
	quantact_memory memory,
    Tensor3d pre_act, const int par, const int pac, const int pad,
    Tensor pre_act_scaling_factor, const int pasfr, const int pasfc,
    int bit_num,
    QuantMode quant_mode,
    Tensor z_scaling_factor, const int zsfr, const int zsfc,	
    Tensor3d identity, const int identityr, const int identityc, const int identityd,
    Tensor identity_scaling_factor, const int isfr, const int isfc
    )
{
    float n ;
    if (quant_mode == QuantMode::symmetric)
    {
        n = (float)exp2(bit_num - 1) -1;
    }
    else{
        n = (float)exp2(bit_num) - 1;
    }
	float space[] = { 0.f };

    copy(pre_act, par, pac, pad, memory.z_int);
    div_dot(pre_act, par, pac, pad, pre_act_scaling_factor, pasfr, pasfc, memory.z_int);
    roundTensor(memory.z_int, par, pac, pad, memory.z_int);

    //the following is in double precision in the code, but I did not make it double precision here
	copy(pre_act_scaling_factor, pasfr, pasfc, memory._A);
	copy(z_scaling_factor, zsfr, zsfc, memory._B);
	copy(memory._A, pasfr, pasfc, memory.new_scale);// this copy is not necessary but gives context to the size of new_scale
	div_dot(memory._A, pasfr, pasfc, memory._B, zsfr, zsfc, memory.new_scale);
    
	copy(memory.new_scale, pasfr, pasfc, memory.m);
	copy(memory.new_scale, pasfr, pasfc, memory.e);
	tensor_frexp(memory.new_scale, pasfr, pasfc, memory.m, pasfr, pasfc, memory.e, pasfr, pasfc);
    copy(memory.z_int, zsfr, zsfc, memory.output);

	fill(memory.twos, zsfr, zsfc, 2.0f);
	pow_dot(memory.twos, zsfr, zsfc, memory.e, pasfr, pasfc, memory.twos); //use twos as temp storage
	div_dot(memory.output, zsfr, zsfc, memory.twos, zsfr, zsfc, memory.output);
	mul_dot(memory.output, zsfr, zsfc, memory.m, pasfr, pasfc, memory.output);
    roundTensor(memory.output, zsfr, zsfc, memory.output);

    if(identity != nullptr)
	{
        copy(identity, identityr, identityc, identityd, memory.wx_int); //also an unnecessary
		div_dot(identity, identityr, identityc, identityd, identity_scaling_factor, isfr, isfc, identity);
        roundTensor(identity, identityr, identityc, identityd, memory.wx_int);

        copy(identity_scaling_factor, isfr, isfc, memory._A1); //_A is also the size of the isf 
        copy(z_scaling_factor, zsfr, zsfc, memory._B1);
		copy(memory._A1, isfr, isfc, memory.new_scale1);
        div_dot(memory._A1, isfr, isfc, memory._B1, zsfr, zsfc, memory.new_scale1);

        copy(memory.new_scale1, isfr, isfc, memory.m1);
        copy(memory.new_scale1, isfr, isfc, memory.e1);
        tensor_frexp(memory.new_scale1, isfr, isfc, memory.m1, isfr, isfc, memory.e1, isfr, isfc);

        copy(memory.wx_int, identityr, identityc, identityd, memory.output1);
		mul_dot(memory.wx_int, identityr, identityc, identityd, memory.m1, isfr, isfc, memory.output1);

        pow_dot(memory.twos, isfr, isfc, memory.e1, isfr, isfc, memory.e1); //use e1 as temp storage TODO: what is going on here?
		div_dot(memory.output1, identityr, identityc, identityd, memory.e1, isfr, isfc, memory.output1); //Can I really use e1 as temp storage?
        roundTensor(memory.output1, identityr, identityc, identityd, memory.output1);

        add(memory.output, zsfr, zsfc, memory.output1, identityr, identityc, memory.output); //TODO: also have no idea what is going on here? assuming 2d...
    }

    if( bit_num == 4 || bit_num == 8 || bit_num == 16)
    {
        if(quant_mode == QuantMode::symmetric)
        {
            clamp(memory.output, zsfr, zsfc, -n-1, n, memory.output);
            return memory.output;
        }
        else{
            clamp(memory.output, zsfr, zsfc, 0, n, memory.output);
            return memory.output;
        }
    }
    else{
        return memory.output;
    }
}
