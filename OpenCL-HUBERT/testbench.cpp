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
	float answerAdd2[] = { 2,3,5,5,6,8,8,9,11,11,12,15 };
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, (Tensor)answerAdd2, tensor1spacer, tensor1spacec));
	
	sub(ones, 4, 1, tensor1, tensor1r, tensor1c, tensor1space);
	float answerSub[] = { 3,4,5,6,7,8,8,9,10,11,12,13 };
	assert(eq(tensor1space, tensor1spacer, tensor1spacec, (Tensor)answerSub, tensor1spacer, tensor1spacec));

	
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
