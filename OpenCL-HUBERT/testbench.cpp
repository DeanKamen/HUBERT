//testbench.cpp, created by Hunter Messner for the HUBERT project
#include "HLS/hls.h"
#include "HLS/stdio.h"
#include "tensors.h" 
#include "tensor3d.h" 
#include "tensor_matMul.h"

//testbench and plus example usage.
int main()
{   
	float tensor1a[] = {1,2,3,4,5,6,7,8,9,10,11,12};
	Tensor tensor1 = tensor1a;
	const int tensor1r = 4;
	const int tensor1c = 3;
	
	//test get()
	assert(get(tensor1, tensor1r, tensor1c, 0, 0) == 1);
	assert(get(tensor1, tensor1r, tensor1c, 3, 2) == 12);

	//test eq()
	float Aa[] = { 1,2,3,4,5,6,7,8,9,10,11,13 };
	float Ba[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	Tensor A = Aa;
	Tensor B = Ba;

	assert(eq(A, tensor1r, tensor1c, tensor1, tensor1r, tensor1c) == false);
	assert(eq(B, tensor1r, tensor1c, tensor1, tensor1r, tensor1c) == true);

	//test set()
	set(A, tensor1r, tensor1c, 3, 2, 12);
	assert(eq(A, tensor1r, tensor1c, tensor1, tensor1r, tensor1c));

	//test matMul
	float tensorMul1a[] = { 1,1,1,2,1,2,1,1,1 };//first matrix, 4x3
	Tensor tensorMul1 = tensorMul1a;
	const int tensorMul1r = 3;
	const int tensorMul1c = 3;

	float tensorMulAnswerA[] = { 8,6,8,20,15,20,32,24,32,44,33,44 }; //second matrix 3x3
	Tensor tensorMulAnswer = tensorMulAnswerA;
	const int tensorMulAnswerr = 4;
	const int tensorMulAnswerc = 3;

	float tensor1spaceA[] = { 0,0,0,0,0,0,0,0,0,0,0,0 }; //result matrix space
	Tensor tensor1space = tensor1spaceA;
	const int tensor1spacer = 4;
	const int tensor1spacec = 3;

	matMul<tensor1r, tensor1c, tensorMul1r, tensorMul1c>(tensor1, tensorMul1, tensor1space);
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, tensorMulAnswer, tensorMulAnswerr, tensorMulAnswerc));

	//test matMul_transposeB
	//like matmul, except we assume B needs to be transposed before multiplication.
	float tensorMulAnswerB[] = { 6,10,6,15,25,15,24,40,24,33,55,33 }; //second matrix 3x3
	tensorMulAnswer = tensorMulAnswerB;
	matMul_transposeB<tensor1r, tensor1c, tensorMul1r, tensorMul1c>(tensor1, tensorMul1, tensor1space);
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, tensorMulAnswer, tensorMulAnswerr, tensorMulAnswerc));

	//test add and subtract, basic
	float onesTwos[] = {1,1,1,2,2,2,1,1,1,2,2,2};
	const int oneTwosr = 4;
	const int oneTwosc = 3;

	add(onesTwos, oneTwosr, oneTwosc, tensor1, tensor1r, tensor1c, tensor1space);
	float answerAdd[] = { 2,3,4,6,7,8,8,9,10,12,13,14 };
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, (Tensor)answerAdd, tensor1spacer, tensor1spacec));

	sub(tensor1space, tensor1r, tensor1c, onesTwos, oneTwosr, oneTwosc, tensor1space);
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, tensor1, tensor1spacer, tensor1spacec));

	//test add and subtract, broadcasting
	float ones[] = { 1,1,2 };
	float twos[] = { 2,2,1,1 };
	add(ones, 1, 3, tensor1, tensor1r, tensor1c, tensor1space);
	float answerAdd2[] = { 2,3,5,5,6,8,8,9,11,11,12,14 };
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, (Tensor)answerAdd2, tensor1spacer, tensor1spacec));
	
	sub(twos, 4, 1, tensor1, tensor1r, tensor1c, tensor1space);
	float answerSub[] = { -1,0,1,2,3,4,6,7,8,9,10,11 };
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, (Tensor)answerSub, tensor1spacer, tensor1spacec));

	//test mul, div, pow. They use basically same code as add and subtract so it should be fine.
	mul_dot(ones, 1, 3, tensor1, tensor1r, tensor1c, tensor1space);
	float answerMul[] = { 1,2,6,4,5,12,7,8,18,10,11,24 };
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, (Tensor)answerMul, tensor1spacer, tensor1spacec));

	div_dot(tensor1space, tensor1r, tensor1c, ones, 1, 3, tensor1space); //order shouldnt matter. Sub and Div where order matters behave wierldly. Larger matrix is always on left
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, tensor1, tensor1spacer, tensor1spacec));
			//element wise test
	pow_dot(tensor1, tensor1r, tensor1c, twos, 1, 1, tensor1space); //here I lie about the size of twos, to make it think I want element wise power
	float answerPow[] = { 1,4,9,16,25,36,49,64,81,100,121,144 };
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, (Tensor)answerPow, tensor1spacer, tensor1spacec));

	// max/min/sum test 
	//WARNING: the result needs to be put in a properly size space. If the space is too big, the program should default to the first n elements in the array.
	max(tensor1, tensor1r, tensor1c, 0, tensor1space); //dim 0, I want the biggest in each col
	float answerMax[] = {10, 11, 12};
	assert(eq(tensor1space, 1, 3, (Tensor)answerMax, 1, 3));
	
	max(tensor1, tensor1r, tensor1c, 1, tensor1space); //dim 1, I want the biggest in each row
	float answerMax2[] = { 3, 6, 9, 12 };
	assert(eq(tensor1space, 4, 1, (Tensor)answerMax2, 4, 1));

	min(tensor1, tensor1r, tensor1c, 0, tensor1space); //dim 0, I want the smallest in each col
	float answerMin[] = { 1, 2, 3 };
	assert(eq(tensor1space, 1, 3, (Tensor)answerMin, 1, 3));

	min(tensor1, tensor1r, tensor1c, 1, tensor1space); //dim 1, I want the smallest in each row
	float answerMin2[] = { 1, 4, 7, 10 };
	assert(eq(tensor1space, 4, 1, (Tensor)answerMin2, 4, 1));

	sum(tensor1, tensor1r, tensor1c, 0, tensor1space); //dim 0, I want the sum in each col
	float answerSum[] = { 22, 26, 30 };
	assert(eq(tensor1space, 1, 3, (Tensor)answerSum, 1, 3));

	sum(tensor1, tensor1r, tensor1c, 1, tensor1space); //dim 1, I want the sum in each row
	float answerSum2[] = { 6, 15, 24, 33 };
	assert(eq(tensor1space, 4, 1, (Tensor)answerSum2, 4, 1));

	//(max/min)_scalar test. Similar to clamp
	min_scalar(tensor1, tensor1r, tensor1c, 5.9, tensor1space);
	float answerMinS[] = { 1,2,3,4,5,5.9,5.9 ,5.9 ,5.9 ,5.9 ,5.9 ,5.9 };
	assert(eq(tensor1space, tensor1r, tensor1c, (Tensor)answerMinS, tensor1r, tensor1c));

	max_scalar(tensor1, tensor1r, tensor1c, 5.9, tensor1space);
	float answerMaxS[] = { 5.9,5.9 ,5.9 ,5.9 ,5.9 ,6,7,8,9,10,11,12 };
	assert(eq(tensor1space, tensor1r, tensor1c, (Tensor)answerMaxS, tensor1r, tensor1c));

	//min_dot test
	float dotInput[] = { 0,0,0,0,0,0,99,99,99,99,99,99 };
	min_dot(tensor1, tensor1r, tensor1c, dotInput, tensor1space);
	float answerMinD[] = { 0,0,0,0,0,0,7,8,9,10,11,12 };
	assert(eq(tensor1space, tensor1r, tensor1c, (Tensor)answerMinD, tensor1r, tensor1c));

	//abs tensor, floor_tensor, exp2_tensor
	mul_scalar(tensor1, tensor1r, tensor1c, -1, tensor1space);
	abs_tensor(tensor1space, tensor1r, tensor1c, tensor1space);
	assert(eq(tensor1space, tensor1r, tensor1c, tensor1, tensor1r, tensor1c));

	mul_scalar(tensor1, tensor1r, tensor1c, 1.01, tensor1space);
	floor_tensor(tensor1space, tensor1r, tensor1c, tensor1space);
	assert(eq(tensor1space, tensor1r, tensor1c, tensor1, tensor1r, tensor1c));

	exp2_tensor(tensor1, tensor1r, tensor1c, tensor1space); //2^n
	float answerExp[] = {2,4,8,16,32,64,128,256,512,1024,2048,4096};
	assert(eq(tensor1space, tensor1r, tensor1c, answerExp, tensor1r, tensor1c));

	// test clamp, round, reciprocal.
	clamp(tensor1, tensor1r, tensor1c, 3.5, 9.5, tensor1space);
	float answerClamp[] = { 3.5,3.5,3.5, 4, 5, 6, 7, 8, 9, 9.5, 9.5, 9.5 };
	assert(eq(tensor1space, tensor1r, tensor1c, answerClamp, tensor1r, tensor1c));

	mul_scalar(tensor1, tensor1r, tensor1c, 1.01, tensor1space);
	roundTensor(tensor1space, tensor1r, tensor1c, tensor1space);
	assert(eq(tensor1space, tensor1r, tensor1c, tensor1, tensor1r, tensor1c));

	reciprocal(tensor1, tensor1r, tensor1c, tensor1space);
	float answerRecip[] = { 1/1, 1/2.0, 1/3.0, 1/4.0, 1/5.0, 1 / 6.0 , 1 / 7.0 , 1 / 8.0 , 1 / 9.0 , 1 / 10.0 , 1 / 11.0 , 1 / 12.0 };
	assert(eq(tensor1space, tensor1r, tensor1c, answerRecip, tensor1r, tensor1c));

	//sign, mean, sqrt test/example
	float mul_half[] = { -1,1,1 };
	mul_dot(tensor1, tensor1r, tensor1c, mul_half,1,3, tensor1space);
	sign(tensor1space, tensor1r, tensor1c, tensor1space);
	float answerSign[] = {-1,1,1,-1,1,1 ,-1,1,1 ,-1,1,1 }; 
	assert(eq(tensor1space, tensor1r, tensor1c, (Tensor)answerSign, tensor1r, tensor1c));

	//Warning: Mean assumes a row vector
	mean(tensor1, 1, 12, tensor1space);
	float answerMean = 6.5;
	assert(eq(tensor1space, 1, 1, &answerMean, 1, 1));

	sqrt_tensor(answerPow, tensor1r, tensor1c, tensor1space);
	assert(eq(tensor1space, tensor1r, tensor1c, tensor1, tensor1r, tensor1c));

	//fill test
	fill(tensor1space, 4, 3, 9);
	float answerFill[] = {9,9,9,9,9,9,9,9,9,9,9,9};
	assert(eq(tensor1space, tensor1r, tensor1c, (Tensor)answerFill, tensor1r, tensor1c));

	//skipping frexp

	/****************************************************************3d section***********************************************************************/
	float A3d[] = {1,2,3,4,5,6,6,5,4,3,2,1}; //Two layers for most tests
	const int Arows = 3;
	const int Acols = 2;
	const int Adep = 2;

	float B3d_ol[] = { 1,1,1,2,1,1,1 };
	const int rowsB = 3;
	const int colsB = 2;

	float B3d[] = { 1,1,1,1,2,1,1,2,1,1,1,1 };
	const int Brows = 2;
	const int Bcols = 3;
	const int Bdep = 2;

	float Cspace[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	const int Crows = 3;
	const int Ccols = 3;
	const int Cdep = 2;

	//get test
	float el = get(A3d, Arows, Acols, Adep, 2,1,0);
	float el2 = get(A3d, Arows, Acols, Adep, 2, 1, 1);
	assert(el == 6 && el2 == 1);

	//get_layer test
	Tensor layer1 = get_layer(A3d, Arows, Acols, Adep, 0);
	Tensor layer2 = get_layer(A3d, Arows, Acols, Adep, 1);
	float answerLayer1[] = { 1,2,3,4,5,6 };
	float answerLayer2[] = { 6,5,4,3,2,1 };
	assert(eq(layer1, Arows, Acols, answerLayer1, Arows, Acols));
	assert(eq(layer2, Arows, Acols, answerLayer2, Arows, Acols));

	//set test
	set(A3d, Arows, Acols, Adep, 2, 1, 1, 10);
	assert(get(A3d, Arows, Acols, Adep, 2, 1, 1) == 10);

	set(A3d, Arows, Acols, Adep, 1, answerLayer2);
	assert(eq(get_layer(A3d, Arows, Acols, Adep, 1), Arows, Acols, (Tensor)answerLayer2, Arows, Acols));


	matMul_transposeB<Arows, Acols, rowsB, colsB>(get_layer(A3d, Arows, Acols, Adep, 0), B3d_ol, Cspace);


	//linear mul, bmm, bmm2 test
	//linear mul assumes the multiplicant is NOT transposed. 
	linear_mul<Arows, Acols, Adep, rowsB, colsB>(A3d, B3d_ol, Cspace); //only take the first layer of B for this one.
	float answerLinear[] = {3,5,3,7,11,7,11,17,11,11,16,11,7,10,7,3,4,3};
	assert(eq(Cspace, Crows, Ccols, Cdep, (Tensor)answerLinear, Crows, Ccols, Cdep));

	//overflow test
	/*
	float bruh[MAX_ROWS*MAX_COLS];
	float yuh[MAX_ROWS*MAX_COLS];
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
	*/
}
