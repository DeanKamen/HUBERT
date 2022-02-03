//softmax.cpp, created by Hunter Messner for the HUBERT project
#include "HLS/hls.h"
#include "HLS/stdio.h"
#include "tensors.h" 
#include <iostream>
#include "quantact.h"
#include "hubertEnums.h"
#include "softmax.h"
#include "HLS/math.h"
#include <limits.h>
#include <float.h>

//verification
#include "constant_headers/softmax_layer0_out.h"

void Softmax(softmax_memory& memory, quantact_memory& qa_memory, int output_bit_i, QuantMode quant_mode_i, ForceDequantMode force_dequant)
{
	memory.output_bit = output_bit_i;
	memory.quant_mode = quant_mode_i;
	qa_memory.quant_mode = quant_mode_i;
	QuantAct(qa_memory, 16, 0.95f, true, false, -1, quant_mode_i);
	if (force_dequant == ForceDequantMode::nonlinear || force_dequant == ForceDequantMode::softmax)
	{
		memory.quant_mode = QuantMode::none;
	}
	memory.x0 = -0.6931f; //  - ln2
	memory.n = 30; // sufficiently large integer
	memory.coef[0] =  0.35815147f;
	memory.coef[1] = 0.96963238f;
	memory.coef[2] = 1.f; // ax**2 + bx + c
	memory.coef[1] /= memory.coef[0];
	memory.coef[2] /= memory.coef[0];
}

scaled_tuple3d int_polynomial(softmax_memory& memory, Tensor3d x_int, const int xr, const int xc, const int xd, Tensor scaling_factor, const int sfr, const int sfc)
{
	reciprocal(scaling_factor, sfr, sfc, memory.b_int);
	mul_scalar(memory.b_int, sfr, sfc, memory.coef[1], memory.b_int);
	floor_tensor(memory.b_int, sfr, sfc, memory.b_int);

	pow_scalar(scaling_factor, sfr, sfc, 2.f, memory.c_int); 
	reciprocal(memory.c_int, sfr, sfc, memory.c_int);
	mul_scalar(memory.c_int, sfr, sfc, memory.coef[2], memory.c_int);
	floor_tensor(memory.c_int, sfr, sfc, memory.c_int);

	add_scalar(x_int, xr, xc, xd, memory.b_int[0], memory.z);
	mul_dot(x_int, xr, xc, xd, memory.z, xr, xc, xd, memory.z);
	add_scalar(memory.z, xr, xc, xd, memory.c_int[0], memory.z);

	pow_scalar(scaling_factor, sfr, sfc, 2, scaling_factor);
	mul_scalar(scaling_factor, sfr, sfc, memory.coef[0], scaling_factor);
	
	scaled_tuple3d returnme;
	returnme.matrix = memory.z;
	returnme.scaling_factor = scaling_factor;
	return returnme;
}

scaled_tuple3d int_exp(softmax_memory& memory, Tensor3d x_int, const int xr, const int xc, const int xd, Tensor scaling_factor, const int sfr, const int sfc)
{
	copy(scaling_factor, sfr, sfc, memory.x0_int);
	reciprocal(scaling_factor, sfr, sfc, memory.x0_int); //makes previous line unnecessary
	mul_scalar(memory.x0_int, sfr, sfc, memory.x0, memory.x0_int);
	floor_tensor(memory.x0_int, sfr, sfc, memory.x0_int);

	copy(memory.x0_int, sfr, sfc, memory.temp);
	mul_scalar(memory.temp, sfr, sfc, (float)memory.n, memory.temp);
	max_scalar(x_int, xr, xc, xd, memory.temp[0], x_int);

	copy(x_int,xr,xc,xd, memory.q);
	div_scalar(memory.q, xr, xc, xd, memory.x0_int[0], memory.q);
	floor_tensor(memory.q, xr, xc, xd, memory.q);

	copy(x_int, xr, xc, xd, memory.r);
	copy(memory.q,xr,xc,xd, memory.temp2);
	mul_scalar(memory.temp2, xr, xc, xd, memory.x0_int[0], memory.temp2);
	sub(x_int, xr, xc, xd, memory.temp2, xr, xc, xd, memory.r);
	scaled_tuple3d exp = int_polynomial(memory, memory.r, xr, xc, xd, scaling_factor, sfr, sfc); //returns a scaled tuple with the size of the first tensor
	sub_scalar((float)memory.n, memory.q, xr, xc, xd, memory.q);
	exp2_tensor(memory.q, xr, xc, xd, memory.q);

	mul_dot(exp.matrix, xr, xc, xd, memory.q, xr, xc, xd, exp.matrix);
	
	floor_tensor(exp.matrix, xr, xc, xd, exp.matrix);
	clamp(exp.matrix, xr, xc, xd, 0.f, FLT_MAX, exp.matrix);

	float x = (float)exp2(memory.n);
	div_scalar(exp.scaling_factor, xr, xc, xd, x, exp.scaling_factor);
	
	return exp;
}


