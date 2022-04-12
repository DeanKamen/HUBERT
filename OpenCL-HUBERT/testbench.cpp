//testbench.cpp, created by Hunter Messner for the HUBERT project
#include "HLS/hls.h"
#include "HLS/stdio.h"
#include "tensors.h" 
#include "tensor3d.h" 
#include "tensor_matMul.h"

//testbench and plus example usage.

int bruh[MAX_ROWS*MAX_COLS];
int yuh[MAX_ROWS*MAX_COLS];

typedef int* Tensor;
typedef int* Tensor3d;

int main()
{   
	int tensor1a[] = {1,2,3,4,5,6,7,8,9,10,11,12};
	Tensor tensor1 = tensor1a;
	const int tensor1r = 4;
	const int tensor1c = 3;
	
	//test get()
	assert(get(tensor1, tensor1r, tensor1c, 0, 0) == 1);
	assert(get(tensor1, tensor1r, tensor1c, 3, 2) == 12);

	//test eq()
	int Aa[] = { 1,2,3,4,5,6,7,8,9,10,11,13 };
	int Ba[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	Tensor A = Aa;
	Tensor B = Ba;

	assert(eq(A, tensor1r, tensor1c, tensor1, tensor1r, tensor1c) == false);
	assert(eq(B, tensor1r, tensor1c, tensor1, tensor1r, tensor1c) == true);

	//test set()
	set(A, tensor1r, tensor1c, 3, 2, 12);
	assert(eq(A, tensor1r, tensor1c, tensor1, tensor1r, tensor1c));

	//test matMul
	int tensorMul1a[] = { 1,1,1,2,1,2,1,1,1 };
	Tensor tensorMul1 = tensorMul1a;
	const int tensorMul1r = 3;
	const int tensorMul1c = 3;

	int tensorMulAnswerA[] = { 8,6,8,20,15,20,32,24,32,44,33,44 }; //second matrix 3x3
	Tensor tensorMulAnswer = tensorMulAnswerA;
	const int tensorMulAnswerr = 4;
	const int tensorMulAnswerc = 3;

	int tensor1spaceA[] = { 0,0,0,0,0,0,0,0,0,0,0,0 }; //result matrix space
	Tensor tensor1space = tensor1spaceA;
	const int tensor1spacer = 4;
	const int tensor1spacec = 3;

	matMul<tensor1r, tensor1c, tensorMul1r, tensorMul1c>(tensor1, tensorMul1, tensor1space);
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, tensorMulAnswer, tensorMulAnswerr, tensorMulAnswerc));

	//test matMul_transposeB
	//like matmul, except we assume B needs to be transposed before multiplication.
	int tensorMulAnswerB[] = { 6,10,6,15,25,15,24,40,24,33,55,33 }; //second matrix 3x3
	tensorMulAnswer = tensorMulAnswerB;
	matMul_transposeB<tensor1r, tensor1c, tensorMul1r, tensorMul1c>(tensor1, tensorMul1, tensor1space);
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, tensorMulAnswer, tensorMulAnswerr, tensorMulAnswerc));

	//test add and subtract, basic
	int onesTwos[] = {1,1,1,2,2,2,1,1,1,2,2,2};
	const int oneTwosr = 4;
	const int oneTwosc = 3;

	add(onesTwos, oneTwosr, oneTwosc, tensor1, tensor1r, tensor1c, tensor1space);
	int answerAdd[] = { 2,3,4,6,7,8,8,9,10,12,13,14 };
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, (Tensor)answerAdd, tensor1spacer, tensor1spacec));

	sub(tensor1space, tensor1r, tensor1c, onesTwos, oneTwosr, oneTwosc, tensor1space);
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, tensor1, tensor1spacer, tensor1spacec));

	//test add and subtract, broadcasting
	int ones[] = { 1,1,2 };
	int twos[] = { 2,2,1,1 };
	add(ones, 1, 3, tensor1, tensor1r, tensor1c, tensor1space);
	int answerAdd2[] = { 2,3,5,5,6,8,8,9,11,11,12,14 };
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, (Tensor)answerAdd2, tensor1spacer, tensor1spacec));
	
	sub(twos, 4, 1, tensor1, tensor1r, tensor1c, tensor1space);
	int answerSub[] = { -1,0,1,2,3,4,6,7,8,9,10,11 };
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, (Tensor)answerSub, tensor1spacer, tensor1spacec));

	//test mul, div, pow. They use basically same code as add and subtract so it should be fine.
	mul_dot(ones, 1, 3, tensor1, tensor1r, tensor1c, tensor1space);
	int answerMul[] = { 1,2,6,4,5,12,7,8,18,10,11,24 };
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, (Tensor)answerMul, tensor1spacer, tensor1spacec));

	div_dot(tensor1space, tensor1r, tensor1c, ones, 1, 3, tensor1space); //order shouldnt matter. Sub and Div where order matters behave wierldly. Larger matrix is always on left
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, tensor1, tensor1spacer, tensor1spacec));
			//element wise test
	pow_dot(tensor1, tensor1r, tensor1c, twos, 1, 1, tensor1space); //here I lie about the size of twos, to make it think I want element wise power
	int answerPow[] = { 1,4,9,16,25,36,49,64,81,100,121,144 };
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, (Tensor)answerPow, tensor1spacer, tensor1spacec));

	// max/min/sum test 
	//WARNING: the result needs to be put in a properly size space. If the space is too big, the program should default to the first n elements in the array.
	max(tensor1, tensor1r, tensor1c, 0, tensor1space); //dim 0, I want the biggest in each col
	int answerMax[] = {10, 11, 12};
	assert(eq(tensor1space, 1, 3, (Tensor)answerMax, 1, 3));
	
	max(tensor1, tensor1r, tensor1c, 1, tensor1space); //dim 1, I want the biggest in each row
	int answerMax2[] = { 3, 6, 9, 12 };
	assert(eq(tensor1space, 4, 1, (Tensor)answerMax2, 4, 1));

	min(tensor1, tensor1r, tensor1c, 0, tensor1space); //dim 0, I want the smallest in each col
	int answerMin[] = { 1, 2, 3 };
	assert(eq(tensor1space, 1, 3, (Tensor)answerMin, 1, 3));

	min(tensor1, tensor1r, tensor1c, 1, tensor1space); //dim 1, I want the smallest in each row
	int answerMin2[] = { 1, 4, 7, 10 };
	assert(eq(tensor1space, 4, 1, (Tensor)answerMin2, 4, 1));

	sum(tensor1, tensor1r, tensor1c, 0, tensor1space); //dim 0, I want the sum in each col
	int answerSum[] = { 22, 26, 30 };
	assert(eq(tensor1space, 1, 3, (Tensor)answerSum, 1, 3));

	sum(tensor1, tensor1r, tensor1c, 1, tensor1space); //dim 1, I want the sum in each row
	int answerSum2[] = { 6, 15, 24, 33 };
	assert(eq(tensor1space, 4, 1, (Tensor)answerSum2, 4, 1));

	//(max/min)_scalar test. Similar to clamp
	min_scalar(tensor1, tensor1r, tensor1c, 5.9, tensor1space);
	int answerMinS[] = { 1,2,3,4,5,5.9,5.9 ,5.9 ,5.9 ,5.9 ,5.9 ,5.9 };
	assert(eq(tensor1space, tensor1r, tensor1c, (Tensor)answerMinS, tensor1r, tensor1c));

	max_scalar(tensor1, tensor1r, tensor1c, 5.9, tensor1space);
	int answerMaxS[] = { 5.9,5.9 ,5.9 ,5.9 ,5.9 ,6,7,8,9,10,11,12 };
	assert(eq(tensor1space, tensor1r, tensor1c, (Tensor)answerMaxS, tensor1r, tensor1c));

	//min_dot test
	int dotInput[] = { 0,0,0,0,0,0,99,99,99,99,99,99 };
	min_dot(tensor1, tensor1r, tensor1c, dotInput, tensor1space);
	int answerMinD[] = { 0,0,0,0,0,0,7,8,9,10,11,12 };
	assert(eq(tensor1space, tensor1r, tensor1c, (Tensor)answerMinD, tensor1r, tensor1c));

	//abs tensor, floor_tensor, exp2_tensor
	mul_scalar(tensor1, tensor1r, tensor1c, -1, tensor1space);
	abs_tensor(tensor1space, tensor1r, tensor1c, tensor1space);
	assert(eq(tensor1space, tensor1r, tensor1c, tensor1, tensor1r, tensor1c));

	mul_scalar(tensor1, tensor1r, tensor1c, 1.01, tensor1space);
	floor_tensor(tensor1space, tensor1r, tensor1c, tensor1space);
	assert(eq(tensor1space, tensor1r, tensor1c, tensor1, tensor1r, tensor1c));

	exp2_tensor(tensor1, tensor1r, tensor1c, tensor1space); //2^n
	int answerExp[] = {2,4,8,16,32,64,128,256,512,1024,2048,4096};
	assert(eq(tensor1space, tensor1r, tensor1c, answerExp, tensor1r, tensor1c));

	// test clamp, round, reciprocal.
	clamp(tensor1, tensor1r, tensor1c, 3.5, 9.5, tensor1space);
	int answerClamp[] = { 3.5,3.5,3.5, 4, 5, 6, 7, 8, 9, 9.5, 9.5, 9.5 };
	assert(eq(tensor1space, tensor1r, tensor1c, answerClamp, tensor1r, tensor1c));

	mul_scalar(tensor1, tensor1r, tensor1c, 1.01, tensor1space);
	roundTensor(tensor1space, tensor1r, tensor1c, tensor1space);
	assert(eq(tensor1space, tensor1r, tensor1c, tensor1, tensor1r, tensor1c));

	reciprocal(tensor1, tensor1r, tensor1c, tensor1space);
	int answerRecip[] = { 1/1, 1/2.0, 1/3.0, 1/4.0, 1/5.0, 1 / 6.0 , 1 / 7.0 , 1 / 8.0 , 1 / 9.0 , 1 / 10.0 , 1 / 11.0 , 1 / 12.0 };
	assert(eq(tensor1space, tensor1r, tensor1c, answerRecip, tensor1r, tensor1c));

	//sign, mean, sqrt test/example
	int mul_half[] = { -1,1,1 };
	mul_dot(tensor1, tensor1r, tensor1c, mul_half,1,3, tensor1space);
	sign(tensor1space, tensor1r, tensor1c, tensor1space);
	int answerSign[] = {-1,1,1,-1,1,1 ,-1,1,1 ,-1,1,1 }; 
	assert(eq(tensor1space, tensor1r, tensor1c, (Tensor)answerSign, tensor1r, tensor1c));

	//Warning: Mean assumes a row vector
	int oneByone[] = { 0 };
	mean(tensor1, 1, 12, oneByone);
	int answerMean = 6.5;
	assert(eq(oneByone, 1, 1, &answerMean, 1, 1));

	sqrt_tensor(answerPow, tensor1r, tensor1c, tensor1space);
	assert(eq(tensor1space, tensor1r, tensor1c, tensor1, tensor1r, tensor1c));

	//fill test
	fill(tensor1space, 4, 3, 9);
	int answerFill[] = {9,9,9,9,9,9,9,9,9,9,9,9};
	assert(eq(tensor1space, tensor1r, tensor1c, (Tensor)answerFill, tensor1r, tensor1c));

	//skipping frexp

	/****************************************************************3d section***********************************************************************/
	int A3d[] = {1,2,3,4,5,6,6,5,4,3,2,1}; //Two layers for most tests
	const int Arows = 3;
	const int Acols = 2;
	const int Adep = 2;

	int B3d_ol[] = { 1,1,1,2,1,1,1 };
	const int rowsB = 3;
	const int colsB = 2;

	int B3d_ol_t[] = { 1,1,1, 1,2,1};

	int B3d[] = { 1,1,1,1,2,1,1,2,1,1,1,1 };
	const int Brows = 2;
	const int Bcols = 3;
	const int Bdep = 2;

	int B3d_t[] = { 1,1,1,2,1,1,1,1,2,1,1,1 };
	const int Brows_t = 3;
	const int Bcols_t = 2;
	const int Bdep_t = 2;

	int Cspace[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	const int Crows = 3;
	const int Ccols = 3;
	const int Cdep = 2;

	//get test
	int el = get(A3d, Arows, Acols, Adep, 2,1,0);
	int el2 = get(A3d, Arows, Acols, Adep, 2, 1, 1);
	assert(el == 6 && el2 == 1);

	//get_layer test
	Tensor layer1 = get_layer(A3d, Arows, Acols, Adep, 0);
	Tensor layer2 = get_layer(A3d, Arows, Acols, Adep, 1);
	int answerLayer1[] = { 1,2,3,4,5,6 };
	int answerLayer2[] = { 6,5,4,3,2,1 };
	assert(eq(layer1, Arows, Acols, answerLayer1, Arows, Acols));
	assert(eq(layer2, Arows, Acols, answerLayer2, Arows, Acols));

	//set test
	set(A3d, Arows, Acols, Adep, 2, 1, 1, 10);
	assert(get(A3d, Arows, Acols, Adep, 2, 1, 1) == 10);

	set(A3d, Arows, Acols, Adep, 1, answerLayer2);
	assert(eq(get_layer(A3d, Arows, Acols, Adep, 1), Arows, Acols, (Tensor)answerLayer2, Arows, Acols));

	//linear mul, bmm, bmm2 test
	//linear mul assumes the multiplicand is NOT transposed. 
	linear_mul<Arows, Acols, Adep, rowsB, colsB>(A3d, B3d_ol, Cspace); //only take the first layer of B for this one.
	int answerLinear[] = {3,5,3,7,11,7,11,17,11,11,16,11,7,10,7,3,4,3};
	assert(eq(Cspace, Crows, Ccols, Cdep, (Tensor)answerLinear, Crows, Ccols, Cdep));

	//bmm
	bmm<Arows, Acols, Adep, Brows_t, Bcols_t, Bdep_t>(A3d, B3d_t, Cspace);
	int answerBmm[] = { 3,5,3,7,11,7,11,17,11,11,17,11,7,11,7,3,5,3 };
	assert(eq(Cspace, Crows, Ccols, Cdep, (Tensor)answerBmm, Crows, Ccols, Cdep));

	//bmm2
	bmm2<Arows, Acols, Adep, Brows, Bcols, Bdep>(A3d, B3d, Cspace);
	int answerBmm2[] = { 3,5,3,7,11,7,11,17,11,11,17,11,7,11,7,3,5,3 };
	assert(eq(Cspace, Crows, Ccols, Cdep, (Tensor)answerBmm2, Crows, Ccols, Cdep));

	//test add, subtract, multiply, divide, pow
	int onesTwos3d[] = { 1,2,1,2,1,2,1,2,1,2,1,2 };
	const int oneTwos3dr = 3;
	const int oneTwos3dc = 2;
	const int oneTwos3dd = 2;


	int spaceOut[] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	const int spaceOutr = 3;
	const int spaceOutc = 2;
	const int spaceOutd = 2;

	add(A3d, Arows, Acols, Adep, onesTwos3d, oneTwos3dr, oneTwos3dc, oneTwos3dd, spaceOut);
	int answerAdd3[] = { 2, 4, 4, 6, 6, 8, 7, 7, 5, 5, 3, 3 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)answerAdd3, spaceOutr, spaceOutc, spaceOutd));

	add(A3d, Arows, Acols, Adep, onesTwos3d, oneTwos3dr, oneTwos3dc, spaceOut);
	int answerAdd32[] = { 2, 4, 4, 6, 6, 8, 7, 7, 5, 5, 3, 3 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)answerAdd32, spaceOutr, spaceOutc, spaceOutd));

	add_scalar(A3d, Arows, Acols, Adep, 1, spaceOut);
	int answerAddS[] = { 2,3,4,5,6,7,7,6,5,4,3,2 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)answerAddS, spaceOutr, spaceOutc, spaceOutd));

	sub(A3d, Arows, Acols, Adep, onesTwos3d, oneTwos3dr, oneTwos3dc, oneTwos3dd, spaceOut);
	int answerSub3[] = { 0, 0, 2, 2, 4, 4, 5, 3, 3, 1, 1, -1 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)answerSub3, spaceOutr, spaceOutc, spaceOutd));

	sub(A3d, Arows, Acols, Adep, onesTwos3d, oneTwos3dr, oneTwos3dc, spaceOut);
	int answerSub32[] = { 0, 0, 2, 2, 4, 4, 5, 3, 3, 1, 1, -1 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)answerSub32, spaceOutr, spaceOutc, spaceOutd));

	sub_scalar(A3d, Arows, Acols, Adep, 1, spaceOut);
	int answerSubS[] = { 0,1,2,3,4,5,5,4,3,2,1,0 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)answerSubS, spaceOutr, spaceOutc, spaceOutd));

	mul_dot(A3d, Arows, Acols, Adep, onesTwos3d, oneTwos3dr, oneTwos3dc, oneTwos3dd, spaceOut);
	int answerMul3[] = { 1, 4, 3, 8, 5, 12, 6, 10, 4, 6, 2, 2 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)answerMul3, spaceOutr, spaceOutc, spaceOutd));

	mul_dot(A3d, Arows, Acols, Adep, onesTwos3d, oneTwos3dr, oneTwos3dc, spaceOut);
	int answerMul32[] = { 1, 4, 3, 8, 5, 12, 6, 10, 4, 6, 2, 2 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)answerMul32, spaceOutr, spaceOutc, spaceOutd));

	mul_scalar(A3d, Arows, Acols, Adep, 0, spaceOut);
	int answerMulS[] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)answerMulS, spaceOutr, spaceOutc, spaceOutd));

	div_dot(A3d, Arows, Acols, Adep, onesTwos3d, oneTwos3dr, oneTwos3dc, oneTwos3dd, spaceOut);
	int answerDiv3[] = { 1, 1, 3, 2, 5, 3, 6, 2.5, 4, 1.5, 2, 0.5 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)answerDiv3, spaceOutr, spaceOutc, spaceOutd));

	div_dot(A3d, Arows, Acols, Adep, onesTwos3d, oneTwos3dr, oneTwos3dc, spaceOut);
	int answerDiv32[] = { 1, 1, 3, 2, 5, 3, 6, 2.5, 4, 1.5, 2, 0.5 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)answerDiv32, spaceOutr, spaceOutc, spaceOutd));

	div_scalar(A3d, Arows, Acols, Adep, 1, spaceOut);
	int answerDivS[] = { 1,2,3,4,5,6,6,5,4,3,2,1 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)answerDivS, spaceOutr, spaceOutc, spaceOutd));

	pow_dot(A3d, Arows, Acols, Adep, onesTwos3d, oneTwos3dr, oneTwos3dc, oneTwos3dd, spaceOut);
	int answerPow3[] = { 1, 4, 3, 16, 5, 36, 6, 25, 4, 9, 2, 1 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)answerPow3, spaceOutr, spaceOutc, spaceOutd));

	pow_dot(A3d, Arows, Acols, Adep, onesTwos3d, oneTwos3dr, oneTwos3dc, spaceOut);
	int answerPow32[] = { 1, 4, 3, 16, 5, 36, 6, 25, 4, 9, 2, 1 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)answerPow32, spaceOutr, spaceOutc, spaceOutd));

	pow_scalar(A3d, Arows, Acols, Adep, 0, spaceOut);
	int answerPowS[] = { 1,1,1,1,1,1,1,1,1,1,1,1 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)answerPowS, spaceOutr, spaceOutc, spaceOutd));
	
	//copy test
	copy(A3d, Arows, Acols, Adep, spaceOut);
	assert(eq(A3d, Arows, Acols, Adep, (Tensor)spaceOut, Arows, Acols, Adep));

	//Min, max 3d tests
	//Even though, in these functions, we shouldnt need a big result space, it needs to be at least as big as the input. You can always collapse it later.
	max(A3d, Arows, Acols, Adep, 0, spaceOut); //We collapse dimention 0, rows, to 1
	int answerMaxd0[] = {5,6,6,5};
	assert(eq(spaceOut, 1, spaceOutc, spaceOutd, (Tensor)answerMaxd0, 1, spaceOutc, spaceOutd));

	max(A3d, Arows, Acols, Adep, 1, spaceOut); //We collapse dimention 2, cols, to 1
	int answerMaxd1[] = { 2,4,6,6,4,2 };
	assert(eq(spaceOut, spaceOutr, 1, spaceOutd, (Tensor)answerMaxd1, spaceOutr, 1, spaceOutd));

	max(A3d, Arows, Acols, Adep, 2, spaceOut); //We collapse dimention 2, depth, to 1
	int answerMaxd2[] = { 6,5,4,4,5,6 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, 1, (Tensor)answerMaxd2, spaceOutr, spaceOutc, 1));

	copy(A3d, Arows, Acols, Adep, spaceOut);
	max(spaceOut, Arows, Acols, Adep); //matrix fully collapses to a single value
	int answerFullMax[] = { 6 };
	assert(eq(spaceOut, 1, 1, 1, (Tensor)answerFullMax, 1, 1, 1));

	min(A3d, Arows, Acols, Adep, 0, spaceOut); //We collapse dimention 0, rows, to 1
	int answerMind0[] = { 1,2,2,1 };
	assert(eq(spaceOut, 1, spaceOutc, spaceOutd, (Tensor)answerMind0, 1, spaceOutc, spaceOutd));

	min(A3d, Arows, Acols, Adep, 1, spaceOut); //We collapse dimention 1, cols, to 1
	int answerMind1[] = { 1,3,5,5,3,1 };
	assert(eq(spaceOut, spaceOutr, 1, spaceOutd, (Tensor)answerMind1, spaceOutr, 1, spaceOutd));

	min(A3d, Arows, Acols, Adep, 2, spaceOut); //We collapse dimention 2, depth, to 1
	int answerMind2[] = { 1,2,3,3,2,1 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, 1, (Tensor)answerMind2, spaceOutr, spaceOutc, 1));

	copy(A3d, Arows, Acols, Adep, spaceOut);
	min(spaceOut, Arows, Acols, Adep); //matrix fully collapses to a single value
	int answerFullMin[] = { 1 };
	assert(eq(spaceOut, 1, 1, 1, (Tensor)answerFullMin, 1, 1, 1));
	
	max_scalar(A3d, Arows, Acols, Adep, 3, spaceOut);
	int ansMaxScalar[] = {3,3,3,4,5,6,6,5,4,3,3,3};
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)ansMaxScalar, spaceOutr, spaceOutc, spaceOutd));

	min_scalar(A3d, Arows, Acols, Adep, 3, spaceOut);
	int ansMinScalar[] = { 1,2,3,3,3,3,3,3,3,3,2,1 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)ansMinScalar, spaceOutr, spaceOutc, spaceOutd));

	int broadcastB[] = { 6,5,4,3,2,1 }; 
	min_dot(A3d, Arows, Acols, Adep, broadcastB,spaceOut);
	int ansMinDot[] = { 1,2,3,3,2,1,6,5,4,3,2,1 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)ansMinDot, spaceOutr, spaceOutc, spaceOutd));

	//abs, floor, ans exp2 tests
	mul_scalar(A3d, Arows, Acols, Adep, -1, spaceOut);
	abs_tensor(spaceOut, Arows, Acols, Adep, spaceOut);
	int ansAbs[] = { 1,2,3,4,5,6,6,5,4,3,2,1 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)ansAbs, spaceOutr, spaceOutc, spaceOutd));

	mul_scalar(A3d, Arows, Acols, Adep, 1.01, spaceOut);
	floor_tensor(spaceOut, Arows, Acols, Adep, spaceOut);
	int ansFloor[] = { 1,2,3,4,5,6,6,5,4,3,2,1 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)ansFloor, spaceOutr, spaceOutc, spaceOutd));

	exp2_tensor(A3d, Arows, Acols, Adep, spaceOut); //2^A
	int ansExp2[] = { 2,4,8,16,32,64,64,32,16,8,4,2 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)ansExp2, spaceOutr, spaceOutc, spaceOutd));

	//clamp and round
	clamp(A3d, Arows, Acols, Adep, 3, 4, spaceOut);
	int ansClamp[] = { 3,3,3,4,4,4,4,4,4,3,3,3 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)ansClamp, spaceOutr, spaceOutc, spaceOutd));

	mul_scalar(A3d, Arows, Acols, Adep, 1.01, spaceOut);
	roundTensor(spaceOut, Arows, Acols, Adep, spaceOut);
	int ansRound[] = { 1,2,3,4,5,6,6,5,4,3,2,1 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)ansRound, spaceOutr, spaceOutc, spaceOutd));

	//recip, sign, and sqrt
	reciprocal(A3d, Arows, Acols, Adep, spaceOut);
	int ansReciprocal[] = { 1/1.0f,1/2.0f,1/3.0f,1/4.0f,1/5.0f,1/6.0f,1/6.0f,1/5.0f,1/4.0f,1/3.0f,1/2.0f,1/1.0f };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)ansReciprocal, spaceOutr, spaceOutc, spaceOutd));
	
	copy(A3d, Arows, Acols, Adep, spaceOut);
	set(spaceOut, Arows, Acols, Adep, 2, 1, 0, -6);
	sign(spaceOut, Arows, Acols, Adep, spaceOut);
	int ansSign[] = { 1,1,1,1,1,-1,1,1,1,1,1,1 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)ansSign, spaceOutr, spaceOutc, spaceOutd));
	
	int PfectSqrs[] = {4,4,1,9,9,16,16,9,9,1,4,4};
	sqrt_tensor(PfectSqrs, Arows, Acols, Adep, spaceOut);
	int ansSqr[] = { 2,2,1,3,3,4,4,3,3,1,2,2 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, spaceOutd, (Tensor)ansSqr, spaceOutr, spaceOutc, spaceOutd));

	//sum 
	sum(A3d, Arows, Acols, Adep, 0, spaceOut);
	int sumAns1[] = { 9, 12, 12, 9 };
	assert(eq(spaceOut, 1, spaceOutc, spaceOutd, (Tensor)sumAns1, 1, spaceOutc, spaceOutd));
	sum(A3d, Arows, Acols, Adep, 1, spaceOut);
	int sumAns2[] = { 3, 7, 11, 11, 7, 3 };
	assert(eq(spaceOut, spaceOutr, 1, spaceOutd, (Tensor)sumAns2, spaceOutr, 1, spaceOutd));
	sum(A3d, Arows, Acols, Adep, 2, spaceOut);
	int sumAns3[] = { 7, 7, 7, 7, 7, 7 };
	assert(eq(spaceOut, spaceOutr, spaceOutc, 1, (Tensor)sumAns3, spaceOutr, spaceOutc, 1));
	
	//mean
	int rowToAvg[] = { 1,2,3,4,5, 2,3,4,5,6 }; //input must be a row vector
	int meanSpace[] = { 0,0 };
	mean(rowToAvg, 1, 5, 2, meanSpace); //WARNING: matrix's size changes
	int meanAns[] = { 3,4 };
	assert(eq(meanSpace, 1, 1, 2, (Tensor)meanAns, 1, 1, 2));
	
	//large matrix test
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
