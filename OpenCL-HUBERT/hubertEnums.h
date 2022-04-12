//hubert_enums.h, created by Hunter Messner for the HUBERT project

#ifndef __HUBERT_ENUMS_H__
#define __HUBERT_ENUMS_H__

#include "tensors.h"
#include "tensor3d.h"

//WARNING: when changing these types, you only change the internal primitive type of the Tensor
typedef int* Tensor3d; //meant to be some int type from 8 to 64 bits
typedef int* Tensor;

//enum to desribe all preloaded Tensors
enum class QuantMode {none, symmetric};

enum class ForceDequantMode{none, nonlinear, softmax, gelu, layernorm};

struct scaled_tuple
{//to get the most fidelity out of the translation, I make
 //a struct that emulates the returned tuple of most forwards
	Tensor matrix;
	Tensor scaling_factor;
};

struct scaled_tuple3d
{//same as scaled_tuple but 3d
	Tensor3d matrix;
	Tensor scaling_factor;
};

struct quantact_memory
{
	float* x_min;
	float* x_max;
	float* act_scaling_factor;
	Tensor3d x_act; //dims of x
	Tensor3d temp; // also same dims of x

	//used in symmetric_linear_quantization_params
	Tensor slqp_scale;

	//used in symmetric_quant_forward
	Tensor sqf_scale;

	//used in linear_quantize
	Tensor lq_scale;

	//used in fixedpoint_mul
	Tensor3d z_int; //size of pre act 
	Tensor _A; //size of pre act sf
	Tensor _B; //size of zsf
	Tensor new_scale; //size of pasf
	Tensor m; //size of new scale
	Tensor e; //size of new scale
	Tensor output; //size of  self.z_int
	Tensor twos; //size of output
	Tensor3d wx_int;
	Tensor _A1; //size of isf
	Tensor _B1; //size of zsf
	Tensor new_scale1; //size of isf
	Tensor m1;
	Tensor e1; //size of isf
	Tensor output1;//size of  self.z_int

	//Kind of like member variables but not because thats illegal
	int activation_bit;
	float act_range_momentum;
	bool running_stat;
	QuantMode quant_mode;
	bool per_channel;
};

struct softmax_memory
{
	/*pointers to space for the functions to use*/

	//used in int_polynomial
	//Export these from your finished python model, they change after training but are const through inference
	Tensor3d z; //size of x_int
	Tensor b_int; //size of scaling factor
	Tensor c_int; //size of scaling factor - > one row 1x3072
	int sfr, sfc; //sizes of the scaling factor

	//used in int_exp
	Tensor x0_int;// size of scaling factor
	Tensor temp; //size of scaling factor
	Tensor3d q; // size of x_int
	Tensor3d r; //size of x_int
	Tensor3d temp2; //size of x_int

	//used in softmax_forward
	Tensor3d x_int_max; //size of x with columns collapsed
	Tensor3d exp_int; //size of x
	Tensor3d exp_int_sum; //size of exp_int (with columns collapsed) 
	Tensor3d factor; //size of exp_int_sum

	//Kind of like member variables but not because thats illegal (pointer to pointer + static funcs)
	int output_bit;
	int n;
};

struct gelu_memory
{
	Tensor shift_int; //these ints are known at compile time but theyre arrays, so they come from header files.
	Tensor b_int; //Export these from your finished python model, they change after training but are const through inference
	Tensor c_int;
	Tensor neg_b_int; //b_int but negative. I am also loading this in a header.
	int sfr, sfc; //size of the prev three tensors
	Tensor3d sigmoid_int; //size of sigmoid_int is the same as x_int, we just want a new sigmoid int. Must allocate on our own.
	Tensor3d sign;// also size of gleu input x_int
	Tensor3d abs_int; //also size of x_int
	Tensor3d temp; //wozah, you guess the size!
	Tensor3d y_int; //also size of x_int, could be optimized away probably
	
};

enum class preload
{ //same name but with double underscore as word seperators instead of dots
    activation_fn_approx__input_scaling_factor=0,
    input_act__x_min,
    input_act__x_max,
    input_act__act_scaling_factor,
    self_attn__k_proj__weight,
    self_attn__k_proj__bias,
    self_attn__k_proj__fc_scaling_factor,
    self_attn__k_proj__weight_integer,
    self_attn__k_proj__bias_integer,
    self_attn__v_proj__weight,
    self_attn__v_proj__bias,
    self_attn__v_proj__fc_scaling_factor,
    self_attn__v_proj__weight_integer,
    self_attn__v_proj__bias_integer,
    self_attn__q_proj__weight,
    self_attn__q_proj__bias,
    self_attn__q_proj__fc_scaling_factor,
    self_attn__q_proj__weight_integer,
    self_attn__q_proj__bias_integer,
    self_attn__k_proj_act__x_min,
    self_attn__k_proj_act__x_max,
    self_attn__k_proj_act__act_scaling_factor,
    self_attn__v_proj_act__x_min,
    self_attn__v_proj_act__x_max,
    self_attn__v_proj_act__act_scaling_factor,
    self_attn__q_proj_act__x_min,
    self_attn__q_proj_act__x_max,
    self_attn__q_proj_act__act_scaling_factor,
    self_attn__softmax__act__x_min,
    self_attn__softmax__act__x_max,
    self_attn__softmax__act__act_scaling_factor,
    self_attn__attn_probs_act__x_min,
    self_attn__attn_probs_act__x_max,
    self_attn__attn_probs_act__act_scaling_factor,
    self_attn__attn_act__x_min,
    self_attn__attn_act__x_max,
    self_attn__attn_act__act_scaling_factor,
    self_attn__out_proj__weight,
    self_attn__out_proj__bias,
    self_attn__out_proj__fc_scaling_factor,
    self_attn__out_proj__weight_integer,
    self_attn__out_proj__bias_integer,
    pre_self_attn_layer_norm_act__x_min,
    pre_self_attn_layer_norm_act__x_max,
    pre_self_attn_layer_norm_act__act_scaling_factor,
    self_attn_layer_norm__weight,
    self_attn_layer_norm__bias,
    self_attn_layer_norm__shift,
    self_attn_layer_norm__activation__x_min,
    self_attn_layer_norm__activation__x_max,
    self_attn_layer_norm__activation__act_scaling_factor,
    fc1_act__x_min,
    fc1_act__x_max,
    fc1_act__act_scaling_factor,
    fc2_act__x_min,
    fc2_act__x_max,
    fc2_act__act_scaling_factor,
    fc1__weight,
    fc1__bias,
    fc1__fc_scaling_factor,
    fc1__weight_integer,
    fc1__bias_integer,
    fc2__weight,
    fc2__bias,
    fc2__fc_scaling_factor,
    fc2__weight_integer,
    fc2__bias_integer,
    pre_final_layer_norm_act__x_min,
    pre_final_layer_norm_act__x_max,
    pre_final_layer_norm_act__act_scaling_factor,
    final_layer_norm__weight,
    final_layer_norm__bias,
    final_layer_norm__shift,
    final_layer_norm__activation__x_min,
    final_layer_norm__activation__x_max,
    final_layer_norm__activation__act_scaling_factor
};

#endif