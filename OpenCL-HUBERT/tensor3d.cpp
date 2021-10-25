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
void add(Tensor3d A, int rowsA, int colsA, int depA, Tensor B, int rowsB, int colsB, Tensor3d C)
{
	//defer error checking to a layer by layer basis. 
	for (unsigned d = 0; d < depA; d++)
	{
		add(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

void sub(Tensor3d A, int rowsA, int colsA, int depA, Tensor B, int rowsB, int colsB, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		sub(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

void mul_dot(Tensor3d A, int rowsA, int colsA, int depA, Tensor B, int rowsB, int colsB, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		mul_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

void div_dot(Tensor3d A, int rowsA, int colsA, int depA, Tensor B, int rowsB, int colsB, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		div_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

void pow_dot(Tensor3d A, int rowsA, int colsA, int depA, Tensor B, int rowsB, int colsB, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		pow_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

void add(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d B, int rowsB, int colsB, int depB, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		add(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(B, rowsB, colsB, depB, d), rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}
void sub(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d B, int rowsB, int colsB, int depB, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		sub(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(B, rowsB, colsB, depB, d), rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

void mul_dot(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d B, int rowsB, int colsB, int depB, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		mul_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(B, rowsB, colsB, depB, d), rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}
void div_dot(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d B, int rowsB, int colsB, int depB, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		div_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(B, rowsB, colsB, depB, d), rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

void pow_dot(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d B, int rowsB, int colsB, int depB, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		pow_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(B, rowsB, colsB, depB, d), rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

//scalar type
void add_scalar(Tensor3d A, int rowsA, int colsA, int depA, float B, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		add_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, get_layer(C, rowsA, colsA, depA, d));
	}
}

void mul_scalar(Tensor3d A, int rowsA, int colsA, int depA, float B, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		mul_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, get_layer(C, rowsA, colsA, depA, d));
	}
}

void sub_scalar(Tensor3d A, int rowsA, int colsA, int depA, float B, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		sub_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, get_layer(C, rowsA, colsA, depA, d));
	}
}
void sub_scalar(float B, Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		sub_scalar(B, get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}
void div_scalar(Tensor3d A, int rowsA, int colsA, int depA, float B, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		div_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, get_layer(C, rowsA, colsA, depA, d));
	}
}

void pow_scalar(Tensor3d A, int rowsA, int colsA, int depA, float B, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		pow_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, get_layer(C, rowsA, colsA, depA, d));
	}
}

void max(Tensor3d A, int rowsA, int colsA, int depA, int dim, Tensor3d C)
{
	if (dim == 0 || dim == 1)
	{
		for (unsigned d = 0; d < depA; d++)
		{
			max(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, dim, get_layer(C, rowsA, colsA, depA, d));
		}
	}
	else //dim ==2
	{
		unsigned i, j;
		float largest;
		bool first = true;
		for (i = 0; i < colsA; i++)
		{
			for (j = 0; j < rowsA; j++)
			{
				for (unsigned d = 0; d < depA; d++)
				{
					if (first)
					{
						largest = get(A, rowsA, colsA, depA, i, j, d);
						first = false;
					}
					else {
						if (largest < get(A, rowsA, colsA, depA, j, i, d))
						{
							largest = get(A, rowsA, colsA, depA, j, i, d);
						}
					}
				}
				set(C, rowsA, colsA, 1, i, j, 0, largest);
				first = true;
			}
		}
	}
}

void min(Tensor3d A, int rowsA, int colsA, int depA, int dim, Tensor3d C)
{
	if (dim == 0 || dim == 1)
	{
		for (unsigned d = 0; d < depA; d++)
		{
			min(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, dim, get_layer(C, rowsA, colsA, depA, d));
		}
	}
	else //dim ==2
	{
		unsigned i, j;
		float smallest;
		bool first = true;
		for (i = 0; i < colsA; i++)
		{
			for (j = 0; j < rowsA; j++)
			{
				for (unsigned d = 0; d < depA; d++)
				{
					if (first)
					{
						smallest = get(A, rowsA, colsA, depA, i, j, d);
						first = false;
					}
					else {
						if (smallest > get(A, rowsA, colsA, depA, j, i, d))
						{
							smallest = get(A, rowsA, colsA, depA, j, i, d);
						}
					}
				}
				set(C, rowsA, colsA, 1, i, j, 0, smallest);
				first = true;
			}
		}
	}
}

void max(Tensor3d A, int rowsA, int colsA, int depA) // full collapse
{
	max(A, rowsA, colsA, depA, 2, A); //depth is now 1
	max(A, rowsA, colsA, 1, 0, A); //rows is now 1
	max(A, 1, colsA, 1, 1, A); //now A is a scalar
}

void min(Tensor3d A, int rowsA, int colsA, int depA)
{
	min(A, rowsA, colsA, depA, 2, A); //depth is now 1
	min(A, rowsA, colsA, 1, 0, A); //rows is now 1
	min(A, 1, colsA, 1, 1, A); //now A is a scalar
}

void max_scalar(Tensor3d A, int rowsA, int colsA, int depA, float compare, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		max_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, compare, get_layer(C, rowsA, colsA, depA, d));
	}
}

void min_scalar(Tensor3d A, int rowsA, int colsA, int depA, float compare, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		min_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, compare, get_layer(C, rowsA, colsA, depA, d));
	}
}

