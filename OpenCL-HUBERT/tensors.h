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
void add(const Tensor A, const int rowsA, const int colsA, const Tensor B, const int rowsB, const int colsB, Tensor C);
void sub(const Tensor A, const int rowsA, const int colsA, const Tensor B, const int rowsB, const int colsB, Tensor C);
void mul_dot(const Tensor A, const int rowsA, const int colsA, const Tensor B, const int rowsB, const int colsB, Tensor C);
void div_dot(const Tensor A, const int rowsA, const int colsA, const Tensor B, const int rowsB, const int colsB, Tensor C);
void pow_dot(const Tensor A, const int rowsA, const int colsA, const Tensor B, const int rowsB, const int colsB, Tensor C);
//scalar type
void add_scalar(const Tensor A, const int rowsA, const int colsA, float B, Tensor C);
void mul_scalar(const Tensor A, const int rowsA, const int colsA, float B, Tensor C);
void sub_scalar(const Tensor A, const int rowsA, const int colsA, float B, Tensor C);
void sub_scalar(float B, const Tensor A, const int rowsA, const int colsA, Tensor C);
void div_scalar(const Tensor A, const int rowsA, const int colsA, float B, Tensor C);
void pow_scalar(const Tensor A, const int rowsA, const int colsA, float B, Tensor C);
void max(const Tensor A, const int rowsA, const int colsA, int dim, Tensor C); //WARNING: matrix's size changes
void min(const Tensor A, const int rowsA, const int colsA, int dim, Tensor C); //WARNING: matrix's size changes
void sum(const Tensor A, const int rowsA, const int colsA, int dim, Tensor C); //WARNING: matrix's size changes
void max_scalar(const Tensor A, const int rowsA, const int colsA, float compare, Tensor C);
void min_scalar(const Tensor A, const int rowsA, const int colsA, float compare, Tensor C);
void min_dot(const Tensor A, const int rowsA, const int colsA, const Tensor B, Tensor C); //implied A.size == B.size
void abs_tensor(const Tensor A, const int rowsA, const int colsA, Tensor C);
void floor_tensor(const Tensor A, const int rowsA, const int colsA, Tensor C);
void exp2_tensor(const Tensor A, const int rowsA, const int colsA, Tensor C);
void clamp(const Tensor A, const int rowsA, const int colsA, float min, float max, Tensor C);
void roundTensor(const Tensor A, const int rowsA, const int colsA, Tensor C);
void reciprocal(const Tensor A, const int rowsA, const int colsA, Tensor C);
void sign(const Tensor A, const int rowsA, const int colsA, Tensor C);
void mean(const Tensor A, const int rowsA, const int colsA, Tensor C); //WARNING: matrix's size changes
void sqrt_tensor(const Tensor A, const int rowsA, const int colsA, Tensor C);
//manipulation
void fill(const Tensor A, const int rowsA, const int colsA, float fill);
//void view(const Tensor A, const int rowsA, const int colsA, int rows, int cols, Tensor space);
void tensor_frexp(Tensor In, int rowsIn, int colsIn, Tensor m, int rowsm, int colsm, Tensor e, int rowse, int colse);
//adressing methods
float get(const Tensor A, const int rowsA, const int colsA, int row, int col);
float transposed_get(const Tensor A, const int rowsA, const int colsA, int row, int col);
void set(const Tensor A, const int rowsA, const int colsA, int row, int col, float val);
void transposed_set(const Tensor A, const int rowsA, const int colsA, int row, int col, float val);

//helper functions
void transpose(const Tensor A, const int rowsA, const int colsA, Tensor C);
void copy(const Tensor A, const int rowsA, const int colsA, Tensor C);
void shrinkTensor(const Tensor A, const int rowsA, const int colsA, Tensor C, const int rowsC, const int colsC); //use this after a dimention has been collapsed
void print(const Tensor A, const int rowsA, const int colsA);
void print_brief(const Tensor A, const int rowsA, const int colsA);
bool eq(const Tensor A, const int rowsA, const int colsA, const Tensor B, const int rowsB, const int colsB);
bool eq_verbose(const Tensor A, const int rowsA, const int colsA, const Tensor B, const int rowsB, const int colsB);

void flopSize(Tensor& lhs, int rowsLHS, int colsLHS, Tensor& rhs, int rowsRHS, int colsRHS);

#endif