//tensor3d.cpp
// 3d HLS tensor implementation for the HUBERT project.
//created by Hunter Messner on 7/19/2021

#include "HLS/hls.h"
#include "HLS/math.h"
#include "HLS/stdio.h"
#include "tensors.h"
#include "tensor3d.h"
#include <iostream>

/*                    DEFINITIONS                      */

//2d broadcasting across 3d
void add(const Tensor3d A, int rowsA, int colsA, int depA, Tensor B, int rowsB, int colsB, Tensor3d C)
{
	//defer error checking to a layer by layer basis. 
	#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		add(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

void sub(const Tensor3d A, int rowsA, int colsA, int depA, Tensor B, int rowsB, int colsB, Tensor3d C)
{
	#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		sub(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

void mul_dot(const Tensor3d A, int rowsA, int colsA, int depA, Tensor B, int rowsB, int colsB, Tensor3d C)
{
	#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		mul_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

void div_dot(const Tensor3d A, int rowsA, int colsA, int depA, Tensor B, int rowsB, int colsB, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		div_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

void pow_dot(const Tensor3d A, int rowsA, int colsA, int depA, Tensor B, int rowsB, int colsB, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		pow_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

void add(const Tensor3d A, int rowsA, int colsA, int depA, const Tensor3d B, int rowsB, int colsB, int depB, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		add(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(B, rowsB, colsB, depB, d), rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}
void sub(const Tensor3d A, int rowsA, int colsA, int depA, const Tensor3d B, int rowsB, int colsB, int depB, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		sub(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(B, rowsB, colsB, depB, d), rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

void mul_dot(const Tensor3d A, int rowsA, int colsA, int depA, const Tensor3d B, int rowsB, int colsB, int depB, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		mul_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(B, rowsB, colsB, depB, d), rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}
void div_dot(const Tensor3d A, int rowsA, int colsA, int depA, const Tensor3d B, int rowsB, int colsB, int depB, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		div_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(B, rowsB, colsB, depB, d), rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

void pow_dot(const Tensor3d A, int rowsA, int colsA, int depA, const Tensor3d B, int rowsB, int colsB, int depB, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		pow_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(B, rowsB, colsB, depB, d), rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

//scalar type
void add_scalar(const Tensor3d A, int rowsA, int colsA, int depA, float B, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		add_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, get_layer(C, rowsA, colsA, depA, d));
	}
}

void mul_scalar(const Tensor3d A, int rowsA, int colsA, int depA, float B, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		mul_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, get_layer(C, rowsA, colsA, depA, d));
	}
}

void sub_scalar(const Tensor3d A, int rowsA, int colsA, int depA, float B, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		sub_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, get_layer(C, rowsA, colsA, depA, d));
	}
}
void sub_scalar(float B, const Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		sub_scalar(B, get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}
void div_scalar(const Tensor3d A, int rowsA, int colsA, int depA, float B, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		div_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, get_layer(C, rowsA, colsA, depA, d));
	}
}

void pow_scalar(const Tensor3d A, int rowsA, int colsA, int depA, float B, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		pow_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, get_layer(C, rowsA, colsA, depA, d));
	}
}

void max(const Tensor3d A, int rowsA, int colsA, int depA, int dim, Tensor3d C)
{
	if (dim == 0 )
	{
#pragma max_concurrency 1
		for (int d = 0; d < depA; d++)
		{
			max(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, dim, get_layer(C, rowsA, colsA, depA, d));
		}
		//we already shrink one dim in the loop, so we shrink it here too.
		shrinkTensor(C, rowsA, colsA, depA, C, 1, colsA, depA);//make the depth continuous
	}
	else if (dim == 1)
	{
#pragma max_concurrency 1
		for (int d = 0; d < depA; d++)
		{
			max(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, dim, get_layer(C, rowsA, colsA, depA, d));
		}
		shrinkTensor(C, rowsA, colsA, depA, C, rowsA, 1, depA); //make the depth continuous
	}
	else //dim ==2
	{
		int i, j;
		float largest;
		bool first = true;
#pragma loop_coalesce
		for (i = 0; i < colsA; i++)
		{
			for (j = 0; j < rowsA; j++)
			{
				for (int d = 0; d < depA; d++)
				{
					if (first)
					{
						largest = get(A, rowsA, colsA, depA, j, i, d);
						first = false;
					}
					else {
						if (largest < get(A, rowsA, colsA, depA, j, i, d))
						{
							largest = get(A, rowsA, colsA, depA, j, i, d);
						}
					}
				}
				set(C, rowsA, colsA, depA, j, i, 0, largest);
				first = true;
			}
		}
		shrinkTensor(C, rowsA, colsA, depA, C, rowsA, colsA, 1);
	}
}

void min(const Tensor3d A, int rowsA, int colsA, int depA, int dim, Tensor3d C)
{
	if (dim == 0)
	{
#pragma max_concurrency 1
		for (int d = 0; d < depA; d++)
		{
			min(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, dim, get_layer(C, rowsA, colsA, depA, d));
		}
		//we already shrink one dim in the loop, so we shrink it here too.
		shrinkTensor(C, rowsA, colsA, depA, C, 1, colsA, depA);
	}
	else if (dim == 1)
	{
#pragma max_concurrency 1
		for (int d = 0; d < depA; d++)
		{
			min(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, dim, get_layer(C, rowsA, colsA, depA, d));
		}
		shrinkTensor(C, rowsA, colsA, depA, C, rowsA, 1, depA);
	}
	else //dim ==2
	{
		int i, j;
		float smallest;
		bool first = true;
#pragma loop_coalesce
		for (i = 0; i < colsA; i++)
		{
			for (j = 0; j < rowsA; j++)
			{
				for (int d = 0; d < depA; d++)
				{
					if (first)
					{
						smallest = get(A, rowsA, colsA, depA, j, i, d);
						first = false;
					}
					else {
						if (smallest > get(A, rowsA, colsA, depA, j, i, d))
						{
							smallest = get(A, rowsA, colsA, depA, j, i, d);
						}
					}
				}
				set(C, rowsA, colsA, 1, j, i, 0, smallest);
				first = true;
			}
		}
		shrinkTensor(C, rowsA, colsA, depA, C, rowsA, colsA, 1);
	}
}

void max(const Tensor3d A, int rowsA, int colsA, int depA) // full collapse
{
	max(A, rowsA, colsA, depA, 2, A); //depth is now 1
	max(A, rowsA, colsA, 1, 0, A); //rows is now 1
	max(A, 1, colsA, 1, 1, A); //now A is a scalar
}

void min(const Tensor3d A, int rowsA, int colsA, int depA)
{
	min(A, rowsA, colsA, depA, 2, A); //depth is now 1
	min(A, rowsA, colsA, 1, 0, A); //rows is now 1
	min(A, 1, colsA, 1, 1, A); //now A is a scalar
}

void max_scalar(const Tensor3d A, int rowsA, int colsA, int depA, float compare, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		max_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, compare, get_layer(C, rowsA, colsA, depA, d));
	}
}