component scaled_tuple3d softmax_forward(softmax_memory& memory, quantact_memory& qa_memory, Tensor3d x, const int xr, const int xc, const int xd, Tensor scaling_factor, const int sfr, const int sfc)
{
	//ASSUMPTION x is 12x22x22, scaling factor is 1x1
	copy(x, xr, xc, xd, memory.x_int);
	if (memory.quant_mode == QuantMode::none)
	{
		normal_softmax(memory, memory.x_int, xr, xc, xd, memory.x_int, xr, xc, xd);
		scaled_tuple3d rm;
		rm.matrix = memory.x_int;
		rm.scaling_factor = nullptr;
		return rm;
	}
	//symmetric mode below
	div_scalar(memory.x_int, xr, xc, xd, scaling_factor[0], memory.x_int);
	max(memory.x_int, xr, xc, xd, 1, memory.x_int_max);
	sub(memory.x_int, xr, xc, xd, memory.x_int_max, xr, 1, xd, memory.x_int);
	scaled_tuple3d exp = int_exp(memory, memory.x_int, xr, xc, xd, scaling_factor, sfr, sfc);
	exp = QuantAct_forward(qa_memory, exp.matrix, xr, xc, xd, exp.scaling_factor, sfr, sfc, nullptr, 0, 0, 0, nullptr, 0,0, nullptr, nullptr);
	copy(exp.matrix, xr, xc, xd, memory.exp_int);
	div_scalar(exp.matrix, xr, xc, xd, exp.scaling_factor[0], memory.exp_int);
	copy(memory.exp_int, xr, xc, xd, memory.exp_int_sum);
	sum(memory.exp_int, xr, xc, xd, 1, memory.exp_int_sum); 

	reciprocal(memory.exp_int_sum, xr, 1, xd, memory.factor); //columns is 1 because the sum operation before collapsed all columns
	mul_scalar(memory.factor, xr, 1, xd, exp2f(32), memory.factor);
	floor_tensor(memory.factor, xr, 1, xd, memory.factor);
	mul_dot(memory.exp_int, xr, xc, xd, memory.factor, xr, 1, xd, memory.exp_int);
	div_scalar(memory.exp_int, xr, xc, xd, exp2f(float(32-memory.output_bit)), memory.exp_int);
	floor_tensor(memory.exp_int, xr, xc, xd, memory.exp_int);

	scaled_tuple3d returnme;
	returnme.matrix = memory.exp_int;
	float sf = 1.f / exp2f((float)memory.output_bit);
	mul_scalar(returnme.matrix, xr, xc, xd, sf, returnme.matrix);
	memory.scaling_return[0] = sf;
	returnme.scaling_factor = memory.scaling_return;

	//eq(returnme.matrix, xr, xc, xd, (const Tensor3d)softmax_layer0_out, xr, xc, xd);//verification

	return returnme;
}

void normal_softmax(softmax_memory& memory, Tensor3d src, const int srcr, const int srcc, const int srcd, Tensor3d dest, const int destr, const int destc, const int destd)
{//according to https ://pytorch.org/docs/stable/generated/torch.nn.Softmax.html?highlight=softmax#torch.nn.Softmax
 // dimention is curretly locked to 1, regarding each row as a unit to perform softmax on.
	//NOT VERIFIED BTW, not used in testing either
	int i, j, d;
	for (d = 0; d < srcr; d++)
	{
		for (i = 0; i < srcr; i++)
		{
			//do a softmax on every row.
			float sum = 0;
			for (j = 0; j < srcc; j++)
			{
				sum += exp(get(src, srcr, srcc, srcd, i, j, d));
			}

			for (j = 0; j < srcc; j++)
			{
				float el = get(src, srcr, srcc, srcd, i, j, d);
				el = exp(el) / sum;
				set(dest, destr, destc, destd, i, j, d, el); //copy to local tensor space
			}
		}
	}
}

