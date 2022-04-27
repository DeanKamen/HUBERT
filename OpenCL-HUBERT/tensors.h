//tensors.h
//Basic HLS tensor implementation for the HUBERT project.
//created by Hunter Messner on 6/6/2021


#ifndef __HUBERT_TENSORS_H__
#define __HUBERT_TENSORS_H__

/*                TUNING AND OPTIONS                   */
#define MAX_ROWS_SMALL 64; // based on the max size of numpy arrays in default IBERT (3072)
#define MAX_COLS_SMALL 64;
#define MAX_ROWS 3072;
#define MAX_COLS 3072;
#define STD_ROWS 768;
#define STD_COLS 768;
#define UNITS_PER_MULTIPLY 32; //must be a factor of the MAX_COLS


//TODO: had to delete const for troubleshootin, did not add it back

/* FUNCTION DEFINITIONS */

//TEMPLATES: the tint defines the underlying int type of the tensor (8,12,16 bits).
//When using this, I would do something like
// typedef int gint
// typedef gint* GELU_TENSOR
// add_scalar(GELU_TENSOR A, int rowsA, int colsA, tint B, GELU_TENSOR C) 

//the loc type is the size of the int that identifies the rows and columns. Going unsigned int or int here should be fine. 
//Loc can be shrunk as well but know that there can be up to 3072 rows so you probably need at least 12 bits.

//dot type (broadcasting)
template<typename tint, typename loc> 
void add( tint* A,  loc rowsA,  loc colsA,  tint* B,  loc rowsB,  loc colsB, tint* C);
template<typename tint, typename loc>
void sub( tint* A,  loc rowsA,  loc colsA,  tint* B,  loc rowsB,  loc colsB, tint* C);
template<typename tint, typename loc>
void mul_dot( tint* A,  loc rowsA,  loc colsA,  tint* B,  loc rowsB,  loc colsB, tint* C);
template<typename tint, typename loc>
void div_dot( tint* A,  loc rowsA,  loc colsA,  tint* B,  loc rowsB,  loc colsB, tint* C);
template<typename tint, typename loc>
void pow_dot( tint* A,  loc rowsA,  loc colsA,  tint* B,  loc rowsB,  loc colsB, tint* C);
template<typename tint, typename loc>
void rightShift( tint* A,  loc rowsA,  loc colsA,  tint* B,  loc rowsB,  loc colsB, tint* C);
//scalar type
template<typename tint, typename loc>
void add_scalar( tint* A,  loc rowsA,  loc colsA, tint B, tint* C);
template<typename tint, typename loc>
void mul_scalar( tint* A,  loc rowsA,  loc colsA, tint B, tint* C);
template<typename tint, typename loc>
void sub_scalar( tint* A,  loc rowsA,  loc colsA, tint B, tint* C);
template<typename tint, typename loc>
void sub_scalar(tint B,  tint* A,  loc rowsA,  loc colsA, tint* C);
template<typename tint, typename loc>
void div_scalar( tint* A,  loc rowsA,  loc colsA, tint B, tint* C);
template<typename tint, typename loc>
void pow_scalar( tint* A,  loc rowsA,  loc colsA, tint B, tint* C);
template<typename tint, typename loc>
void max( tint* A,  loc rowsA,  loc colsA, tint dim, tint* C); //WARNING: matrix's size changes
template<typename tint, typename loc>
void min( tint* A,  loc rowsA,  loc colsA, tint dim, tint* C); //WARNING: matrix's size changes
template<typename tint, typename loc>
void sum( tint* A,  loc rowsA,  loc colsA, tint dim, tint* C); //WARNING: matrix's size changes
template<typename tint, typename loc>
void max_scalar( tint* A,  loc rowsA,  loc colsA, tint compare, tint* C);
template<typename tint, typename loc>
void min_scalar( tint* A,  loc rowsA,  loc colsA, tint compare, tint* C);
template<typename tint, typename loc>
void min_dot( tint* A,  loc rowsA,  loc colsA,  tint* B, tint* C); //implied A.size == B.size
template<typename tint, typename loc>
void abs_tensor( tint* A,  loc rowsA,  loc colsA, tint* C);
template<typename tint, typename loc>
void exp2_tensor( tint* A,  loc rowsA,  loc colsA, tint* C);
template<typename tint, typename loc>
void clamp( tint* A,  loc rowsA,  loc colsA, tint min, tint max, tint* C);
template<typename tint, typename loc>
void sign( tint* A,  loc rowsA,  loc colsA, tint* C);
template<typename tint, typename loc>
void mean( tint* A,  loc rowsA,  loc colsA, tint* C); //WARNING: matrix's size changes

//manipulation
template<typename tint, typename loc>
void fill( tint* A,  loc rowsA,  loc colsA, tint fill);

//adressing methods


template<typename tint, typename loc> tint get(tint* A, loc rowsA, loc colsA, loc row, loc col);
template<typename tint, typename loc> tint transposed_get( tint* A,  loc rowsA,  loc colsA, loc row, loc col);

template<typename tint, typename loc> void set(tint* A,  loc rowsA,  loc colsA, loc row, loc col, tint val);
template<typename tint, typename loc> void transposed_set( tint* A,  loc rowsA,  loc colsA, loc row, loc col, tint val);

//helper functions
template<typename tint, typename loc>
void transpose( tint* A,  loc rowsA,  loc colsA, tint* C);
template<typename tint, typename loc>
void copy( tint* A,  loc rowsA,  loc colsA, tint* C);
template<typename tint, typename loc>
void shrinktint( tint* A,  loc rowsA,  loc colsA, tint* C,  loc rowsC,  loc colsC); //use this after a dimention has been collapsed
template<typename tint, typename loc>
void print( tint* A,  loc rowsA,  loc colsA);
template<typename tint, typename loc>
void print_brief( tint* A,  loc rowsA,  loc colsA);
template<typename tint, typename loc>
bool eq( tint* A,  loc rowsA,  loc colsA,  tint* B,  loc rowsB,  loc colsB);
template<typename tint, typename loc>
bool eq_verbose( tint* A,  loc rowsA,  loc colsA,  tint* B,  loc rowsB,  loc colsB);

template<typename tint, typename loc>
void flopSize(tint*& lhs, loc rowsLHS, loc colsLHS, tint*& rhs, loc rowsRHS, loc colsRHS);


//void floor_tensor( Tensor A,  int rowsA,  int colsA, Tensor C); //commented functions like this one assume float inputs, change to FLENSOR when necessary
//void roundTensor( Tensor A,  int rowsA,  int colsA, Tensor C);
//void reciprocal( Tensor A,  int rowsA,  int colsA, Tensor C);
//void reciprocal( Flensor A,  int rowsA,  int colsA, Flensor C);
//void sqrt_tensor( Tensor A,  int rowsA,  int colsA, Tensor C);
//void view( Tensor A,  int rowsA,  int colsA, int rows, int cols, Tensor space);
//void tensor_frexp(Tensor In, int rowsIn, int colsIn, Tensor m, int rowsm, int colsm, Tensor e, int rowse, int colse);
//float get( Tensor A,  int rowsA,  int colsA, int row, int col);
//void set( Tensor A,  int rowsA,  int colsA, int row, int col, float val);
#include "tensors.hpp"
#endif