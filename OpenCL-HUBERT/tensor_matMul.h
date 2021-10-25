//tensor_matMul.h
//templates regarding matrix multiplication for the HUBERT project.
//created by Hunter Messner on 10/22/2021


#ifndef __HUBERT_TENSOR_MATMUL_H__
#define __HUBERT_TENSOR_MATMUL_H__

#include "tensors.h"
#include "tensor3d.h"
#include "matrix_mult.h"
#include "matrix_mult_transpose.h"

/* FUNCTION DEFINITIONS */
template<int rowsA, int colsA, int rowsB, int colsB>
void matMul(Tensor A, Tensor B, Tensor C) //WARNING: matrix's size changes
//this function needs to use MACROS or constants known at compile time for sizes.
//when using multiplies in components, use the below prototype.
{
	matrix_multiply<float, rowsA, colsA, colsB>(A, B, C);
}


template<int rowsA, int colsA, int rowsB, int colsB>
void matMul_transposeB(Tensor A, Tensor B, Tensor C)
//this function needs to use MACROS or constants known at compile time for sizes.
//when using multiplies in components, use the below prototype.
{
	matrix_multiply_transpose<float, rowsA, colsA, rowsB>(A, B, C);
	print(C, rowsA, rowsB);
}

//special multiply
template<int rowsA, int colsA, int depA, int rowsB, int colsB>
void linear_mul(Tensor3d A, Tensor B, Tensor3d C)
{
	for (unsigned d = 0; d < depA; d++)
	{
		matMul_transposeB<rowsA, colsA, rowsB, colsB>(get_layer(A, rowsA, colsA, depA, d), B, get_layer(C, rowsA, rowsB, depA, d));
		print(get_layer(A, rowsA, colsA, depA, d), rowsA, colsA);
		print(B, rowsB, colsB);
		//print(get_layer(C, rowsA, rowsB, depA, d), rowsA, rowsB);
	}
	//the resulting matrix should have cols = colsB, rows = rowsA
}

template<int rowsA, int colsA, int depA, int rowsB, int colsB, int depB>
void bmm(Tensor3d A, Tensor3d B, Tensor3d C)
{ //for when they both have the same size. 
	//We assume B is the same shape as A but compatible to multiply 
	//assuming a 22x64 * 22x64 but we transpose the second input
	//assert(colsA == colsB);
	for (unsigned d = 0; d < depA; d++)
	{
		Tensor rhs = get_layer(B, rowsB, colsB, depB, d);
		matMul_transposeB<rowsA, colsA, colsB, rowsB>(get_layer(A, rowsA, colsA, depA, d), rhs, get_layer(C, rowsA, colsA, depA, d));
	}
}

template<int rowsA, int colsA, int depA, int rowsB, int colsB, int depB>
void bmm2(Tensor3d A, Tensor3d B, Tensor3d C)
{ //for when they both have the same size. 
	//We assume B is already "transposed". Also assuming a 22x22 * 22x64
	//assert(colsA == rowsB);
	for (unsigned d = 0; d < depA; d++)
	{
		matMul<rowsA, colsA, colsB, rowsB>(get_layer(A, rowsA, colsA, depA, d), get_layer(B, rowsB, colsB, depB, d), get_layer(C, rowsA, colsA, depA, d));
	}
}
#endif