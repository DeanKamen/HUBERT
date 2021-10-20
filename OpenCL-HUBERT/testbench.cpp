//testbench.cpp, created by Hunter Messner for the HUBERT project
#include "HLS/hls.h"
#include "HLS/stdio.h"
#include "tensors.h" 
#include "CL/opencl.hpp"


int main()
{   
	float bruh[MAX_ROWS*MAX_COLS];
	float yuh[MAX_ROWS*MAX_COLS];
	for (int i = 0; i < MAX_ROWS; i++)
	{
		for (int j = 0; j < MAX_COLS; j++)
		{
			set(bruh, MAX_ROWS, MAX_COLS, i, j, i*MAX_ROWS+j);
			transposed_set(yuh, MAX_ROWS, MAX_COLS, i, j, i*MAX_ROWS + j);
		}
	}
	print_brief(bruh, MAX_ROWS, MAX_COLS);
	print_brief(bruh, MAX_ROWS, MAX_COLS);
}
