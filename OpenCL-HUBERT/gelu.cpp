//softmax.cpp, created by Hunter Messner for the HUBERT project
#include "HLS/hls.h"
#include "HLS/stdio.h"
#include "tensors.h" 
#include "tensor3d.h"
#include <iostream>
#include "quantact.h"
#include "hubertEnums.h"
#include "gelu.h"
#include "HLS/math.h"
#include <limits.h>
#include <float.h>

//verification
//#include "constant_headers/gelu_pre_fte.h"
//member functions
Tensor3d int_erf(gelu_memory memory, Tensor3d x_int, int xr, int xc, int xd) {
	//x_int is normally 22x1x3072, while our scaling factor constants are 1x3072
	sign(x_int, xr, xc, xd, memory.sign);
	abs_tensor(x_int, xr, xc, xd, memory.abs_int);
	min_dot(memory.abs_int, xr, xc, xd, memory.neg_b_int, memory.abs_int); //this is a custom function tailored for GELU so syntax is weird.
	add(memory.abs_int, xr, xc, xd, memory.b_int, memory.sfr, memory.sfc, memory.temp);
	pow_scalar(memory.temp, xr, xc, xd, (underlyingTensor)2, memory.temp);
	add(memory.temp, xr, xc, xd, memory.c_int, memory.sfr, memory.sfc, memory.y_int);

	mul_dot(memory.y_int, xr, xc, xd, memory.sign, xr,xc,xd, memory.y_int);
	div_scalar(memory.y_int, xr, xc, xd, underlyingTensor(1 << 14), memory.y_int);//This generates a small amount of error when compared to python verions
	//eq(memory.y_int,xr,xc,xd, (Tensor)gelu_pre_fte, xr, xc, xd);
	return memory.y_int;
}
component Tensor3d gelu_forward(gelu_memory memory, Tensor3d x_int, int xr, int xc, int xd) {
	memory.sigmoid_int = int_erf(memory, x_int, xr, xc, xd);
	add(memory.sigmoid_int,xr,xc,xd, memory.shift_int, memory.sfr, memory.sfc, memory.sigmoid_int);
	mul_dot(x_int, xr, xc, xd, memory.sigmoid_int, xr, xc, xd, x_int);
	return x_int;
}