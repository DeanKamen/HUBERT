//quantact_testbench.cpp, created by Hunter Messner for the HUBERT project
//actually a testbench for all of the modules
#include "HLS/hls.h"
#include "HLS/stdio.h"
#include "quantact.h"
#include "hubertEnums.h"
#include "tensors.h" 
#include "tensor3d.h"
#include "softmax.h"
#include "constant_headers/self_attn_softmax_act_act_scaling_factor.h"
#include "constant_headers/self_attn_softmax_act_x_max.h"
#include "constant_headers/self_attn_softmax_act_x_min.h"
#include "constant_headers/softmax_layer0.h"
#include "constant_headers/softmax_sf_layer0.h"
#include "constant_headers/softmax_layer0_out.h"
//#include "QuantLinear.h"
//#include "IntLayerNorm.h"
//#include "IntGELU.h"
//#include "multiheadAttention.h"
//#include "sentence_encoder_layer.h"



#define CHANNEL_LEN 1
/*************************** QUANTACT DEFINES ******************************/
//TODO: let the input be defined in  a header file. 
//const float* quant_act_inside_softmax = qa_x_softmax;
const int qaisr=22;
const int qaisc=22;
const int qaisd=12;

//const float* qais_scaling_factor = qa_pasf_softmax; //pre act sf
const int qaissfr=1;
const int qaissfc=1;

const float* identity = nullptr;
const int ir=1;
const int ic=1;
const int id=1;

const float* identity_sf = nullptr;
const int isfr=1;
const int isfc=1;

//TEMPORARY DEFINES. Eventually move these to a higher level and pass them in through function parameters
const int x_minr = 1;
const int x_minc = CHANNEL_LEN;

const int x_maxr = 1;
const int x_maxc = CHANNEL_LEN;

const int asfr = 1;
const int asfc = CHANNEL_LEN;

/*** Space for QUANTACT ***/
float x_min[x_minr * x_minc];
float x_max[x_maxr * x_maxc];
float act_scaling_factor[asfr * asfc];
float x_act[qaisr*qaisc*qaisd]; //dims of qaisr
float temp_qa[qaisr*qaisc*qaisd]; // also same dims of qaisr

//used in symmetric_linear_quantization_params
float slqp_scale[x_minr * x_minc];

//used in symmetric_quant_forward
float sqf_scale[asfr * asfc];

//used in linear_quantize
float lq_scale[asfr * asfc];

//used in fixedpoint_mul
float z_int[qaisr*qaisc*qaisd]; //size of pre act 
float _A[qaissfr * qaissfc]; //size of pre act sf
float _B[asfr*asfc]; //size of zsf
float new_scale[qaissfr * qaissfc]; //size of pasf
float m[qaissfr * qaissfc]; //size of new scale
float e[qaissfr * qaissfc]; //size of new scale
float output[qaisr*qaisc*qaisd]; //size of  z_int
float twos[qaisr*qaisc*qaisd]; //size of output
float wx_int[ir*ic*id];
float _A1[isfr*isfc]; //size of isf
float _B1[asfr*asfc]; //size of zsf
float new_scale1[isfr*isfc]; //size of isf
float m1[isfr*isfc];
float e1[isfr*isfc]; //size of isf
float output1[qaisr*qaisc*qaisd]; //size of  z_int

quantact_memory qa_memory;
/************************* END QUANTACT DEFINES ****************************/


/*************************** SOFTMAX DEFINES *******************************/

float* softmax_in = softmax_layer0;
const int sir = 22;
const int sic = 22;
const int sid = 12;

float* softmax_scaling_factor = softmax_sf_layer0; //pre act sf
const int ssfr = 1;
const int ssfc = 1;

//used in int_polynomial
float z[sir*sic*sid]; //size of x_int
float b_int[ssfr * ssfc]; //size of scaling factor
float c_int[ssfr * ssfc]; //size of scaling factor

//used in int_exp
float x0_int[ssfr * ssfc];// size of scaling factor
float temp_sm[ssfr * ssfc]; //size of scaling factor
float q[sir*sic*sid]; // size of x_int
float r[sir*sic*sid]; //size of x_int
float temp_sm2[sir*sic*sid]; //size of x_int