void min_scalar(const Tensor3d A, int rowsA, int colsA, int depA, float compare, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		min_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, compare, get_layer(C, rowsA, colsA, depA, d));
	}
}

void min_dot(const Tensor3d A, int rowsA, int colsA, int depA, Tensor B, Tensor3d C)
{ //assuming a and B are the same size.
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		min_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, get_layer(C, rowsA, colsA, depA, d));
	}
}

void abs_tensor(const Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		abs_tensor(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

void floor_tensor(const Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		floor_tensor(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

void exp2_tensor(const Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		exp2_tensor(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

void clamp(const Tensor3d A, int rowsA, int colsA, int depA, float min, float max, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		clamp(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, min, max, get_layer(C, rowsA, colsA, depA, d));
	}
}

void roundTensor(const Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		roundTensor(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

void reciprocal(const Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		reciprocal(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

void sum(const Tensor3d A, int rowsA, int colsA, int depA, int dim, Tensor3d C)
{
	if (dim == 0)
	{
#pragma max_concurrency 1
		for (int d = 0; d < depA; d++)
		{
			sum(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, dim, get_layer(C, rowsA, colsA, depA, d));
		}
		//we already shrink one dim in the loop, so we shrink it here too.
		shrinkTensor(C, rowsA, colsA, depA, C, 1, colsA, depA);
	}
	else if (dim == 1)
	{
#pragma max_concurrency 1
		for (int d = 0; d < depA; d++)
		{
			sum(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, dim, get_layer(C, rowsA, colsA, depA, d));
		}
		shrinkTensor(C, rowsA, colsA, depA, C, rowsA, 1, depA);
	}
	else //dim ==2
	{
		float running;
		running = float(0);
#pragma loop_coalesce
		for (int i = 0; i < colsA; i++)
		{
			for (int j = 0; j < rowsA; j++)
			{
				for (int d = 0; d < depA; d++)
				{
					running += get(A, rowsA, colsA, depA, j, i, d);
				}
				set(C, rowsA, colsA, 1, j, i, 0, running); //C has depth 1.
				running = 0;
			}
		}
		shrinkTensor(C, rowsA, colsA, depA, C, rowsA, colsA, 1);
	}
}

void sign(const Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		sign(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

void mean(const Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		mean(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, 1, 1, depA, d)); //the output matrix C should be a depth vector
	}
}

void sqrt_tensor(const Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		sqrt_tensor(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

//adressing methods where dep is depth and select the 2d array you want.
float get(const Tensor3d A, int rowsA, int colsA, int depA, int row, int col, int dep)
{
	int first_el_of_layer = dep*rowsA*colsA;
	return A[first_el_of_layer + row * colsA + col];
}

void set(const Tensor3d A, int rowsA, int colsA, int depA, int row, int col, int dep, float val)
{
	int first_el_of_layer = dep*rowsA*colsA;
	A[first_el_of_layer + row * colsA + col] = val;
}

Tensor get_layer(const Tensor3d A, int rowsA, int colsA, int depA, int dep)
{
	int first_el_of_layer = dep * rowsA*colsA;
	return &A[first_el_of_layer]; //C++ pointers are so easY! 
}

void set(const Tensor3d A, int rowsA, int colsA, int depA, int dep, Tensor slice)
{//does a copy operation from slice to tensor
#pragma max_concurrency 1
	for (int i = 0; i < rowsA*colsA; i++)
	{
		A[dep*rowsA*colsA + i] = slice[i];
	}
}

void toTwoD(const Tensor3d A, int rowsA, int colsA, int depA, Tensor C)
{
	if (depA == 1)
	{
		for (int r = 0; r < rowsA; r++)
		{
			for (int c = 0; c < colsA; c++)
			{
				set(C, rowsA, colsA, r, c, get(A, rowsA, colsA, depA, 0, r, c));
			}
		}
	}
	else if (rowsA == 1)
	{// Here we transform depth into rows. depth 0 being the first row
		for (int d = 0; d < depA; d++)
		{
			for (int c = 0; c < colsA; c++)
			{
				set(C, rowsA, colsA, d, c, get(A, rowsA, colsA, depA, 0, c, d));
			}
		}
	}
	else if (colsA == 1)
	{// Here we transform depth into cols. depth 0 being the first column
		for (int d = 0; d < depA; d++)
		{
			for (int r = 0; r < rowsA; r++)
			{
				set(C, rowsA, colsA, r, d, get(A, rowsA, colsA, depA, r, 0, d));
			}
		}
	}
	else
	{
		printf("array cannot be reduced\n");
		//assert(false);
	}
}

void append(const Tensor3d A, int rowsA, int colsA, Tensor slice)
{//just starts an array. Idk why this is here
	set(A, rowsA, colsA, 0, 0, slice);
}

//helper functions
void print(const Tensor3d A, int rowsA, int colsA, int depA)
{
	printf("Tensor3d\n[");
	for (int d = 0; d < depA; d++)
	{
		print(get_layer(A, rowsA, colsA, depA,d), rowsA, colsA);
		printf(",\n");
	}
	printf("] End Tensor3d\n");
}

void print_brief(const Tensor3d A, int rowsA, int colsA, int depA)
{
	printf("Tensor3d\n[");
	for (int d = 0; d < depA; d++)
	{
		print_brief(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA);
		printf(",\n");
	}
	printf("] End Tensor3d\n");
}

void copy(const Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		copy(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

void shrinkTensor(const Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C, int rowsC, int colsC, int depC)
{
	//we will assume that one of [rows, cols, or dep] have been collapsed to 1.
	//we know that each individual layer is correct, but the layers may not be collapsed to be contiguous with one another
	if (rowsA != rowsC && rowsC == 1)
	{//we have a 3d matrix who has one row but the values are positioned assuming no dim was collapsed. Iterate over the remaining dims using different assumptions to collapse to C.
#pragma loop_coalesce
		for (int i = 0; i < depA; i++)
		{
			Tensor cur_layer = get_layer(A, rowsA, colsA, depA, i); //this is necessary because the depth is not continuous
			for (int j = 0; j < colsA; j++)
			{
				float take = get(cur_layer, 1, colsA, 0, j); //by assuming this layer was collapsed, we can get it correctly
				set(C, rowsC, colsC, depC, 0, j, i, take);
			}
		}
	}
	else if (colsA != colsC && colsC == 1)
	{
#pragma loop_coalesce
		for (int i = 0; i < depA; i++)
		{
			Tensor cur_layer = get_layer(A, rowsA, colsA, depA, i); //this is necessary because the depth is not continuous
			for (int j = 0; j < rowsA; j++)
			{
				float take = get(cur_layer, rowsA, 1, j, 0); //by assuming this layer was collapsed, we can get it correctly
				set(C, rowsC, colsC, depC, j, 0, i, take);
			}
		}
	}
	else if (depA != depC && depC == 1)
	{
#pragma loop_coalesce
		for (int i = 0; i < rowsA; i++)
		{
			for (int j = 0; j < colsA; j++)
			{
				float take = get(A, rowsA, colsA, depA, i, j, 0);
				set(C, rowsC, colsC, depC, i, j, 0, take);
			}
		}
	}
}

bool eq(const Tensor3d A, int rowsA, int colsA, int depA, const Tensor3d B, int rowsB, int colsB, int depB)
{
	for (int d = 0; d < depA; d++)
	{
		if (!eq_verbose(get_layer(A, rowsA, colsA, depA,d), rowsA, colsA, get_layer(B, rowsB, colsB, depB,d), rowsB, colsB))
		{
			printf("Layer %d\n", d);
			return false;
		}
	}
	return true;
}