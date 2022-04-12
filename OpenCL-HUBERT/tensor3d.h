//tensor3d.h
// 3d HLS tensor implementation for the HUBERT project.
//created by Hunter Messner on 7/19/2021


#ifndef __HUBERT_TENSOR3D_H__
#define __HUBERT_TENSOR3D_H__

#include "tensors.h"

/*                TUNING AND OPTIONS                   */
const unsigned MAX_DEPTH = 22;
//TODO: for optimization, const might help the HLS compiler

//NOTE: this Tensor3d will store its elements exactly the same as Tensor (2d) but its longer. That is, it is stored layer by layer, row by row
//TEMPLATES: the tint defines the underlying int type of the tensor (8,12,16 bits).

//the loc type is the size of the int that identifies the rows and columns. Going unsigned int or int here should be fine. 
//Loc can be shrunk as well but know that there can be up to 3072 rows so you probably need at least 12 bits.


/* FUNCTION DEFINITIONS */
//element to element type (broadcasting)

//Templating here gets a bit complicated. Since this first block of functions mixes 3d(A) and 2d (B), we want to distinguish those types.
//HOWEVER in normal use they should be the same type. Ex:
// typedef tint* GLEU3d
// typedef tint* GELU2d
template<typename t3d_int, typename tint, typename loc>
void add( t3d_int* A,  loc rowsA,  loc colsA, loc depA, tint* B,  loc rowsB,  loc colsB, t3d_int* C);
template<typename t3d_int, typename tint, typename loc>
void sub( t3d_int* A,  loc rowsA,  loc colsA, loc depA, tint* B,  loc rowsB,  loc colsB, t3d_int* C);
template<typename t3d_int, typename tint, typename loc>
void mul_dot( t3d_int* A,  loc rowsA,  loc colsA, loc depA, tint* B,  loc rowsB,  loc colsB, t3d_int* C);
template<typename t3d_int, typename tint, typename loc>
void div_dot( t3d_int* A,  loc rowsA,  loc colsA, loc depA, tint* B,  loc rowsB,  loc colsB, t3d_int* C);
template<typename t3d_int, typename tint, typename loc>
void pow_dot( t3d_int* A,  loc rowsA,  loc colsA, loc depA, tint* B,  loc rowsB,  loc colsB, t3d_int* C);
//3d and 3d
template<typename t3d_int, typename loc>
void add( t3d_int* A,  loc rowsA,  loc colsA, loc depA,  t3d_int* B,  loc rowsB,  loc colsB, loc depB, t3d_int* C);
template<typename t3d_int, typename loc>
void sub( t3d_int* A,  loc rowsA,  loc colsA, loc depA,  t3d_int* B,  loc rowsB,  loc colsB, loc depB, t3d_int* C);
template<typename t3d_int, typename loc>
void mul_dot( t3d_int* A,  loc rowsA,  loc colsA, loc depA,  t3d_int* B,  loc rowsB,  loc colsB, loc depB, t3d_int* C);
template<typename t3d_int, typename loc>
void div_dot( t3d_int* A,  loc rowsA,  loc colsA, loc depA,  t3d_int* B,  loc rowsB,  loc colsB, loc depB, t3d_int* C);
template<typename t3d_int, typename loc>
void pow_dot( t3d_int* A,  loc rowsA,  loc colsA, loc depA,  t3d_int* B,  loc rowsB,  loc colsB, loc depB, t3d_int* C);
template<typename t3d_int, typename loc>
void rightShift( t3d_int* A,  loc rowsA,  loc colsA, loc depA,  t3d_int* B,  loc rowsB,  loc colsB, loc depB, t3d_int* C);

