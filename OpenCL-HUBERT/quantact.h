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
    QuantAct(int activation_bit, 
             float act_range_momentum=0.95f,
             bool running_stat=true,
             bool per_channel=false,
             int channel_len= -1,
             QuantMode quant_mode = QuantMode::none);

	~QuantAct();

    //other functions
	static scaled_tuple3d QuantAct_forward(
		QuantAct &self,
		Tensor x,
        Tensor pre_act_scaling_factor,
        Tensor3d identity,
        Tensor identity_scaling_factor,
        Tensor specified_min,
        Tensor specified_max);

    void fix();
    void unfix();

    static Tensor symmetric_linear_quantization_params(
		unsigned num_bits,
        Tensor saturation_min,
        Tensor saturation_max,
        bool per_channel=false);

    static Tensor3d symmetric_quant_forward(QuantAct &self, Tensor3d x, int k, Tensor specified_scale);
    static Tensor3d linear_quantize(Tensor3d x, Tensor scale, Tensor zero_point);
    static Tensor3d fixedpoint_mul(
        Tensor3d pre_act,
        Tensor pre_act_scaling_factor,
        int bit_num,
        QuantMode quant_mode,
        Tensor z_scaling_factor,
        Tensor3d identity,
        Tensor identity_scaling_factor
    );
	void set_param(preload x_min_n, preload x_max_n, preload act_scaling_factor_n);

    //members
    int activation_bit;
    float act_range_momentum;
    bool running_stat;
    QuantMode quant_mode;
    bool per_channel;
};

#endif