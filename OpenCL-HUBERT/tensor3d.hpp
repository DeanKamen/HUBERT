//tensor3d.hpp
// 3d HLS tensor implementation for the HUBERT project.
//created by Hunter Messner on 7/19/2021

#include "HLS/hls.h"
#include "HLS/math.h"
#include "HLS/stdio.h"
#include <iostream>

/*                    DEFINITIONS                      */

//2d broadcasting across 3d
template<typename t3d_int, typename tint, typename loc>
void add( t3d_int* A, loc rowsA, loc colsA, loc depA, tint* B, loc rowsB, loc colsB, t3d_int* C)
{
	//defer error checking to a layer by layer basis. 
	#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		add(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename tint, typename loc>
void sub( t3d_int* A, loc rowsA, loc colsA, loc depA, tint* B, loc rowsB, loc colsB, t3d_int* C)
{
	#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		sub(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename tint, typename loc>
void mul_dot( t3d_int* A, loc rowsA, loc colsA, loc depA, tint* B, loc rowsB, loc colsB, t3d_int* C)
{
	#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		mul_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename tint, typename loc>
void div_dot( t3d_int* A, loc rowsA, loc colsA, loc depA, tint* B, loc rowsB, loc colsB, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		div_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename tint, typename loc>
void pow_dot( t3d_int* A, loc rowsA, loc colsA, loc depA, tint* B, loc rowsB, loc colsB, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		pow_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename loc>
void add( t3d_int* A, loc rowsA, loc colsA, loc depA,  t3d_int* B, loc rowsB, loc colsB, loc depB, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		add(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(B, rowsB, colsB, depB, d), rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename loc>
void sub( t3d_int* A, loc rowsA, loc colsA, loc depA,  t3d_int* B, loc rowsB, loc colsB, loc depB, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		sub(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(B, rowsB, colsB, depB, d), rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename loc>
void mul_dot( t3d_int* A, loc rowsA, loc colsA, loc depA,  t3d_int* B, loc rowsB, loc colsB, loc depB, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		mul_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(B, rowsB, colsB, depB, d), rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename loc>
void div_dot( t3d_int* A, loc rowsA, loc colsA, loc depA,  t3d_int* B, loc rowsB, loc colsB, loc depB, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		div_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(B, rowsB, colsB, depB, d), rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename loc>
void pow_dot( t3d_int* A, loc rowsA, loc colsA, loc depA,  t3d_int* B, loc rowsB, loc colsB, loc depB, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		pow_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(B, rowsB, colsB, depB, d), rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename loc>
void rightShift( t3d_int* A,  loc rowsA,  loc colsA, loc depA,  t3d_int* B,  loc rowsB,  loc colsB, loc depB, t3d_int* C) {
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		rightShift(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(B, rowsB, colsB, depB, d), rowsB, colsB, get_layer(C, rowsA, colsA, depA, d));
	}
}

//scalar type
template<typename t3d_int, typename loc>
void add_scalar( t3d_int* A, loc rowsA, loc colsA, loc depA, t3d_int B, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		add_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename loc>
void mul_scalar( t3d_int* A, loc rowsA, loc colsA, loc depA, t3d_int B, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		mul_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename loc>
void sub_scalar( t3d_int* A, loc rowsA, loc colsA, loc depA, t3d_int B, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		sub_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename loc>
void sub_scalar(t3d_int B,  t3d_int* A, loc rowsA, loc colsA, loc depA, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		sub_scalar(B, get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename loc>
void div_scalar( t3d_int* A, loc rowsA, loc colsA, loc depA, t3d_int B, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		div_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename loc>
void pow_scalar( t3d_int* A, loc rowsA, loc colsA, loc depA, t3d_int B, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		pow_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename loc>
void max( t3d_int* A, loc rowsA, loc colsA, loc depA, int dim, t3d_int* C)
{
	if (dim == 0 )
	{
#pragma max_concurrency 1
		for (loc d = 0; d < depA; d++)
		{
			max(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, dim, get_layer(C, rowsA, colsA, depA, d));
		}
		//we already shrink one dim in the loop, so we shrink it here too.
		shrinkTensor(C, rowsA, colsA, depA, C, 1, colsA, depA);//make the depth continuous
	}
	else if (dim == 1)
	{
#pragma max_concurrency 1
		for (loc d = 0; d < depA; d++)
		{
			max(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, dim, get_layer(C, rowsA, colsA, depA, d));
		}
		shrinkTensor(C, rowsA, colsA, depA, C, rowsA, 1, depA); //make the depth continuous
	}
	else //dim ==2
	{
		loc i, j;
		t3d_int largest;
		bool first = true;
#pragma loop_coalesce
		for (i = 0; i < colsA; i++)
		{
			for (j = 0; j < rowsA; j++)
			{
				for (loc d = 0; d < depA; d++)
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

template<typename t3d_int, typename loc>
void min( t3d_int* A, loc rowsA, loc colsA, loc depA, int dim, t3d_int* C)
{
	if (dim == 0)
	{
#pragma max_concurrency 1
		for (loc d = 0; d < depA; d++)
		{
			min(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, dim, get_layer(C, rowsA, colsA, depA, d));
		}
		//we already shrink one dim in the loop, so we shrink it here too.
		shrinkTensor(C, rowsA, colsA, depA, C, 1, colsA, depA);
	}
	else if (dim == 1)
	{
#pragma max_concurrency 1
		for (loc d = 0; d < depA; d++)
		{
			min(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, dim, get_layer(C, rowsA, colsA, depA, d));
		}
		shrinkTensor(C, rowsA, colsA, depA, C, rowsA, 1, depA);
	}
	else //dim ==2
	{
		loc i, j;
		t3d_int smallest;
		bool first = true;
#pragma loop_coalesce
		for (i = 0; i < colsA; i++)
		{
			for (j = 0; j < rowsA; j++)
			{
				for (loc d = 0; d < depA; d++)
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

template<typename t3d_int, typename loc>
void max( t3d_int* A, loc rowsA, loc colsA, loc depA) // full collapse
{
	max(A, rowsA, colsA, depA, 2, A); //depth is now 1
	max(A, rowsA, colsA, 1, 0, A); //rows is now 1
	max(A, 1, colsA, 1, 1, A); //now A is a scalar
}

template<typename t3d_int, typename loc>
void min( t3d_int* A, loc rowsA, loc colsA, loc depA)
{
	min(A, rowsA, colsA, depA, 2, A); //depth is now 1
	min(A, rowsA, colsA, 1, 0, A); //rows is now 1
	min(A, 1, colsA, 1, 1, A); //now A is a scalar
}

template<typename t3d_int, typename loc>
void max_scalar( t3d_int* A, loc rowsA, loc colsA, loc depA, t3d_int compare, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		max_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, compare, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename loc>
void min_scalar( t3d_int* A, loc rowsA, loc colsA, loc depA, t3d_int compare, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		min_scalar(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, compare, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename tint, typename loc>
void min_dot( t3d_int* A, loc rowsA, loc colsA, loc depA, tint* B, t3d_int* C)
{ //assuming a and B are the same size.
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		min_dot(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, B, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename loc>
void abs_tensor( t3d_int* A, loc rowsA, loc colsA, loc depA, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		abs_tensor(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}


template<typename t3d_int, typename loc>
void exp2_tensor( t3d_int* A, loc rowsA, loc colsA, loc depA, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		exp2_tensor(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename loc>
void clamp( t3d_int* A, loc rowsA, loc colsA, loc depA, t3d_int min, t3d_int max, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		clamp(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, min, max, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename loc>
void sum( t3d_int* A, loc rowsA, loc colsA, loc depA, int dim, t3d_int* C)
{
	if (dim == 0)
	{
#pragma max_concurrency 1
		for (loc d = 0; d < depA; d++)
		{
			sum(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, dim, get_layer(C, rowsA, colsA, depA, d));
		}
		//we already shrink one dim in the loop, so we shrink it here too.
		shrinkTensor(C, rowsA, colsA, depA, C, 1, colsA, depA);
	}
	else if (dim == 1)
	{
#pragma max_concurrency 1
		for (loc d = 0; d < depA; d++)
		{
			sum(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, dim, get_layer(C, rowsA, colsA, depA, d));
		}
		shrinkTensor(C, rowsA, colsA, depA, C, rowsA, 1, depA);
	}
	else //dim ==2
	{
		t3d_int running = 0;
#pragma loop_coalesce
		for (loc i = 0; i < colsA; i++)
		{
			for (loc j = 0; j < rowsA; j++)
			{
				for (loc d = 0; d < depA; d++)
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

template<typename t3d_int, typename loc>
void sign( t3d_int* A, loc rowsA, loc colsA, loc depA, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		sign(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename loc>
void mean( t3d_int* A, loc rowsA, loc colsA, loc depA, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		mean(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, 1, 1, depA, d)); //the output matrix C should be a depth vector
	}
}


//manipulation
template<typename t3d_int, typename loc>
void fill( t3d_int* A,  loc rowsA,  loc colsA, loc depA, t3d_int fillnum)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		fill(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, fillnum); 
	}
}

//adressing methods where dep is depth and select the 2d array you want.
template<typename t3d_int, typename loc>
t3d_int get( t3d_int* A, loc rowsA, loc colsA, loc depA, loc row, loc col, loc dep)
{
	int first_el_of_layer = dep*rowsA*colsA;
	return A[first_el_of_layer + row * colsA + col];
}

template<typename t3d_int, typename loc>
void set( t3d_int* A, loc rowsA, loc colsA, loc depA, loc row, loc col, loc dep, t3d_int val)
{
	int first_el_of_layer = dep*rowsA*colsA;
	A[first_el_of_layer + row * colsA + col] = val;
}

template<typename t3d_int, typename loc>
t3d_int* get_layer( t3d_int* A, loc rowsA, loc colsA, loc depA, loc dep)
{
	int first_el_of_layer = dep * rowsA*colsA;
	return &A[first_el_of_layer]; //C++ pointers are so easY! 
}

template<typename t3d_int, typename tint, typename loc>
void set( t3d_int* A, loc rowsA, loc colsA, loc depA, loc dep, tint* slice)
{//does a copy operation from slice to Tensor
#pragma max_concurrency 1
	for (loc i = 0; i < rowsA*colsA; i++)
	{
		A[dep*rowsA*colsA + i] = slice[i];
	}
}

template<typename t3d_int, typename tint, typename loc>
void toTwoD( t3d_int* A, loc rowsA, loc colsA, loc depA, tint* C)
{
	if (depA == 1)
	{
		for (loc r = 0; r < rowsA; r++)
		{
			for (loc c = 0; c < colsA; c++)
			{
				set(C, rowsA, colsA, r, c, get(A, rowsA, colsA, depA, 0, r, c));
			}
		}
	}
	else if (rowsA == 1)
	{// Here we transform depth into rows. depth 0 being the first row
		for (loc d = 0; d < depA; d++)
		{
			for (loc c = 0; c < colsA; c++)
			{
				set(C, rowsA, colsA, d, c, get(A, rowsA, colsA, depA, 0, c, d));
			}
		}
	}
	else if (colsA == 1)
	{// Here we transform depth into cols. depth 0 being the first column
		for (loc d = 0; d < depA; d++)
		{
			for (loc r = 0; r < rowsA; r++)
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

template<typename t3d_int, typename tint, typename loc>
void append( t3d_int* A, loc rowsA, loc colsA, tint* slice)
{//just starts an array. Idk why this is here
	set(A, rowsA, colsA, 0, 0, slice);
}

//helper functions
template<typename t3d_int, typename loc>
void print( t3d_int* A, loc rowsA, loc colsA, loc depA)
{
	printf("Tensor3d\n[");
	for (loc d = 0; d < depA; d++)
	{
		print(get_layer(A, rowsA, colsA, depA,d), rowsA, colsA);
		printf(",\n");
	}
	printf("] End Tensor3d\n");
}

template<typename t3d_int, typename loc>
void print_brief( t3d_int* A, loc rowsA, loc colsA, loc depA)
{
	printf("Tensor3d\n[");
	for (loc d = 0; d < depA; d++)
	{
		print_brief(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA);
		printf(",\n");
	}
	printf("] End Tensor3d\n");
}

template<typename t3d_int, typename loc>
void copy( t3d_int* A, loc rowsA, loc colsA, loc depA, t3d_int* C)
{
#pragma max_concurrency 1
	for (loc d = 0; d < depA; d++)
	{
		copy(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<typename t3d_int, typename loc>
void shrinkTensor( t3d_int* A, loc rowsA, loc colsA, loc depA, t3d_int* C, loc rowsC, loc colsC, loc depC)
{
	//we will assume that one of [rows, cols, or dep] have been collapsed to 1.
	//we know that each individual layer is correct, but the layers may not be collapsed to be contiguous with one another
	if (rowsA != rowsC && rowsC == 1)
	{//we have a 3d matrix who has one row but the values are positioned assuming no dim was collapsed. Iterate over the remaining dims using different assumptions to collapse to C.
#pragma loop_coalesce
		for (loc i = 0; i < depA; i++)
		{
			t3d_int* cur_layer = get_layer(A, rowsA, colsA, depA, i); //this is necessary because the depth is not continuous
			for (loc j = 0; j < colsA; j++)
			{
				t3d_int take = get(cur_layer, 1, colsA, 0, j); //by assuming this layer was collapsed, we can get it correctly
				set(C, rowsC, colsC, depC, 0, j, i, take);
			}
		}
	}
	else if (colsA != colsC && colsC == 1)
	{
#pragma loop_coalesce
		for (loc i = 0; i < depA; i++)
		{
			t3d_int* cur_layer = get_layer(A, rowsA, colsA, depA, i); //this is necessary because the depth is not continuous
			for (loc j = 0; j < rowsA; j++)
			{
				t3d_int take = get(cur_layer, rowsA, 1, j, 0); //by assuming this layer was collapsed, we can get it correctly
				set(C, rowsC, colsC, depC, j, 0, i, take);
			}
		}
	}
	else if (depA != depC && depC == 1)
	{
#pragma loop_coalesce
		for (loc i = 0; i < rowsA; i++)
		{
			for (loc j = 0; j < colsA; j++)
			{
				t3d_int take = get(A, rowsA, colsA, depA, i, j, 0);
				set(C, rowsC, colsC, depC, i, j, 0, take);
			}
		}
	}
}

template<typename t3d_int, typename loc>
bool eq( t3d_int* A, loc rowsA, loc colsA, loc depA,  t3d_int* B, loc rowsB, loc colsB, loc depB)
{
	for (loc d = 0; d < depA; d++)
	{
		if (!eq_verbose(get_layer(A, rowsA, colsA, depA,d), rowsA, colsA, get_layer(B, rowsB, colsB, depB,d), rowsB, colsB))
		{
			printf("Layer %d\n", d);
			return false;
		}
	}
	return true;
}

/*
void floor_tensor( Tensor3d A, int rowsA, loc colsA, int depA, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		floor_tensor(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}*/
/*
void roundTensor( Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		roundTensor(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}*/

/*
void reciprocal( Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		reciprocal(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}*/

/*
void sqrt_tensor( Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C)
{
#pragma max_concurrency 1
	for (int d = 0; d < depA; d++)
	{
		sqrt_tensor(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA, get_layer(C, rowsA, colsA, depA, d));
	}
}*/