//scalar type
template<typename t3d_int, typename loc>
void add_scalar( t3d_int* A,  loc rowsA,  loc colsA, loc depA, t3d_int B, t3d_int* C);
template<typename t3d_int, typename loc>
void mul_scalar( t3d_int* A,  loc rowsA,  loc colsA, loc depA, t3d_int B, t3d_int* C);
template<typename t3d_int, typename loc>
void sub_scalar( t3d_int* A,  loc rowsA,  loc colsA, loc depA, t3d_int B, t3d_int* C);
template<typename t3d_int, typename loc>
void sub_scalar(t3d_int B,  t3d_int* A,  loc rowsA,  loc colsA, loc depA, t3d_int* C);
template<typename t3d_int, typename loc>
void div_scalar( t3d_int* A,  loc rowsA,  loc colsA, loc depA, t3d_int B, t3d_int* C);
template<typename t3d_int, typename loc>
void pow_scalar( t3d_int* A,  loc rowsA,  loc colsA, loc depA, t3d_int B, t3d_int* C);
template<typename t3d_int, typename loc>
void max( t3d_int* A,  loc rowsA,  loc colsA, loc depA, int dim, t3d_int* C); //WARNING: matrix's size changes, along one dimention
template<typename t3d_int, typename loc>
void min( t3d_int* A,  loc rowsA,  loc colsA, loc depA, int dim, t3d_int* C); //WARNING: matrix's size changes
template<typename t3d_int, typename loc>
void max( t3d_int* A,  loc rowsA,  loc colsA, loc depA); //WARNING: matrix's size changes to 1x1
template<typename t3d_int, typename loc>
void min( t3d_int* A,  loc rowsA,  loc colsA, loc depA);//WARNING: matrix's size changes to 1x1
template<typename t3d_int, typename loc>
void max_scalar( t3d_int* A,  loc rowsA,  loc colsA, loc depA, t3d_int compare, t3d_int* C);
template<typename t3d_int, typename loc>
void min_scalar( t3d_int* A,  loc rowsA,  loc colsA, loc depA, t3d_int compare, t3d_int* C);
template<typename t3d_int, typename tint, typename loc>
void min_dot( t3d_int* A,  loc rowsA,  loc colsA, loc depA, tint* B, t3d_int* C);
template<typename t3d_int, typename loc>
void abs_tensor( t3d_int* A,  loc rowsA,  loc colsA, loc depA, t3d_int* C);

template<typename t3d_int, typename loc>
void exp2_tensor( t3d_int* A,  loc rowsA,  loc colsA, loc depA, t3d_int* C);
template<typename t3d_int, typename loc>
void clamp( t3d_int* A,  loc rowsA,  loc colsA, loc depA, t3d_int min, t3d_int max, t3d_int* C);
template<typename t3d_int, typename loc>
void sum( t3d_int* A,  loc rowsA,  loc colsA, loc depA, int dim, t3d_int* C);
template<typename t3d_int, typename loc>
void sign( t3d_int* A,  loc rowsA,  loc colsA, loc depA, t3d_int* C);
template<typename t3d_int, typename loc>
void mean( t3d_int* A,  loc rowsA,  loc colsA, loc depA, t3d_int* C); //WARNING: matrix's size changes


//manipulation
template<typename t3d_int, typename loc>
void fill( t3d_int* A,  loc rowsA,  loc colsA, loc depA, t3d_int fillnum);

//adressing methods where dep is depth and select the 2d array you want.
template<typename t3d_int, typename loc>
t3d_int get( t3d_int* A,  loc rowsA,  loc colsA, loc depA, loc row, loc col, loc dep);
template<typename t3d_int, typename loc>
void set( t3d_int* A, loc rowsA, loc colsA, loc depA, loc row, loc col, loc dep, t3d_int val);
template<typename t3d_int, typename loc> //This one does not have a special 2d type.
t3d_int* get_layer( t3d_int* A,  loc rowsA,  loc colsA, loc depA, loc dep); //returns a 2d pointer to a part of this matrix
template<typename t3d_int, typename tint, typename loc>
void set( t3d_int* A,  loc rowsA,  loc colsA, loc depA, loc dep, tint* slice); //copies the elements of a 2d pointer into a section of the matrix
template<typename t3d_int, typename tint, typename loc>
void toTwoD( t3d_int* A,  loc rowsA,  loc colsA, loc depA, tint* C);//takes a tensor that is YxZx1, Yx1xZ, or 1xYxZ and returns the 2d matrix
template<typename t3d_int, typename tint, typename loc>
void append( t3d_int* A,  loc rowsA,  loc colsA, tint* slice); //sets the first layer to be the elements of a 2d matrix 

//helper functions
template<typename t3d_int, typename loc>
void print( t3d_int* A,  loc rowsA,  loc colsA, loc depA);
template<typename t3d_int, typename loc>
void print_brief( t3d_int* A,  loc rowsA,  loc colsA, loc depA);
template<typename t3d_int, typename loc>
void copy( t3d_int* A,  loc rowsA,  loc colsA, loc depA, t3d_int* C);
template<typename t3d_int, typename loc>
void shrinkTensor( t3d_int* A,  loc rowsA,  loc colsA, loc depA, t3d_int* C,  loc rowsC,  loc colsC, loc depC);
template<typename t3d_int, typename loc>
bool eq( t3d_int* A,  loc rowsA,  loc colsA, loc depA,  t3d_int* B,  loc rowsB,  loc colsB, loc depB);

//void floor_tensor(const Tensor3d A, const int rowsA, const int colsA, int depA, Tensor3d C);
//void roundTensor(const Tensor3d A, const int rowsA, const int colsA, int depA, Tensor3d C);
//void reciprocal(const Tensor3d A, const int rowsA, const int colsA, int depA, Tensor3d C);
//void sqrt_tensor(const Tensor3d A, const int rowsA, const int colsA, int depA, Tensor3d C);
#include "tensor3d.hpp"
#endif