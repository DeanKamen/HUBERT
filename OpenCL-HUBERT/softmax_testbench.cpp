//quantact_testbench.cpp, created by Hunter Messner for the HUBERT project
//actually a testbench for all of the modules
#include "HLS/hls.h"
#include "HLS/stdio.h"
#include "quantact.h"
#include "hubertEnums.h"
#include "tensors.h" 
#include "tensor3d.h"
#include "softmax.h"
#include "constant_headers/softmax_b_int.h"
#include "constant_headers/softmax_c_int.h"
#include "constant_headers/softmax_x0_int.h"
#include "constant_headers/softmax_x_int.h"



#define CHANNEL_LEN 1

/*************************** SOFTMAX DEFINES *******************************/

//input matrix dims
const int sir = 22;//"softmax input rows"
const int sic = 22;
const int sid = 12;

//scaling factor dims
const int ssfr = 1; //"softmax scaling factor rows"
const int ssfc = 1;

//used in int_polynomial
int z[sir*sic*sid]; //size of x_int

//used in int_exp
int x0_int[ssfr * ssfc];// size of scaling factor
int temp_sm[ssfr * ssfc]; //size of scaling factor
int q[sir*sic*sid]; // size of x_int
int r[sir*sic*sid]; //size of x_int
int temp_sm2[sir*sic*sid]; //size of x_int

//used in softmax_forward
int exp_int[sir*sic*sid]; //size of x
int x_int_max[sir * sic * sid]; //size of x with (dim 1 collapsed) 
int exp_int_sum[sir* sic *sid]; //size of exp_int (with dim 1 collapsed) 
int factor[sir * sic * sid]; //size of exp_int_sum

softmax_memory sm_memory;

/************************* END SOFTMAX DEFINES *****************************/

int main()
{   
	//Softmax memory init
	sm_memory.z = z; //size of x_int
	sm_memory.b_int = softmax_b_int; //size of scaling factor
	sm_memory.c_int = softmax_c_int; //size of scaling factor
	sm_memory.x0_int = softmax_x0_int;// size of scaling factor
	sm_memory.temp = temp_sm; //size of scaling factor
	sm_memory.q = q; // size of x_int
	sm_memory.r = r; //size of x_int
	sm_memory.temp2 = temp_sm2; //size of x_int
	sm_memory.exp_int = exp_int; //size of x
	sm_memory.x_int_max = x_int_max; //size of x with (one dimention collapsed)
	sm_memory.exp_int_sum = exp_int_sum; //size of exp_int (with one dimention collapsed) 
	sm_memory.factor = factor; //size of exp_int_sum
	sm_memory.sfr = ssfr;
	sm_memory.sfc = ssfc;
	sm_memory.output_bit = 8;
	sm_memory.n = 30;

	//testSoftmax.set_param(sm_memory, qa_memory);
    Tensor3d softmax_result = softmax_forward(sm_memory, softmax_x_int, sir, sic, sid);
	print_brief(softmax_result, sir, sic, sid);
}