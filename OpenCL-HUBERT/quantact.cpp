//quantact.cpp, created by Hunter Messner for the HUBERT project

#include "HLS/hls.h"
#include "HLS/stdio.h"
#include "tensors.h" 
#include <iostream>
#include "quantact.h"
#include "hubertEnums.h"
#include "constant_headers/qa_pasf_softmax.h"
#include "constant_headers/qa_x_softmax.h"

//TEMPORARY DEFINES. Eventually move these to a higher level and pass them in through function parameters
#define CHANNEL_LEN 1
const int x_minr = 1;
const int x_minc = CHANNEL_LEN;

const int x_maxr = 1;
const int x_maxc = CHANNEL_LEN;

const int asfr = 1;
const int asfc = CHANNEL_LEN;

QuantAct::QuantAct(
	int activation_bit_i, 
    float act_range_momentum_i,
    bool running_stat_i,
    bool per_channel_i,
    int channel_len,
    QuantMode quant_mode_i)
{
    activation_bit = activation_bit_i;
    act_range_momentum= act_range_momentum_i;
    running_stat = running_stat_i;
    quant_mode = quant_mode_i;
    per_channel = per_channel_i;

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

scaled_tuple3d QuantAct::QuantAct_forward(
	QuantAct& self,
	Tensor3d x, const int xr, const int xc, const int xd,//identity and x are 22x1x768 or 12x22x22.
	Tensor pre_act_scaling_factor, const int pasfr, const int pasfc,
	Tensor3d identity, const int identityr, const int identityc, const int identityd,
	Tensor identity_scaling_factor, const int isfr, const int isfc,
	Tensor specified_min,
	Tensor specified_max)
{
	copy(x, xr, xc, xd, self.memory.x_act);
	eq(x, xr, xc, xd, (const Tensor3d)qa_x_softmax, xr, xc, xd);
	if (!(identity == nullptr))
	{
		add(x, xr, xc, xd, identity, identityr, identityc, identityd, self.memory.x_act);
	}

	float local_xmin[] = { 0.f };
	float local_xmax[] = { 0.f };

	if (self.running_stat)
	{
		if (!self.per_channel)
		{
			copy(self.memory.x_act, xr, xc, xd, self.memory.temp);
			min(self.memory.temp, xr, xc, xd, self.memory.temp);
			toTwoD(self.memory.temp, xr, xc, xd, local_xmin);

			copy(self.memory.x_act, xr, xc, xd, self.memory.temp);
			max(self.memory.temp, xr, xc, xd, self.memory.temp);
			toTwoD(self.memory.temp, xr, xc, xd, local_xmax);
		}
		else
		{
			//assert(false);
		}

		//Initialization 
		if (eq(self.memory.x_min, x_minr, x_minc, self.memory.x_max, x_maxr, x_maxc))
		{
			add(self.memory.x_min, x_minr, x_minc, local_xmin, 1, 1, self.memory.x_min);
			add(self.memory.x_max, x_maxr, x_maxc, local_xmax, 1, 1, self.memory.x_max);
		}
		else if (self.act_range_momentum == -1)
		{
			float obj_min = self.memory.x_min[0];
			float obj_max = self.memory.x_max[0];
			float localmin = local_xmin[0];
			float localmax = local_xmax[0];

			if (localmax > obj_max)
			{
				set(self.memory.x_max, x_maxr, x_maxc, 0, 0, localmax);
			}
			if (localmin < obj_min)
			{
				set(self.memory.x_min, x_minr, x_minc, 0, 0, localmin);
			}
		}
		else
		{
			//here I am assuming xmin and xmax are 1x1
			float objmin = self.memory.x_min[0];
			float localmin = local_xmin[0];
			set(self.memory.x_min, x_minr, x_minc, 0, 0, objmin*self.act_range_momentum + localmin * (1 - self.act_range_momentum));

			float objmax = self.memory.x_max[0];
			float localmax = local_xmax[0];
			set(self.memory.x_max, x_maxr, x_maxc, 0, 0, objmax*self.act_range_momentum + localmax * (1 - self.act_range_momentum));
		}
	}

	if (self.quant_mode == QuantMode::none)
	{
		scaled_tuple3d returnme;
		returnme.matrix = self.memory.x_act;
		returnme.scaling_factor = nullptr;
		return returnme;
	}

	if (specified_min != nullptr)
		self.memory.x_min = specified_min;
	if (specified_max != nullptr)
		self.memory.x_min = specified_max;

	self.memory.act_scaling_factor = QuantAct::symmetric_linear_quantization_params(self, self.activation_bit, self.memory.x_min, x_minr, x_minc, self.memory.x_max, self.per_channel);

	Tensor3d quant_act_int = nullptr; //TODO: size? I dont think i have to allocate this
	if (pre_act_scaling_factor == nullptr)
	{
		quant_act_int = QuantAct::symmetric_quant_forward(self, x, xr, xc, xd, self.activation_bit, self.memory.act_scaling_factor, asfr, asfc); //returns a modified x
	}
	else
	{
		quant_act_int = fixedpoint_mul(
			self,
			x, xr, xc, xd, 
			pre_act_scaling_factor, pasfr, pasfc, 
			self.activation_bit, 
			self.quant_mode, 
			self.memory.act_scaling_factor, asfr, asfc,
			identity, identityr, identityc, identityd, 
			identity_scaling_factor, isfr, isfc);
	}

	float space[] = { 0.f };
	float correct_output_scale[] = { self.memory.act_scaling_factor[0] };
	//correct output scale has just one element while quant act int has 2
    mul_scalar(quant_act_int, xr, xc, xd, correct_output_scale[0], quant_act_int);
    scaled_tuple3d returnme;
    returnme.matrix = quant_act_int;
    returnme.scaling_factor = self.memory.act_scaling_factor;
    return returnme;
}

Tensor QuantAct::symmetric_linear_quantization_params(
	QuantAct &self,
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
    fill(self.memory.slqp_scale, smr, smc, 0.0f);
    unsigned n =  (unsigned int)exp2( num_bits - 1 ) - 1;
    if (per_channel)
    { // saturation min and max are columns
		for (unsigned i = 0; i < smc; i++)
		{//custom max loop
			float x = fabs(get(saturation_min, smr, smc, 0, i)); 
			float y = fabs(get(saturation_max, smr, smc, 0, i));
			if (x > y)
			{
				set(self.memory.slqp_scale, smr, smc, 0, i, x);
			}
			else
			{
				set(self.memory.slqp_scale, smr, smc, 0, i, y);
			}
		}
		clamp(self.memory.slqp_scale, smr, smc, 1e-8f, FLT_MAX, self.memory.slqp_scale);
		div_scalar(self.memory.slqp_scale, smr, smc, (float)n, self.memory.slqp_scale);
    }
    else
    {//saturation min and max are one element tensors
        set(self.memory.slqp_scale, smr, smc, 0,0, fmax(fabs(saturation_min[0]), fabs(saturation_max[0])));
        clamp(self.memory.slqp_scale, smr, smc, 1e-8f, FLT_MAX, self.memory.slqp_scale);
        div_scalar(self.memory.slqp_scale, smr, smc, (float)n, self.memory.slqp_scale);
    }
    return self.memory.slqp_scale;
}

Tensor3d QuantAct::symmetric_quant_forward(QuantAct &self, Tensor3d x, const int xr, const int xc, const int xd, int k, Tensor specified_scale, const int ssr, const int ssc)
{
    if(specified_scale != nullptr)
    {
        copy(specified_scale,ssr,ssc, self.memory.sqf_scale);
    }
	float zero_point[] = { 0.f };
    float n = exp2f(float(k - 1)) - 1;

    Tensor3d new_quant_x = QuantAct::linear_quantize(self, x, xr, xc, xd, self.memory.sqf_scale, ssr, ssc, zero_point, 1, 1);
    clamp(new_quant_x, xr, xc, xd, -n, n-1, new_quant_x);
    return new_quant_x;
}

Tensor3d QuantAct::linear_quantize(QuantAct &self, Tensor3d x, const int xr, const int xc, const int xd, Tensor scale_c, const int sr, const int sc, Tensor zero_point, const int zr, const int zc)
{
    //scale is 1 when x is truely 3d. When x is 2d, scale is also 2d (or at least broadcastable.)
	copy(scale_c, sr, sc, self.memory.lq_scale);
    reciprocal(self.memory.lq_scale, sr, sc, self.memory.lq_scale);
	if (xd != 1)
	{
		mul_scalar(x, xr, xc, xd, self.memory.lq_scale[0], x);
	}
	else
	{
		mul_dot(x, xr, xc, xd, self.memory.lq_scale, sr, sc, x);
	}
    add_scalar(x, xr, xc, xd, zero_point[0], x);
    roundTensor(x, xr, xc, xd, x);
    return x;
}

Tensor3d QuantAct::fixedpoint_mul(
	QuantAct &self,
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

    copy(pre_act, par, pac, pad, self.memory.z_int);
    div_dot(pre_act, par, pac, pad, pre_act_scaling_factor, pasfr, pasfc, self.memory.z_int);
    roundTensor(self.memory.z_int, par, pac, pad, self.memory.z_int);

    //the following is in double precision in the code, but I did not make it double precision here
	copy(pre_act_scaling_factor, pasfr, pasfc, self.memory._A);
	copy(z_scaling_factor, zsfr, zsfc, self.memory._B);
	copy(self.memory._A, pasfr, pasfc, self.memory.new_scale);// this copy is not necessary but gives context to the size of new_scale
	div_dot(self.memory._A, pasfr, pasfc, self.memory._B, zsfr, zsfc, self.memory.new_scale);
    
	copy(self.memory.new_scale, pasfr, pasfc, self.memory.m);
	copy(self.memory.new_scale, pasfr, pasfc, self.memory.e);
	tensor_frexp(self.memory.new_scale, pasfr, pasfc, self.memory.m, pasfr, pasfc, self.memory.e, pasfr, pasfc);
    copy(self.memory.z_int, zsfr, zsfc, self.memory.output);

	fill(self.memory.twos, zsfr, zsfc, 2.0f);
	pow_dot(self.memory.twos, zsfr, zsfc, self.memory.e, pasfr, pasfc, self.memory.twos); //use twos as temp storage
	div_dot(self.memory.output, zsfr, zsfc, self.memory.twos, zsfr, zsfc, self.memory.output);
	mul_dot(self.memory.output, zsfr, zsfc, self.memory.m, pasfr, pasfc, self.memory.output);
    roundTensor(self.memory.output, zsfr, zsfc, self.memory.output);

    if(identity != nullptr)
	{
        copy(identity, identityr, identityc, identityd, self.memory.wx_int); //also an unnecessary
		div_dot(identity, identityr, identityc, identityd, identity_scaling_factor, isfr, isfc, identity);
        roundTensor(identity, identityr, identityc, identityd, self.memory.wx_int);

        copy(identity_scaling_factor, isfr, isfc, self.memory._A1); //_A is also the size of the isf 
        copy(z_scaling_factor, zsfr, zsfc, self.memory._B1);
		copy(self.memory._A1, isfr, isfc, self.memory.new_scale1);
        div_dot(self.memory._A1, isfr, isfc, self.memory._B1, zsfr, zsfc, self.memory.new_scale1);

        copy(self.memory.new_scale1, isfr, isfc, self.memory.m1);
        copy(self.memory.new_scale1, isfr, isfc, self.memory.e1);
        tensor_frexp(self.memory.new_scale1, isfr, isfc, self.memory.m1, isfr, isfc, self.memory.e1, isfr, isfc);

        copy(self.memory.wx_int, identityr, identityc, identityd, self.memory.output1);
		mul_dot(self.memory.wx_int, identityr, identityc, identityd, self.memory.m1, isfr, isfc, self.memory.output1);

        pow_dot(self.memory.twos, isfr, isfc, self.memory.e1, isfr, isfc, self.memory.e1); //use e1 as temp storage TODO: what is going on here?
		div_dot(self.memory.output1, identityr, identityc, identityd, self.memory.e1, isfr, isfc, self.memory.output1); //Can I really use e1 as temp storage?
        roundTensor(self.memory.output1, identityr, identityc, identityd, self.memory.output1);

        add(self.memory.output, zsfr, zsfc, self.memory.output1, identityr, identityc, self.memory.output); //TODO: also have no idea what is going on here? assuming 2d...
    }

    if( bit_num == 4 || bit_num == 8 || bit_num == 16)
    {
        if(quant_mode == QuantMode::symmetric)
        {
            clamp(self.memory.output, zsfr, zsfc, -n-1, n, self.memory.output);
            return self.memory.output;
        }
        else{
            clamp(self.memory.output, zsfr, zsfc, 0, n, self.memory.output);
            return self.memory.output;
        }
    }
    else{
        return self.memory.output;
    }
}


void QuantAct::set_param(
	QuantAct &self, 
	quantact_memory memory
	)
{
	//In this function, I want a pointer to all of these pre allocated arrays and assign them to member variables. These will all be empty
	//additionally I want a pointer to the "preload" arrays (weights and biases learned from the python model)
	self.memory = memory;
}