//used in softmax_forward
float x_int[sir*sic*sid]; //size of x
float exp_int[sir*sic*sid]; //size of x
float x_int_max[sir * sic * sid]; //size of x with (dim 1 collapsed) 
float exp_int_sum[sir* sic *sid]; //size of exp_int (with dim 1 collapsed) 
float factor[sir * sic * sid]; //size of exp_int_sum
float scaling_return [1]; // 1x1

softmax_memory sm_memory;

/************************* END SOFTMAX DEFINES *****************************/

int main()
{   
	//QuantAct memory init
	qa_memory.x_min = x_min;
	qa_memory.x_max = x_max;
	qa_memory.act_scaling_factor = act_scaling_factor;
	qa_memory.x_act = x_act; //dims of x
	qa_memory.temp = temp_qa; // also same dims of x
	qa_memory.slqp_scale = slqp_scale;
	qa_memory.sqf_scale = sqf_scale;
	qa_memory.lq_scale = lq_scale;
	qa_memory.z_int = z_int; //size of pre act 
	qa_memory._A = _A; //size of pre act sf
	qa_memory._B = _B; //size of zsf
	qa_memory.new_scale = new_scale; //size of pasf
	qa_memory.m = m; //size of new scale
	qa_memory.e = e; //size of new scale
	qa_memory.output = output; //size of  self.z_int
	qa_memory.twos = twos; //size of output
	qa_memory.wx_int = wx_int;
	qa_memory._A1 = _A1; //size of isf
	qa_memory._B1 = _B1; //size of zsf
	qa_memory.new_scale1 = new_scale1; //size of isf
	qa_memory.m1 = m1;
	qa_memory.e1 = e1; //size of isf
	qa_memory.output1 = output1;//size of  self.z_int

	//Softmax memory init
	sm_memory.z = z; //size of x_int
	sm_memory.b_int = b_int; //size of scaling factor
	sm_memory.c_int = c_int; //size of scaling factor
	sm_memory.x0_int = x0_int;// size of scaling factor
	sm_memory.temp = temp_sm; //size of scaling factor
	sm_memory.q = q; // size of x_int
	sm_memory.r = r; //size of x_int
	sm_memory.temp2 = temp_sm2; //size of x_int
	sm_memory.x_int = x_int; //size of x
	sm_memory.exp_int = exp_int; //size of x
	sm_memory.x_int_max = x_int_max; //size of x with (one dimention collapsed)
	sm_memory.exp_int_sum = exp_int_sum; //size of exp_int (with one dimention collapsed) 
	sm_memory.factor = factor; //size of exp_int_sum
	sm_memory.scaling_return = scaling_return; // 1x1

	/*
	QuantAct testQuantAct(8, 0.95f, true, false, -1, QuantMode::symmetric);
	QuantAct::set_param(testQuantAct, qa_memory);

	scaled_tuple3d result1 = QuantAct::QuantAct_forward(
		testQuantAct, 
		quant_act_inside_softmax, qaisr, qaisc, qaisd, 
		qais_scaling_factor, qaissfr, qaissfc,
		identity, ir, ic, id,
		identity_sf, ir, ic,
		nullptr, nullptr);

	print(result1.matrix, qaisr, qaisc, qaisd);
	*/

	//QuantAct + softmax verification
	copy((const Tensor)self_attn_softmax_act_x_min, x_minr, x_minc, qa_memory.x_min);
	copy((const Tensor)self_attn_softmax_act_x_max, x_maxr, x_maxc, qa_memory.x_max);
	copy((const Tensor)self_attn_softmax_act_act_scaling_factor, asfr, asfc, qa_memory.act_scaling_factor);

	scaled_tuple3d softmax_result;
    Softmax(sm_memory, qa_memory, 8, QuantMode::symmetric, ForceDequantMode::layernorm);
	//testSoftmax.set_param(sm_memory, qa_memory);
    softmax_result = softmax_forward(
		sm_memory,
		qa_memory,
		softmax_in, sir, sic, sid, 
		softmax_scaling_factor, ssfr, ssfc);
	
	/*
	 //QuantLinear verification
	int thirtytwo = 32;
	Tensor3dXL* matrix3d_testdata = loadGeneric3dXL("bin/quantlinear_layer0.bin");
	TensorXL* quantlinear_scaling_factor = new TensorXL(1, 1, 0.04931505f);
	QuantLinear testQuantLinear(8, &thirtytwo, true, QuantMode::symmetric);
	testQuantLinear.set_param(preload::self_attn__q_proj__fc_scaling_factor, 
		preload::self_attn__q_proj__weight, 
		preload::self_attn__q_proj__bias);
	result1 = testQuantLinear.quantlinear_forward(matrix3d_testdata, quantlinear_scaling_factor);
	*/
	/*
	//IntLayerNorm Verification
	Tensor3dXL* matrix3d_testdata = loadGeneric3dXL("bin/intlayernorm_layer0.bin");
	TensorXL* intlayernorm_scaling_factor = new TensorXL(1, 1, 7.685552e-06f);
	IntLayerNorm testIntLayerNorm(32, true, QuantMode::symmetric, ForceDequantMode::layernorm);
	testIntLayerNorm.set_param(preload::self_attn_layer_norm__shift, preload::self_attn_layer_norm__weight, preload::self_attn_layer_norm__bias);
	result1 = testIntLayerNorm.intlayernorm_forward(matrix3d_testdata, intlayernorm_scaling_factor);
	printf("RESTULTS START\n");
    Tensor3dXL::print(result1.matrix);
    TensorXL::print(result1.scaling_factor);
	*/
	/*
	//IntGELU Verification
	Tensor3dXL* matrix3d_testdata = loadGeneric3dXL("bin/intgelu_layer0.bin");
	TensorXL* intgelu_scaling_factor = loadGeneric2d("bin/intgelu_sf_layer0.bin");
	IntGELU testintgelu(QuantMode::symmetric, ForceDequantMode::layernorm);
	result1 = testintgelu.intgelu_forward(matrix3d_testdata, intgelu_scaling_factor);
	printf("RESTULTS START\n");
	Tensor3dXL::print(result1.matrix);
	TensorXL::print(result1.scaling_factor);
	*/
	
	/*
	Tensor3dXL* q_testdata = loadGeneric3dXL("bin/q_multihead0.bin");
	Tensor3dXL* k_testdata = loadGeneric3dXL("bin/k_multihead0.bin");
	Tensor3dXL* v_testdata = loadGeneric3dXL("bin/v_multihead0.bin");
	TensorXL* q_scaling_factor = loadGeneric2d("bin/qsf_multihead0.bin");
	TensorXL* k_scaling_factor = loadGeneric2d("bin/vsf_multihead0.bin");
	TensorXL* v_scaling_factor = loadGeneric2d("bin/ksf_multihead0.bin");
	multiheadAttention testMULTIHEAD(768, 12, -1, -1, 0.1f, true, false, false, true, 
		false, 0, 8, QuantMode::symmetric, ForceDequantMode::layernorm, true);
	result1 = testMULTIHEAD.multiheadAttention_forward(q_testdata, k_testdata, v_testdata, nullptr, nullptr, false, false, nullptr, false, false,
		q_scaling_factor, k_scaling_factor, v_scaling_factor);
	*/

	/*
	//SEL Verification
	Tensor3dXL* matrix3d_testdata = loadGeneric3dXL("bin/tsel_input.bin");
	sentenceEncoderLayer testSEL(768, 3072, 12, 0.1f, 0.1f, 0.f, nullptr, false, 0.0f, 8, QuantMode::symmetric, ForceDequantMode::layernorm, false);
	result1 = testSEL.sel_forward(matrix3d_testdata, nullptr);
	printf("RESTULTS START\n");
	Tensor3dXL::print(result1.matrix);
	TensorXL::print(result1.scaling_factor);
	*/

}