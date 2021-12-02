//softmax.cpp, created by Hunter Messner for the HUBERT project
#include "HLS/hls.h"
#include "HLS/stdio.h"
#include "tensors.h" 
#include <iostream>
#include "quantact.h"
#include "hubertEnums.h"
#include "softmax.h"

//verification
#include "constant_headers/softmax_b4_int_exp.h"

QuantAct global_quantact_instance_memory(16, 0.95f, true, false, -1, QuantMode::symmetric);

Softmax::Softmax(int output_bit_i, QuantMode quant_mode_i, ForceDequantMode force_dequant)
{
	output_bit = output_bit_i;
	quant_mode = quant_mode_i;
	if (force_dequant == ForceDequantMode::nonlinear || force_dequant == ForceDequantMode::softmax)
	{
		quant_mode = QuantMode::none;
	}
	global_quantact_instance_memory = QuantAct(16, 0.95f, true, false, -1, quant_mode);
	act = &global_quantact_instance_memory;
	x0 = -0.6931f; //  - ln2
	n = 30; // sufficiently large integer
	coef[0] =  0.35815147f;
	coef[1] = 0.96963238f;
	coef[2] = 1.f; // ax**2 + bx + c
	coef[1] /= coef[0];
	coef[2] /= coef[0];
}

scaled_tuple3d Softmax::int_polynomial(Softmax &self, Tensor3d x_int, const int xr, const int xc, const int xd, Tensor scaling_factor, const int sfr, const int sfc)
{
	copy(scaling_factor, sfr, sfc, self.memory.b_int);
	reciprocal(scaling_factor, sfr, sfc, self.memory.b_int);
	mul_scalar(self.memory.b_int, sfr, sfc, self.coef[1], self.memory.b_int);
	floor_tensor(self.memory.b_int, sfr, sfc, self.memory.b_int);

	copy(scaling_factor, sfr, sfc, self.memory.c_int);
	pow_scalar(scaling_factor, sfr, sfc, 2.f, self.memory.c_int); //makes the previous line unnecessary
	reciprocal(self.memory.c_int, sfr, sfc, self.memory.c_int);
	mul_scalar(self.memory.c_int, sfr, sfc, self.coef[2], self.memory.c_int);

	copy(x_int, xr, xc, xd, self.memory.z);
	add_scalar(x_int, xr, xc, xd, self.memory.b_int[0], self.memory.z);//makes the previous line unnecessary
	mul_dot(x_int, xr, xc, xd, self.memory.z, xr, xc, xd, self.memory.z);
	add_scalar(self.memory.z, xr, xc, xd, self.memory.c_int[0], self.memory.z);

	pow_scalar(scaling_factor, sfr, sfc, 2, scaling_factor);
	mul_scalar(scaling_factor, sfr, sfc, self.coef[0], scaling_factor);
	
	scaled_tuple3d returnme;
	returnme.matrix = self.memory.z;
	returnme.scaling_factor = scaling_factor;
	return returnme;
}

scaled_tuple3d Softmax::int_exp(Softmax &self, Tensor3d x_int, const int xr, const int xc, const int xd, Tensor scaling_factor, const int sfr, const int sfc)
{
	copy(scaling_factor, sfr, sfc, self.memory.x0_int);
	reciprocal(scaling_factor, sfr, sfc, self.memory.x0_int); //makes previous line unnecessary
	mul_scalar(self.memory.x0_int, sfr, sfc, self.x0, self.memory.x0_int);
	floor_tensor(self.memory.x0_int, sfr, sfc, self.memory.x0_int);

	copy(self.memory.x0_int, sfr, sfc, self.memory.temp);
	mul_scalar(self.memory.temp, sfr, sfc, (float)self.n, self.memory.temp);
	max_scalar(x_int, sfr, sfc, self.memory.temp[0], x_int);

	copy(x_int,xr,xc,xd, self.memory.q);
	div_scalar(self.memory.q, xr, xc, xd, self.memory.x0_int[0], self.memory.q);
	floor_tensor(self.memory.q, xr, xc, xd, self.memory.q);

	copy(x_int, xr, xc, xd, self.memory.r);
	copy(self.memory.q,xr,xc,xd, self.memory.temp2);
	mul_scalar(self.memory.temp2, xr, xc, xd, self.memory.x0_int[0], self.memory.temp2);
	sub(x_int, xr, xc, xd, self.memory.temp2, xr, xc, xd, self.memory.r);

	scaled_tuple3d exp = int_polynomial(self, self.memory.r, xr, xc, xd, scaling_factor, sfr, sfc); //returns a scaled tuple with the size of the first tensor

	sub_scalar((float)self.n, self.memory.q, xr, xc, xd, self.memory.q);
	exp2_tensor(self.memory.q, xr, xc, xd, self.memory.q);
	mul_dot(exp.matrix, xr, xc, xd, self.memory.q, xr, xc, xd, exp.matrix);
	floor_tensor(exp.matrix, xr, xc, xd, exp.matrix);
	clamp(exp.matrix, xr, xc, xd, 0.f, FLT_MAX, exp.matrix);

	float x = (float)exp2(self.n);
	div_scalar(exp.scaling_factor, xr, xc, xd, x, exp.scaling_factor);
	
	return exp;
}


