//softmax.h, created by Hunter Messner for the HUBERT project
#ifndef __HUBERT_SOFTMAX_H__
#define __HUBERT_SOFTMAX_H__

#include "HLS/hls.h"
#include "HLS/stdio.h"
#include "tensors.h" 
#include "tensor3d.h"
#include "hubertEnums.h"

//softmax.h implements the softmax function

class Softmax
{
public:
	//initializer
	Softmax(quantact_memory memory,int output_bit, QuantMode quant_mode = QuantMode::none, ForceDequantMode force_dequant = ForceDequantMode::none);

	//member functions
	static scaled_tuple3d int_polynomial(Softmax &self, Tensor3d x_int, const int xr, const int xc, const int xd, Tensor scaling_factor, const int sfr, const int sfc);//returned matrix is size xr xc xd
	static scaled_tuple3d int_exp(Softmax &self, Tensor3d x_int, const int xr, const int xc, const int xd, Tensor scaling_factor, const int sfr, const int sfc); //returned matrix is size xr xc xd
	static scaled_tuple3d softmax_forward(Softmax &self, Tensor3d x, const int xr, const int xc, const int xd, Tensor scaling_factor, const int sfr, const int sfc);
	static void normal_softmax(Softmax &self, Tensor3d src, const int srcr, const int srcc, const int srcd, Tensor3d dest, const int destr, const int destc, const int destd);

	static void set_param(
		Softmax &self,
		softmax_memory memory,
		quantact_memory qa_memory
	);

	int output_bit;
	QuantMode quant_mode;
	QuantAct* act;
	float x0;
	int n;
	float coef[3];
	
	softmax_memory memory;

};
#endif