void min_dot(Tensor3d A, int rowsA, int colsA, int depA, Tensor B, int rowsB, int colsB, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		min_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, get_layer(C, rowsA, colsA, depA, d));
	}
}

void abs_tensor(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		abs_tensor(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

void floor_tensor(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		floor_tensor(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

void exp2_tensor(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		exp2_tensor(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

void clamp(Tensor3d A, int rowsA, int colsA, int depA, float min, float max, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		clamp(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, min, max, get_layer(C, rowsA, colsA, depA, d));
	}
}

void roundTensor(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		roundTensor(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

void reciprocal(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		reciprocal(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

void sum(Tensor3d A, int rowsA, int colsA, int depA, int dim, Tensor3d C)
{
	if (dim == 0 || dim == 1)
	{
		for (unsigned d = 0; d < depA; d++)
		{
			sum(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, dim, get_layer(C, rowsA, colsA, depA, d));
		}
	}

	else //dim = 2
	{
		float running;
		running = float(0);
		for (unsigned i = 0; i < colsA; i++)
		{
			for (unsigned j = 0; j < rowsA; j++)
			{
				for (unsigned d = 0; d < depA; d++)
				{
					running += get(A, rowsA, colsA, depA, j, i, d);
				}
				set(C, rowsA, colsA, 1, i, j, 0, running); //C has depth 1.
				running = 0; 
			}
		}
	}
}

void sign(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		sign(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

void mean(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		mean(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

void sqrt_tensor(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		sqrt_tensor(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

//adressing methods where dep is depth and select the 2d array you want.
float get(Tensor3d A, int rowsA, int colsA, int depA, int row, int col, int dep)
{
	int first_el_of_layer = dep*rowsA*colsA;
	return A[first_el_of_layer + row * colsA + col];
}

void set(Tensor3d A, int rowsA, int colsA, int depA, int row, int col, int dep, float val)
{
	int first_el_of_layer = dep*rowsA*colsA;
	A[first_el_of_layer + row * colsA + col] = val;
}

Tensor get_layer(Tensor3d A, int rowsA, int colsA, int depA, int dep)
{
	int first_el_of_layer = dep * rowsA*colsA;
	return &A[first_el_of_layer]; //C++ pointers are so easY! 
}

void set(Tensor3d A, int rowsA, int colsA, int depA, int dep, Tensor slice)
{//does a copy operation from slice to tensor
	for (int i = 0; i < rowsA*colsA; i++)
	{
		A[dep*rowsA*colsA + i] = slice[i];
	}
}

void toTwoD(Tensor3d A, int rowsA, int colsA, int depA, Tensor C)
{
	if (depA == 1)
	{
		for (unsigned r = 0; r < rowsA; r++)
		{
			for (unsigned c = 0; c < colsA; c++)
			{
				set(C, rowsA, colsA, r, c, get(A, rowsA, colsA, depA, 0, r, c));
			}
		}
	}
	else if (rowsA == 1)
	{// Here we transform depth into rows. depth 0 being the first row
		for (unsigned d = 0; d < depA; d++)
		{
			for (unsigned c = 0; c < colsA; c++)
			{
				set(C, rowsA, colsA, d, c, get(A, rowsA, colsA, depA, 0, c, d));
			}
		}
	}
	else if (colsA == 1)
	{// Here we transform depth into cols. depth 0 being the first column
		for (unsigned d = 0; d < depA; d++)
		{
			for (unsigned r = 0; r < rowsA; r++)
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

void append(Tensor3d A, int rowsA, int colsA, Tensor slice)
{//just starts an array. Idk why this is here
	set(A, rowsA, colsA, 0, 0, slice);
}

//helper functions
void print(Tensor3d A, int rowsA, int colsA, int depA)
{
	printf("Tensor3d\n[");
	for (unsigned d = 0; d < depA; d++)
	{
		print(get_layer(A, rowsA, colsA, depA,d), rowsA, colsA);
		printf(",\n");
	}
	printf("] End Tensor3d\n");
}

void print_brief(Tensor3d A, int rowsA, int colsA, int depA)
{
	printf("Tensor3d\n[");
	for (unsigned d = 0; d < depA; d++)
	{
		print_brief(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA);
		printf(",\n");
	}
	printf("] End Tensor3d\n");
}

bool eq(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d B, int rowsB, int colsB, int depB)
{
	for (unsigned d = 0; d < depA; d++)
	{
		if (!eq_verbose(get_layer(A, rowsA, colsA, depA,d), rowsA, colsA, get_layer(B, rowsB, colsB, depB,d), rowsB, colsB))
		{
			return false;
		}
	}
	return true;
}