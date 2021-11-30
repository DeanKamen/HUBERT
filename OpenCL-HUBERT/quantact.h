//quantact.h, created by Hunter Messner for the HUBERT project
#ifndef __HUBERT_QUANTACT_H__
#define __HUBERT_QUANTACT_H__

#include "HLS/hls.h"
#include "HLS/stdio.h"
#include "tensors.h" 
#include "tensor3d.h"
#include <iostream>
#include "hubertEnums.h"

class QuantAct
{
public:
	//initializer
	QuantAct(
		int activation_bit,
		float act_range_momentum = 0.95f,
		bool running_stat = true,
		bool per_channel = false,
		int channel_len = -1,
		QuantMode quant_mode = QuantMode::none);

	//other functions
	static scaled_tuple3d QuantAct_forward( //returns a matrix of size xr,xc,xd
		QuantAct& self,
		Tensor3d x, const int xr, const int xc, const int xd,//identity and x are 22x1x768 or 12x22x22.
		Tensor pre_act_scaling_factor, const int pasfr, const int pasfc,
		Tensor3d identity, const int identityr, const int identityc, const int identityd,
		Tensor identity_scaling_factor, const int isfr, const int isfc,
		Tensor specified_min,
		Tensor specified_max);

	static Tensor symmetric_linear_quantization_params(
		QuantAct &self,
		unsigned num_bits,
		Tensor saturation_min,
		const int smr,
		const int smc,
		Tensor saturation_max,
		bool per_channel);

	static Tensor3d symmetric_quant_forward(QuantAct &self, Tensor3d x, const int xr, const int xc, const int xd, int k, Tensor specified_scale, const int ssr, const int ssc);
	static Tensor3d linear_quantize(QuantAct &self, Tensor3d x, const int xr, const int xc, const int xd, Tensor scale_c, const int sr, const int sc, Tensor zero_point, const int zr, const int zc);
	
	static Tensor3d fixedpoint_mul(
		QuantAct &self,
		Tensor3d pre_act, const int par, const int pac, const int pad,
		Tensor pre_act_scaling_factor, const int pasfr, const int pasfc,
		int bit_num,
		QuantMode quant_mode,
		Tensor z_scaling_factor, const int zsfr, const int zsfc,
		Tensor3d identity, const int identityr, const int identityc, const int identityd,
		Tensor identity_scaling_factor, const int isfr, const int isfc
	);


	static void set_param(//this allocates space for all of the members that are pointers.
		QuantAct &self,
		quantact_memory memory
	); 

	//member variables
	int activation_bit;
	float act_range_momentum;
	bool running_stat;
	QuantMode quant_mode;
	bool per_channel;

	//memory
	quantact_memory memory;

};
#endif