//gelu_testbench.cpp, created by Hunter Messner for the HUBERT project
#include "HLS/hls.h"
#include "HLS/stdio.h"
#include "quantact.h"
#include "hubertEnums.h"
#include "tensors.h" 
#include "tensor3d.h"
#include "gelu.h"
#include "constant_headers/gelu_x_int.h"
#include "constant_headers/gelu_b_int.h"
#include "constant_headers/gelu_c_int.h"
#include "constant_headers/gelu_neg_b_int.h"
#include "constant_headers/gelu_shift_int.h"
#include "constant_headers/gelu_result_int.h"




#define CHANNEL_LEN 1
/*************************** GELU DEFINES ******************************/
const int xr=1;
const int xc=3072;
const int xd=22;


/*** Space for GELU ***/
underlyingTensor sigmoid_int[xr*xc*xd]; //size of sigmoid_int is the same as x_int, we just want a new sigmoid int. Must allocate on our own.
underlyingTensor signGelu[xr*xc*xd];// also size of gleu input x_int
underlyingTensor abs_int[xr*xc*xd]; //also size of x_int
underlyingTensor temp[xr*xc*xd]; //wozah, you guess the size!
underlyingTensor y_int[xr*xc*xd]; //also size of x_int, could be optimized away probably


gelu_memory g_memory;
/************************* END GELU DEFINES ****************************/

int main()
{   
	g_memory.shift_int = (Tensor)gelu_shift_int; //these ints are known at compile time but theyre arrays, so they come from header files.
	g_memory.b_int = (Tensor)gelu_b_int; //Export these from your finished python model, they change after training but are const through inference
	g_memory.c_int = (Tensor)gelu_c_int;
	g_memory.neg_b_int = (Tensor)gelu_neg_b_int; //b_int but negative. I am also loading this in a header.
	g_memory.sfr = 1;
	g_memory.sfc = 3072; //size of the prev three tensors
	g_memory.sigmoid_int = sigmoid_int; //size of sigmoid_int is the same as x_int, we just want a new sigmoid int. Must allocate on our own.
	g_memory.sign = signGelu;// also size of gleu input x_int
	g_memory.abs_int = abs_int; //also size of x_int
	g_memory.temp = temp; //wozah, you guess the size!
	g_memory.y_int = y_int; //also size of x_int, could be optimized away probably

	Tensor3d gelu_result;
	gelu_result = gelu_forward(g_memory, (Tensor3d)gelu_x_int, xr,xc,xd);

	eq(gelu_result, xr,xc,xd, (Tensor3d)gelu_result_int,xr,xc,xd);
}