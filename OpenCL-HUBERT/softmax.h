//softmax.h, created by Hunter Messner for the HUBERT project
#ifndef __HUBERT_SOFTMAX_H__
#define __HUBERT_SOFTMAX_H__

#include "HLS/hls.h"
#include "HLS/stdio.h"
#include "tensors.h" 
#include "tensor3d.h"
#include "hubertEnums.h"

//softmax.h implements the softmax function

//member functions
Tensor3d int_polynomial(softmax_memory& memory, Tensor3d x_int, const int xr, const int xc, const int xd);//returned matrix is size xr xc xd
Tensor3d int_exp(softmax_memory& memory, Tensor3d x_int, const int xr, const int xc, const int xd); //returned matrix is size xr xc xd
Tensor3d softmax_forward(softmax_memory memory, Tensor3d x, const int xr, const int xc, const int xd);
#endif
