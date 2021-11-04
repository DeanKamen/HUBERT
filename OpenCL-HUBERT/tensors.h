//tensors.h
//Basic HLS tensor implementation for the HUBERT project.
//created by Hunter Messner on 6/6/2021


#ifndef __HUBERT_TENSORS_H__
#define __HUBERT_TENSORS_H__

/*                TUNING AND OPTIONS                   */
const unsigned MAX_ROWS_SMALL = 64; // based on the max size of numpy arrays in default IBERT (3072)
const unsigned MAX_COLS_SMALL = 64;
const unsigned MAX_ROWS = 3072;
const unsigned MAX_COLS = 3072;
const unsigned STD_ROWS = 768;
const unsigned STD_COLS = 768;

const unsigned UNITS_PER_MULTIPLY= 32; //must be a factor of the MAX_COLS
// for example float t_tensor[MAX_ROWS*MAX_COLS];
static int RETURN_NOTHING = 0;


typedef float* Tensor;
/* FUNCTION DEFINITIONS */
//dot type (broadcasting)
void add(Tensor A, int rowsA, int colsA, Tensor B, int rowsB, int colsB, Tensor C);
void sub(Tensor A, int rowsA, int colsA, Tensor B, int rowsB, int colsB, Tensor C);
void mul_dot(Tensor A, int rowsA, int colsA, Tensor B, int rowsB, int colsB, Tensor C);
void div_dot(Tensor A, int rowsA, int colsA, Tensor B, int rowsB, int colsB, Tensor C);
void pow_dot(Tensor A, int rowsA, int colsA, Tensor B, int rowsB, int colsB, Tensor C);
//scalar type
void add_scalar(Tensor A, int rowsA, int colsA, float B, Tensor C);
void mul_scalar(Tensor A, int rowsA, int colsA, float B, Tensor C);
void sub_scalar(Tensor A, int rowsA, int colsA, float B, Tensor C);
void sub_scalar(float B, Tensor A, int rowsA, int colsA, Tensor C);
void div_scalar(Tensor A, int rowsA, int colsA, float B, Tensor C);
void pow_scalar(Tensor A, int rowsA, int colsA, float B, Tensor C);
void max(Tensor A, int rowsA, int colsA, int dim, Tensor C); //WARNING: matrix's size changes
void min(Tensor A, int rowsA, int colsA, int dim, Tensor C); //WARNING: matrix's size changes
void sum(Tensor A, int rowsA, int colsA, int dim, Tensor C); //WARNING: matrix's size changes
void max_scalar(Tensor A, int rowsA, int colsA, float compare, Tensor C);
void min_scalar(Tensor A, int rowsA, int colsA, float compare, Tensor C);
void min_dot(Tensor A, int rowsA, int colsA, Tensor B, Tensor C); //implied A.size == B.size
void abs_tensor(Tensor A, int rowsA, int colsA, Tensor C);
void floor_tensor(Tensor A, int rowsA, int colsA, Tensor C);
void exp2_tensor(Tensor A, int rowsA, int colsA, Tensor C);
void clamp(Tensor A, int rowsA, int colsA, float min, float max, Tensor C);
void roundTensor(Tensor A, int rowsA, int colsA, Tensor C);
void reciprocal(Tensor A, int rowsA, int colsA, Tensor C);
void sign(Tensor A, int rowsA, int colsA, Tensor C);
void mean(Tensor A, int rowsA, int colsA, Tensor C); //WARNING: matrix's size changes
void sqrt_tensor(Tensor A, int rowsA, int colsA, Tensor C);
//manipulation
void fill(Tensor A, int rowsA, int colsA, float fill);
//void view(Tensor A, int rowsA, int colsA, int rows, int cols, Tensor space);
void tensor_frexp(Tensor In, int rowsIn, int colsIn, Tensor m, int rowsm, int colsm, Tensor e, int rowse, int colse);
//adressing methods
float get(Tensor A, int rowsA, int colsA, int row, int col);
float transposed_get(Tensor A, int rowsA, int colsA, int row, int col);
void set(Tensor A, int rowsA, int colsA, int row, int col, float val);
void transposed_set(Tensor A, int rowsA, int colsA, int row, int col, float val);

//helper functions
void transpose(Tensor A, int rowsA, int colsA, Tensor C);
void copy(Tensor A, int rowsA, int colsA, Tensor C);
void shrinkTensor(Tensor A, int rowsA, int colsA, Tensor C, int rowsC, int colsC); //use this after a dimention has been collapsed
void print(Tensor A, int rowsA, int colsA);
void print_brief(Tensor A, int rowsA, int colsA);
bool eq(Tensor A, int rowsA, int colsA, Tensor B, int rowsB, int colsB);
bool eq_verbose(Tensor A, int rowsA, int colsA, Tensor B, int rowsB, int colsB);

void flopSize(Tensor& lhs, int rowsLHS, int colsLHS, Tensor& rhs, int rowsRHS, int colsRHS);

#endif