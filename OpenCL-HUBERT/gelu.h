//gelu.h, created by Hunter Messner for the HUBERT project
#ifndef __HUBERT_GELU_H__
#define __HUBERT_GELU_H__

#include "HLS/hls.h"
#include "HLS/stdio.h"
#include "tensors.h" 
#include "tensor3d.h"
#include "hubertEnums.h"

//gelu.h implements the gelu function
//no initializer, see gelu_testbench on how to assign constants to the global memory
//member functions
Tensor3d int_erf(gelu_memory memory, Tensor3d x_int, const int xr, const int xc, const int xd);
Tensor3d gelu_forward(gelu_memory memory, Tensor3d x_int, const int xr, const int xc, const int xd);
#endif
