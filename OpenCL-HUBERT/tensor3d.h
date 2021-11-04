//tensor3d.h
// 3d HLS tensor implementation for the HUBERT project.
//created by Hunter Messner on 7/19/2021


#ifndef __HUBERT_TENSOR3D_H__
#define __HUBERT_TENSOR3D_H__

#include "tensors.h"

/*                TUNING AND OPTIONS                   */
const unsigned MAX_DEPTH = 22;
typedef float* Tensor3d;

//NOTE: this Tensor3d will store its elements exactly the same as Tensor (2d) but its longer. That is, it is stored layer by layer, row by row


/* FUNCTION DEFINITIONS */
//element to element type (broadcasting)
void add(Tensor3d A, int rowsA, int colsA, int depA, Tensor B, int rowsB, int colsB, Tensor3d C);
void sub(Tensor3d A, int rowsA, int colsA, int depA, Tensor B, int rowsB, int colsB, Tensor3d C);
void mul_dot(Tensor3d A, int rowsA, int colsA, int depA, Tensor B, int rowsB, int colsB, Tensor3d C);
void div_dot(Tensor3d A, int rowsA, int colsA, int depA, Tensor B, int rowsB, int colsB, Tensor3d C);
void pow_dot(Tensor3d A, int rowsA, int colsA, int depA, Tensor B, int rowsB, int colsB, Tensor3d C);
//3d and 3d
void add(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d B, int rowsB, int colsB, int depB, Tensor3d C);
void sub(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d B, int rowsB, int colsB, int depB, Tensor3d C);
void mul_dot(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d B, int rowsB, int colsB, int depB, Tensor3d C);
void div_dot(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d B, int rowsB, int colsB, int depB, Tensor3d C);
void pow_dot(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d B, int rowsB, int colsB, int depB, Tensor3d C);

//scalar type
void add_scalar(Tensor3d A, int rowsA, int colsA, int depA, float B, Tensor3d C);
void mul_scalar(Tensor3d A, int rowsA, int colsA, int depA, float B, Tensor3d C);
void sub_scalar(Tensor3d A, int rowsA, int colsA, int depA, float B, Tensor3d C);
void sub_scalar(float B, Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C);
void div_scalar(Tensor3d A, int rowsA, int colsA, int depA, float B, Tensor3d C);
void pow_scalar(Tensor3d A, int rowsA, int colsA, int depA, float B, Tensor3d C);
void max(Tensor3d A, int rowsA, int colsA, int depA, int dim, Tensor3d C); //WARNING: matrix's size changes, along one dimention
void min(Tensor3d A, int rowsA, int colsA, int depA, int dim, Tensor3d C); //WARNING: matrix's size changes
void max(Tensor3d A, int rowsA, int colsA, int depA); //WARNING: matrix's size changes to 1x1
void min(Tensor3d A, int rowsA, int colsA, int depA);//WARNING: matrix's size changes to 1x1
void max_scalar(Tensor3d A, int rowsA, int colsA, int depA, float compare, Tensor3d C);
void min_scalar(Tensor3d A, int rowsA, int colsA, int depA, float compare, Tensor3d C);
void min_dot(Tensor3d A, int rowsA, int colsA, int depA, Tensor B, Tensor3d C);
void abs_tensor(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C);
void floor_tensor(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C);
void exp2_tensor(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C);
void clamp(Tensor3d A, int rowsA, int colsA, int depA, float min, float max, Tensor3d C);
void roundTensor(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C);
void reciprocal(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C);
void sum(Tensor3d A, int rowsA, int colsA, int depA, int dim, Tensor3d C);
void sign(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C);
void mean(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C); //WARNING: matrix's size changes
void sqrt_tensor(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C);

//adressing methods where dep is depth and select the 2d array you want.
float get(Tensor3d A, int rowsA, int colsA, int depA, int row, int col, int dep);
void set(Tensor3d A, int rowsA, int colsA, int depA, int row, int col, int dep, float val);
Tensor get_layer(Tensor3d A, int rowsA, int colsA, int depA, int dep); //returns a 2d pointer to a part of this matrix
void set(Tensor3d A, int rowsA, int colsA, int depA, int dep, Tensor slice); //copies the elements of a 2d pointer into a section of the matrix
void toTwoD(Tensor3d A, int rowsA, int colsA, int depA, Tensor C);//takes a tensor that is YxZx1, Yx1xZ, or 1xYxZ and returns the 2d matrix
void append(Tensor3d A, int rowsA, int colsA, Tensor slice); //sets the first layer to be the elements of a 2d matrix 

//helper functions
void print(Tensor3d A, int rowsA, int colsA, int depA);
void print_brief(Tensor3d A, int rowsA, int colsA, int depA);
void copy(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C);
void shrinkTensor(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d C, int rowsC, int colsC, int depC);
bool eq(Tensor3d A, int rowsA, int colsA, int depA, Tensor3d B, int rowsB, int colsB, int depB);


#endif