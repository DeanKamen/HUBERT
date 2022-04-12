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

//test only
#include "constant_headers/softmax_n_m_q.h"
#include "constant_headers/softmax_exp2.h"
#include "constant_headers/softmax_exp_int.h"
#include "constant_headers/softmax_poly.h"
#include "constant_headers/softmax_return.h"

Tensor3d int_polynomial(softmax_memory& memory, Tensor3d x_int, const int xr, const int xc, const int xd)
{
	add(x_int, xr, xc, xd, memory.b_int, memory.sfr, memory.sfc, memory.z);
	mul_dot(x_int, xr, xc, xd, memory.z, xr, xc, xd, memory.z);
	add(memory.z, xr, xc, xd, memory.c_int, memory.sfr, memory.sfc, memory.z);
	
	return memory.z;
}

Tensor3d int_exp(softmax_memory& memory, Tensor3d x_int, const int xr, const int xc, const int xd)
{
	//x0 is imported

	copy(memory.x0_int, memory.sfr, memory.sfc, memory.temp);
	mul_scalar(memory.temp, memory.sfr, memory.sfc, memory.n, memory.temp);
	max_scalar(x_int, xr, xc, xd, memory.temp[0], x_int); //TODO: restriction on temp being 1x1 

	copy(x_int,xr,xc,xd, memory.q);
	div_dot(memory.q, xr, xc, xd, memory.x0_int, memory.sfr, memory.sfc, memory.q); //TODO: if x0_int is always 1x1, this can be div_scalar
	//integer division makes floor unnecessary
	
	copy(x_int, xr, xc, xd, memory.r);
	copy(memory.q,xr,xc,xd, memory.temp2);
	mul_dot(memory.temp2, xr, xc, xd, memory.x0_int, memory.sfr, memory.sfc, memory.temp2);
	sub(x_int, xr, xc, xd, memory.temp2, xr, xc, xd, memory.r);
	Tensor3d exp_int = int_polynomial(memory, memory.r, xr, xc, xd); //returns a scaled tuple with the size of the first tensor
	
	//sub_scalar(memory.n, memory.q, xr, xc, xd, memory.q);//I overwrite q here because I dont need it anymore. Saves memory.
	//eq(memory.q, xr, xc, xd, (Tensor3d)softmax_n_m_q, xr, xc, xd);
	//exp2_tensor(memory.q, xr, xc, xd, memory.q);
	//eq(memory.q, xr, xc, xd, (Tensor3d)softmax_exp2, xr, xc, xd);
	//eq(exp_int, xr, xc, xd, (Tensor3d)softmax_poly, xr, xc, xd);
	//mul_dot(exp_int, xr, xc, xd, memory.q, xr, xc, xd, exp_int);
	//clamp(exp_int, xr, xc, xd, 0, INT_MAX, exp_int);
	rightShift(exp_int, xr, xc, xd, memory.q, xr,xc,xd, exp_int); // exp_int >> q
	//eq(exp_int, xr, xc, xd, (Tensor3d)softmax_exp_int, xr, xc, xd);
	return exp_int; //just a pointer to z-int still.
}


component Tensor3d softmax_forward(softmax_memory memory, Tensor3d x_int, const int xr, const int xc, const int xd)
{
	//symmetric mode below
	max(x_int, xr, xc, xd, 1, memory.x_int_max);
	sub(x_int, xr, xc, xd, memory.x_int_max, xr, 1, xd, x_int); //we collapsed the columns
	Tensor3d exp_int = int_exp(memory, x_int, xr, xc, xd);
	copy(exp_int, xr, xc, xd, memory.exp_int); //new memory lot, TODO: could probably delete later
	copy(memory.exp_int, xr, xc, xd, memory.exp_int_sum);
	sum(memory.exp_int, xr, xc, xd, 1, memory.exp_int_sum); //we collapse columns 
	
	div_dot(memory.exp_int, xr, xc, xd, memory.exp_int_sum, xr, 1, xd, memory.exp_int); //this is an attempt at the original algorithm
	
	//fill(memory.factor, xr, 1, xd, 1 << 31);
	//div_dot(memory.factor, xr, 1, xd, memory.exp_int_sum, xr, 1, xd, memory.factor);
	//mul_dot(memory.exp_int, xr, xc, xd, memory.factor, xr, 1, xd, memory.exp_int);
	//div_scalar(memory.exp_int, xr, xc, xd, 1<<(32-memory.output_bit), memory.exp_int);

	eq(memory.exp_int, xr, xc, xd, (Tensor3d)softmax_return, xr, xc, xd);
	return memory.exp_int;
}