scaled_tuple3d Softmax::softmax_forward(Softmax &self, Tensor3d x, const int xr, const int xc, const int xd, Tensor scaling_factor, const int sfr, const int sfc)
{
	//ASSUMPTION x is 12x22x22, scaling factor is 1x1
	copy(x, xr, xc, xd, self.memory.x_int);
	if (self.quant_mode == QuantMode::none)
	{
		normal_softmax(self, self.memory.x_int, xr, xc, xd, self.memory.x_int, xr, xc, xd);
		scaled_tuple3d rm;
		rm.matrix = self.memory.x_int;
		rm.scaling_factor = nullptr;
		return rm;
	}
	//symmetric mode below

	//not same dims
	div_scalar(self.memory.x_int, xr, xc, xd, scaling_factor[0], self.memory.x_int);
	copy(self.memory.x_int, xr, xc, xd, self.memory.x_int_max); //unnessecary
	max(self.memory.x_int, xr, xc, xd, 1, self.memory.x_int_max); //TODO: x_int_max should actually be a different size.
	sub(self.memory.x_int, xr, xc, xd, self.memory.x_int_max, xr, xc, xd, self.memory.x_int);
	eq(self.memory.x_int, xr, xc, xd, (const Tensor3d)softmax_b4_int_exp, xr, xc, xd);//verification
	scaled_tuple3d exp = int_exp(self, self.memory.x_int, xr, xc, xd, scaling_factor, sfr, sfc);

	exp = QuantAct::QuantAct_forward(*self.act, exp.matrix, xr, xc, xd, exp.scaling_factor, sfr, sfc, nullptr, 0, 0, 0, nullptr, 0,0, nullptr, nullptr);
	copy(exp.matrix, xr, xc, xd, self.memory.exp_int);
	div_scalar(exp.matrix, xr, xc, xd, exp.scaling_factor[0], self.memory.exp_int);
	copy(self.memory.exp_int, xr, xc, xd, self.memory.exp_int_sum);
	sum(self.memory.exp_int, xr, xc, xd, 1, self.memory.exp_int_sum); //TODO: must properly size exp_int_um

	copy(self.memory.exp_int_sum, xr, xc, xd, self.memory.factor); //TODO: correct dimentions and unnessecary
	reciprocal(self.memory.exp_int_sum, xr, xc, xd, self.memory.factor); //TODO: correct dimentions in this section on expintsum and factor
	mul_scalar(self.memory.factor, xr, xc, xd, exp2f(32), self.memory.factor);
	floor_tensor(self.memory.factor, xr, xc, xd, self.memory.factor);
	mul_dot(self.memory.exp_int, xr, xc, xd, self.memory.factor, xr, xc, xd, self.memory.exp_int);
	div_scalar(self.memory.exp_int, xr, xc, xd, exp2f(float(32-self.output_bit)), self.memory.exp_int);
	floor_tensor(self.memory.exp_int, xr, xc, xd, self.memory.exp_int);

	scaled_tuple3d returnme;
	returnme.matrix = self.memory.exp_int;
	float sf = 1.f / exp2f((float)self.output_bit);
	mul_scalar(returnme.matrix, xr, xc, xd, sf, returnme.matrix);
	self.memory.scaling_return[0] = sf;
	returnme.scaling_factor = self.memory.scaling_return;

	return returnme;
}

void Softmax::normal_softmax(Softmax &self, Tensor3d src, const int srcr, const int srcc, const int srcd, Tensor3d dest, const int destr, const int destc, const int destd)
{//according to https ://pytorch.org/docs/stable/generated/torch.nn.Softmax.html?highlight=softmax#torch.nn.Softmax
 // dimention is curretly locked to 1, regarding each row as a unit to perform softmax on.
	//NOT VERIFIED BTW, not used in testing either
	unsigned i, j, d;
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

void Softmax::set_param(
	Softmax &self,
	softmax_memory memory,
	quantact_memory qa_memory
)
{
	self.memory = memory;
	QuantAct::set_param(*self.act, qa_memory); //call setup on the local quantact module
}
