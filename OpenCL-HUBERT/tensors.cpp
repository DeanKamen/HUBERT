//tensors.cpp
//Basic HLS tensor implementation for the HUBERT project.
//created by Hunter Messner on 6/6/2021

#include "HLS/hls.h"
#include "HLS/math.h"
#include "HLS/stdio.h"
#include "tensors.h"
#include <iostream>
/*                    DEFINITIONS                      */

//TODO: translate everything to template?

void add(const Tensor A, int rowsA, int colsA, const Tensor B, int rowsB, int colsB, Tensor C) 
//with basic broadcasting
{
	int rowMod;
	int colMod;
	Tensor larger = A; //more rows or cols
	Tensor smaller = B; //one row or one col
	if (rowsA == rowsB && colsA == colsB)
	{//exactly the same size.
		rowMod = rowsA + 1; //these mods do NOT affect the iterator
		colMod = colsA + 1;
	} //larger smaller does matter now
	else if (rowsA == rowsB)
	{
		rowMod = rowsA + 1;
		colMod = 1; //the column is always the 0th index.
		flopSize(larger, rowsA, colsA, smaller, rowsB, colsB);
	}
	else if (colsA == colsB)
	{
		rowMod = 1; //the row is always the 0th index.
		colMod = colsA + 1;
		flopSize(larger, rowsA, colsA, smaller, rowsB, colsB);
	}
	else if(rowsB == 1 && colsB == 1)
	{
		add_scalar(A, rowsA, colsA, B[0], C);
		return;
	}
	else
	{
		printf("incompatible dimenions\n");
		//assert(false);
	}


	//deal with potentially flopped dimentions
	if (larger != A)
	{ //rowsA always belongs to the larger of the two
		int temp1 = rowsA;
		int temp2 = colsA;
		rowsA = rowsB;
		colsA = colsB;
		rowsB = temp1;
		colsB = temp2;
	}

	//now for the actual math
    int i,j;
#pragma max_concurrency 1
    for (i = 0; i < rowsA; i++)
    {
#pragma max_concurrency 1
        for (j = 0; j < colsA; j++)
        {
            set(C, rowsA, colsA, i,j,get(larger, rowsA, colsA, i, j) + get(smaller, rowsB, colsB, i % rowMod, j % colMod));
        }
    }
}


void sub(const Tensor A, int rowsA, int colsA, const Tensor B, int rowsB, int colsB, Tensor C)
{
	int rowMod;
	int colMod;
	Tensor larger = A; //more rows or cols
	Tensor smaller = B; //one row or one col
	if (rowsA == rowsB && colsA == colsB)
	{//exactly the same size.
		rowMod = rowsA + 1; //these mods do NOT affect the iterator
		colMod = colsA + 1;
	} //larger smaller does matter now
	else if (rowsA == rowsB)
	{
		rowMod = rowsA + 1;
		colMod = 1; //the column is always the 0th index.
		flopSize(larger, rowsA, colsA, smaller, rowsB, colsB);
	}
	else if (colsA == colsB)
	{
		rowMod = 1; //the row is always the 0th index.
		colMod = colsA + 1;;
		flopSize(larger, rowsA, colsA, smaller, rowsB, colsB);
	}
	else if (rowsB == 1 && colsB == 1)
	{
		sub_scalar(A, rowsA, colsA, B[0], C);
		return;
	}
	else
	{
		printf("incompatible dimenions\n");
		//assert(false);
	}
	//deal with potentially flopped dimentions
	if (larger != A)
	{ //rowsA always belongs to the larger of the two
		int temp1 = rowsA;
		int temp2 = colsA;
		rowsA = rowsB;
		colsA = colsB;
		rowsB = temp1;
		colsB = temp2;
	}

	//now for the actual math
	int i, j;
#pragma max_concurrency 1
	for (i = 0; i < rowsA; i++)
	{
#pragma max_concurrency 1
		for (j = 0; j < colsA; j++)
		{
			set(C, rowsA, colsA, i, j, get(larger, rowsA, colsA, i, j) - get(smaller, rowsB, colsB, i % rowMod, j % colMod));
		}
	}
}


void mul_dot(const Tensor A, int rowsA, int colsA, const Tensor B, int rowsB, int colsB, Tensor C)
{
	int rowMod;
	int colMod;
	Tensor larger = A; //more rows or cols
	Tensor smaller = B; //one row or one col
	if (rowsA == rowsB && colsA == colsB)
	{//exactly the same size.
		rowMod = rowsA + 1; //these mods do NOT affect the iterator
		colMod = colsA + 1;
	} //larger smaller does matter now
	else if (rowsA == rowsB)
	{
		rowMod = rowsA + 1;
		colMod = 1; //the column is always the 0th index.
		flopSize(larger, rowsA, colsA, smaller, rowsB, colsB);
	}
	else if (colsA == colsB)
	{
		rowMod = 1; //the row is always the 0th index.
		colMod = colsA + 1;;
		flopSize(larger, rowsA, colsA, smaller, rowsB, colsB);
	}
	else if (rowsB == 1 && colsB == 1)
	{
		mul_scalar(A, rowsA, colsA, B[0], C);
		return;
	}
	else
	{
		printf("incompatible dimenions\n");
		//assert(false);
	}
	//deal with potentially flopped dimentions
	if (larger != A)
	{ //rowsA always belongs to the larger of the two
		int temp1 = rowsA;
		int temp2 = colsA;
		rowsA = rowsB;
		colsA = colsB;
		rowsB = temp1;
		colsB = temp2;
	}

	//now for the actual math
	int i, j;
#pragma max_concurrency 1
	for (i = 0; i < rowsA; i++)
	{
#pragma max_concurrency 1
		for (j = 0; j < colsA; j++)
		{
			set(C, rowsA, colsA, i, j, get(larger, rowsA, colsA, i, j) * get(smaller, rowsB, colsB, i % rowMod, j % colMod));
		}
	}
}


void div_dot(const Tensor A, int rowsA, int colsA, const Tensor B, int rowsB, int colsB, Tensor C)
{
	int rowMod;
	int colMod;
	Tensor larger = A; //more rows or cols
	Tensor smaller = B; //one row or one col
	if (rowsA == rowsB && colsA == colsB)
	{//exactly the same size.
		rowMod = rowsA + 1; //these mods do NOT affect the iterator
		colMod = colsA + 1;
	} //larger smaller does matter now
	else if (rowsA == rowsB)
	{
		rowMod = rowsA + 1;
		colMod = 1; //the column is always the 0th index.
		flopSize(larger, rowsA, colsA, smaller, rowsB, colsB);
	}
	else if (colsA == colsB)
	{
		rowMod = 1; //the row is always the 0th index.
		colMod = colsA + 1;;
		flopSize(larger, rowsA, colsA, smaller, rowsB, colsB);
	}
	else if (rowsB == 1 && colsB == 1)
	{
		div_scalar(A, rowsA, colsA, B[0], C);
		return;
	}
	else
	{
		printf("incompatible dimenions\n");
		//assert(false);
	}
	//deal with potentially flopped dimentions
	if (larger != A)
	{ //rowsA always belongs to the larger of the two
		int temp1 = rowsA;
		int temp2 = colsA;
		rowsA = rowsB;
		colsA = colsB;
		rowsB = temp1;
		colsB = temp2;
	}

	//now for the actual math
	int i, j;
#pragma max_concurrency 1
	for (i = 0; i < rowsA; i++)
	{
#pragma max_concurrency 1
		for (j = 0; j < colsA; j++)
		{
			set(C, rowsA, colsA, i, j, get(larger, rowsA, colsA, i, j) / get(smaller, rowsB, colsB, i % rowMod, j % colMod));
		}
	}
}


void pow_dot(const Tensor A, int rowsA, int colsA, const Tensor B, int rowsB, int colsB, Tensor C)
{// A = B^C, note that there are more efficient functions for 2^X or e^X or 10^X
	int rowMod;
	int colMod;
	Tensor larger = A; //more rows or cols
	Tensor smaller = B; //one row or one col
	if (rowsA == rowsB && colsA == colsB)
	{//exactly the same size.
		rowMod = rowsA + 1; //these mods do NOT affect the iterator
		colMod = colsA + 1;
	} //larger smaller does matter now
	else if (rowsA == rowsB)
	{
		rowMod = rowsA + 1;
		colMod = 1; //the column is always the 0th index.
		flopSize(larger, rowsA, colsA, smaller, rowsB, colsB);
	}
	else if (colsA == colsB)
	{
		rowMod = 1; //the row is always the 0th index.
		colMod = colsA + 1;;
		flopSize(larger, rowsA, colsA, smaller, rowsB, colsB);
	}
	else if (rowsB == 1 && colsB == 1)
	{
		pow_scalar(A, rowsA, colsA, B[0], C);
		return;
	}
	else
	{
		printf("incompatible dimenions\n");
		//assert(false);
	}

	//deal with potentially flopped dimentions
	if (larger != A)
	{ //rowsA always belongs to the larger of the two
		int temp1 = rowsA;
		int temp2 = colsA;
		rowsA = rowsB;
		colsA = colsB;
		rowsB = temp1;
		colsB = temp2;
	}

	//now for the actual math
	int i, j;
#pragma max_concurrency 1
	for (i = 0; i < rowsA; i++)
	{
#pragma max_concurrency 1
		for (j = 0; j < colsA; j++)
		{
			set(C, rowsA, colsA, i, j, (int)pow(get(larger, rowsA, colsA, i, j), get(smaller, rowsB, colsB, i % rowMod, j % colMod)));
		}
	}
}


void add_scalar(const Tensor A, int rowsA, int colsA, int B, Tensor C)
{
    int i,j;
#pragma max_concurrency 1
    for (i = 0; i < rowsA; i++)
    {
#pragma max_concurrency 1
        for (j = 0; j < colsA; j++)
        {
            set(C, rowsA, colsA, i,j,get(A, rowsA, colsA, i,j) + B);
        }
    }
}


void mul_scalar(const Tensor A, int rowsA, int colsA, int B, Tensor C)
{
    int i,j;
#pragma max_concurrency 1
    for (i = 0; i < rowsA; i++)
    {
#pragma max_concurrency 1
        for (j = 0; j < colsA; j++)
        {
            set(C, rowsA, colsA, i,j,get(A, rowsA, colsA, i,j) * B);
        }
    }
}


void sub_scalar(const Tensor A, int rowsA, int colsA, int B, Tensor C)
{
    int i,j;
#pragma max_concurrency 1
    for (i = 0; i < rowsA; i++)
    {
#pragma max_concurrency 1
        for (j = 0; j < colsA; j++)
        {
            set(C, rowsA, colsA, i,j,get(A, rowsA, colsA, i,j) - B);
        }
    }
}


void sub_scalar(int B, const Tensor A, int rowsA, int colsA, Tensor C)
{
	int i, j;
#pragma max_concurrency 1
	for (i = 0; i < rowsA; i++)
	{
#pragma max_concurrency 1
		for (j = 0; j < colsA; j++)
		{
			set(C, rowsA, colsA, i, j, B - get(A, rowsA, colsA, i, j));
		}
	}
}


void div_scalar(const Tensor A, int rowsA, int colsA, int B, Tensor C)
{
    int i,j;
#pragma max_concurrency 1
    for (i = 0; i < rowsA; i++)
    {
#pragma max_concurrency 1
        for (j = 0; j < colsA; j++)
        {
            set(C, rowsA, colsA, i,j,get(A, rowsA, colsA, i,j) / B);
        }
    }
}


void pow_scalar(const Tensor A, int rowsA, int colsA, int B, Tensor C)
{// A = B^C, note that there are more efficient functions for 2^X or e^X or 10^X
    int i,j;
#pragma max_concurrency 1
    for (i = 0; i < rowsA; i++)
    {
#pragma max_concurrency 1
        for (j = 0; j < colsA; j++)
        {
            set(C, rowsA, colsA, i,j, (int)pow(get(A, rowsA, colsA, i,j), B));
        }
    }  
}


void max(const Tensor A, int rowsA, int colsA, int dim, Tensor C)
//functions similar to https://pytorch.org/docs/stable/generated/torch.max.html#torch.max
//but only works on 2d tensors and only returns a tensor with the maximums, no indexes. 
//dim=0 means you find the biggest in each column,
//dim=1 means you find the biggest in each row. 
//Note that the result of this operation is always stored in the first few elements of C.
{
    if(dim == 0)
    {
        int i,j;
        int largest;
        bool first = true;
#pragma max_concurrency 1
        for (i = 0; i < colsA; i++)
        {
            for (j = 0; j < rowsA; j++)
            {
                if(first) 
                {
                    largest = get(A, rowsA, colsA, j,i);
                    first = false;
                }
                else{
                    if(largest < get(A, rowsA, colsA, j,i))
                    {
                        largest = get(A, rowsA, colsA, j,i);
                    }
                }
            }
			//C[i] = largest; //This doesnt use set() due to the way we want to address the space
			set(C, rowsA, colsA, 0, i, largest);
			first = true;
        }
		shrinkTensor(C, rowsA, colsA, C, 1, colsA);
    }
    else
    {
        int i,j;
        int largest;
        bool first = true;
#pragma max_concurrency 1
        for (i = 0; i < rowsA; i++)
        {
            for (j = 0; j < colsA; j++)
            {
                if(first) 
                {
                    largest = get(A, rowsA, colsA, i,j);
                    first = false;
                }
                else{
                    if(largest < get(A, rowsA, colsA, i,j))
                    {
                        largest = get(A, rowsA, colsA, i,j);
                    }
                }
            }
			//C[i] = largest; //This doesnt use set() due to the way we want to address the space
			set(C, rowsA, colsA, i, 0, largest);
			first = true;
        }
		shrinkTensor(C, rowsA, colsA, C, rowsA, 1);
    }
}

void min(const Tensor A, int rowsA, int colsA, int dim, Tensor C)
//virtually same code as MAX
//dim=0 means you find the smallest in each column,
//dim=1 means you find the smallest in each row. 
{
    if(dim == 0)
    {
        int i,j;
        int smallest;
        bool first = true;
#pragma max_concurrency 1
        for (i = 0; i < colsA; i++)
        {
            for (j = 0; j < rowsA; j++)
            {
                if(first) 
                {
                    smallest = get(A, rowsA, colsA, j,i);
                    first = false;
                }
                else{
                    if(smallest > get(A, rowsA, colsA, j,i))
                    {
                        smallest = get(A, rowsA, colsA, j,i);
                    }
                }
            }
			//C[i] = smallest; //This doesnt use set() due to the way we want to address the space
			set(C, rowsA, colsA, 0, i, smallest);
			first = true;
        }
		shrinkTensor(C, rowsA, colsA, C, 1, colsA);
    }
    else
    { //dim ==1
        int i,j;
        int smallest;
        bool first = true;
#pragma max_concurrency 1
        for (i = 0; i < rowsA; i++)
        {
            for (j = 0; j < colsA; j++)
            {
                if(first) 
                {
                    smallest = get(A, rowsA, colsA, i,j);
                    first = false;
                }
                else{
                    if(smallest > get(A, rowsA, colsA, i,j))
                    {
                        smallest = get(A, rowsA, colsA, i,j);
                    }
                }
            }
			//C[i] = smallest; //This doesnt use set() due to the way we want to address the space
			set(C, rowsA, colsA, i, 0, smallest);
			first = true;
        }
		shrinkTensor(C, rowsA, colsA, C, rowsA, 1);
    }
}

void sum(const Tensor A, int rowsA, int colsA, int dim, Tensor C)
{
	//dim=0 means you find the sum of each column,
	//dim=1 means you find the sum of each row. 
	int i, j;
	int running = 0.0f;
	if (dim == 0)
	{
#pragma max_concurrency 1
		for (i = 0; i < colsA; i++)
		{
			for (j = 0; j < rowsA; j++)
			{
				running += get(A, rowsA, colsA, j, i);
			}
			//C[i] = running;
			set(C, rowsA, colsA, 0, i, running);
			running = 0;
		}
		shrinkTensor(C, rowsA, colsA, C, 1, colsA);
	}
	else
	{ //dim ==1
#pragma max_concurrency 1
		for (i = 0; i < rowsA; i++)
		{
			for (j = 0; j < colsA; j++)
			{
				running += get(A, rowsA, colsA, i, j);
			}
			//C[i] = running;
			set(C, rowsA, colsA, i, 0, running);
			running = 0;
		}
		shrinkTensor(C, rowsA, colsA, C, rowsA, 1);
	}
}


void max_scalar(const Tensor A, int rowsA, int colsA, int compare, Tensor C)
{ //similar to clamp but more readable
	int i, j;
#pragma max_concurrency 1
	for (i = 0; i < rowsA; i++)
	{
#pragma max_concurrency 1
		for (j = 0; j < colsA; j++)
		{
			int mat = get(A, rowsA, colsA, i, j);
			if (mat < compare) { set(C, rowsA, colsA, i, j, compare); }
			else { set(C, rowsA, colsA, i, j, mat); }
		}
	}
}

void min_scalar(const Tensor A, int rowsA, int colsA, int compare, Tensor C)
{
	int i, j;
#pragma max_concurrency 1
	for (i = 0; i < rowsA; i++)
	{
#pragma max_concurrency 1
		for (j = 0; j < colsA; j++)
		{
			int mini = get(A, rowsA, colsA, i, j);
			if (mini > compare) { set(C, rowsA, colsA, i, j, compare); }
			else { set(C, rowsA, colsA, i, j, mini); }
		}
	}
}


void min_dot(const Tensor A, int rowsA, int colsA, const Tensor B, Tensor C)
{//element wise min that assumes a and b are the same size
	//assert(sameSize(A, B));
	int i, j;
#pragma max_concurrency 1
	for (i = 0; i < rowsA; i++)
	{
#pragma max_concurrency 1
		for (j = 0; j < colsA; j++)
		{
			int left = get(A, rowsA, colsA, i, j);
			int right = get(B, rowsA, colsA, i, j);

			if (left > right) { set(C, rowsA, colsA, i, j, right); }
			else { set(C, rowsA, colsA, i, j, left); }
		}
	}
}


void abs_tensor(const Tensor A, int rowsA, int colsA, Tensor C)
{
	int i, j;
#pragma max_concurrency 1
	for (i = 0; i < rowsA; i++)
	{
#pragma max_concurrency 1
		for (j = 0; j < colsA; j++)
		{
			int el = get(A, rowsA, colsA, i, j);
			el = abs(el);
			set(C, rowsA, colsA, i, j, el);
		}
	}
}

/*
void floor_tensor(const Tensor A, int rowsA, int colsA, Tensor C)
{//does a cast to a float and then floors it.
    int i,j;
#pragma max_concurrency 1
    for (i = 0; i < rowsA; i++)
    {
#pragma max_concurrency 1
        for (j = 0; j < colsA; j++)
        {
            float temp = get(A, rowsA, colsA, i,j);
            temp = floorf(temp);
            set(C, rowsA, colsA, i,j,temp);
        }
    }
}*/


void exp2_tensor(const Tensor A, int rowsA, int colsA, Tensor C)
{
	int i, j;
#pragma max_concurrency 1
	for (i = 0; i < rowsA; i++)
	{
#pragma max_concurrency 1
		for (j = 0; j < colsA; j++)
		{
			set(C, rowsA, colsA, i, j, (int)exp2(get(A, rowsA, colsA, i, j)));
		}
	}
}


void clamp(const Tensor A, int rowsA, int colsA, int min, int max, Tensor C)
{
    int i,j;
#pragma max_concurrency 1
    for (i = 0; i < rowsA; i++)
    {
#pragma max_concurrency 1
        for (j = 0; j < colsA; j++)
        {
            int viq = get(A, rowsA, colsA, i,j);
            if(viq > max) {set(C, rowsA, colsA, i,j,max);}
            else if (viq < min) {set(C, rowsA, colsA, i,j,min);}
			else { set(C, rowsA, colsA, i, j, viq); }
        }
    }     
}

/*
void roundTensor(const Tensor A, int rowsA, int colsA, Tensor C)
{
    int i,j;
#pragma max_concurrency 1
    for (i = 0; i < rowsA; i++)
    {
#pragma max_concurrency 1
        for (j = 0; j < colsA; j++)
        {
            float roundme = get(A, rowsA, colsA, i,j);
            float rounded = round(roundme); //always cast to float
			if (fabs(rounded - roundme) == 0.5f)
			{// glitch where this should be rounded down
				rounded = trunc(roundme);
			}
            set(C, rowsA, colsA, i,j, rounded);
        }
    }     
}*/

/*
void reciprocal(const Tensor A, int rowsA, int colsA, Tensor C)
{
    int i,j;
#pragma max_concurrency 1
    for (i = 0; i < rowsA; i++)
    {
#pragma max_concurrency 1
        for (j = 0; j < colsA; j++)
        {
            float recip = get(A, rowsA, colsA, i,j);
            recip = 1.f/recip;
            set(C, rowsA, colsA, i,j,recip);
        }
    }     
}*/
/*
void reciprocal(const Flensor A, int rowsA, int colsA, Flensor C)
{//incoming big tensor array
	int i, j;
#pragma max_concurrency 1
	for (i = 0; i < rowsA; i++)
	{
#pragma max_concurrency 1
		for (j = 0; j < colsA; j++)
		{
			auto recip = get(A, rowsA, colsA, i, j);
			recip = reciprocal_fixed(recip);
			set(C, rowsA, colsA, i, j, recip);
		}
	}
}
*/

void sign(const Tensor A, int rowsA, int colsA, Tensor C)
{
	int i, j;
#pragma max_concurrency 1
	for (i = 0; i < rowsA; i++)
	{
#pragma max_concurrency 1
		for (j = 0; j < colsA; j++)
		{
			if (get(A, rowsA, colsA, i, j) < 0)
			{
				set(C, rowsA, colsA, i, j, -1);
			}
			else if (get(A, rowsA, colsA, i, j) > 0)
			{
				set(C, rowsA, colsA, i, j, 1);
			}
			else
			{
				set(C, rowsA, colsA, i, j, 0);
			}
		}
	}
}

 
void mean(const Tensor A, int rowsA, int colsA, Tensor C)
{// assume a row vector. can be expanded upon like max and min to work along multiple dimentions
	//assert(rowsA == 1);
	int running = 0.f;
#pragma max_concurrency 1
	for (int j = 0; j < colsA; j++)
	{
		running += get(A, rowsA, colsA, 0, j);
	}
	set(C, rowsA, colsA, 0, 0, running / colsA);
}

/*
void sqrt_tensor(const Tensor A, int rowsA, int colsA, Tensor C)
{
	int i, j;
#pragma max_concurrency 1
	for (i = 0; i < rowsA; i++)
	{
#pragma max_concurrency 1
		for (j = 0; j < colsA; j++)
		{
			set(C, rowsA, colsA, i, j, sqrt(get(A, rowsA, colsA, i,j)));
		}
	}
}*/
/****************************************************manipulation****************************************************/

void fill(const Tensor A, int rowsA, int colsA, int fill)
{
    int i,j;
#pragma max_concurrency 1
    for (i = 0; i < rowsA; i++)
    {
#pragma max_concurrency 1
        for (j = 0; j < colsA; j++)
        {
            set(A, rowsA, colsA, i,j, fill);
        }
    }     
}

/* TODO: this is probably not a necessary function anymore
void view(const Tensor A, int rowsA, int colsA, const int rows, const int cols, Tensor space)
{// a PRIMITIVE implementation of https://pytorch.org/docs/stable/generated/torch.Tensor.view.html?highlight=view#torch.Tensor.view
 // currentely only supports (rows, cols) where row and col go from -1 to 3072.
 // reshapes the tensor so that its values fit in a new shape. BE SMART when using this, because the function is dumb
    
    int i,j;
    for (i = 0; i < rowsA; i++)
    {
        for (j = 0; j < colsA; j++)
        {
            set(space,i,j, get(A,i,j)); //copy to local tensor space
        }
    }
    //now we are going to copy to the new space. If we calculate inferred dimentions first
    int numElements = rowsA*colsA;
    int newRows = rows;
    int newCols = cols;
    //you can see how this will go bad if total elements doesnt neatly fit into the new shape
    if(newRows == -1)
    {
        newRows = numElements/newCols;
    }
    else if(newCols == -1)
    {
        newCols = numElements/newRows;
    }
    int curNewRow = 0;
    int curNewCol = 0;
    for (i = 0; i < rowsA; i++)
    {
        for (j = 0; j < colsA; j++)
        {
            set(A, curNewRow, curNewCol, get(space,i,j)); //copy from local tensor space
            curNewCol++;
            curNewCol = curNewCol % newCols;
            //now if the modulus reset us, increment the row.
            if(curNewCol == 0) curNewRow++; //only supports a stride of 1.
        }
    }
    setRows(A, newRows);
    setCols(A, newCols);
}
*/
/*
void tensor_frexp(Tensor In, int rowsIn, int colsIn, Tensor m, int rowsm, int colsm, Tensor e, int rowse, int colse)
{
    //I am writing this one myself as I dont have access to numpy
    //C has a function called frexp, so I am just applying it to every element in a matrix.
    //used for the fixed point multiply function in quant_act 
    //reutrns the mantissas and then put the exponents in a seperate tensor.
	const int MAX_BIT = 31;
    int i,j;
#pragma max_concurrency 1
    for (i = 0; i < rowsIn; i++)
    {
#pragma max_concurrency 1
        for (j = 0; j < colsIn; j++)
        {
            float m1;
            int e1;
            m1 = frexp(get(In, rowsIn, colsIn, i,j), &e1);
            set(m, rowsm, colsm, i, j, m1);
            set(e, rowse, colse, i, j, (float)e1);

			//additional math
			int m_t = int(round(get(m, rowsm, colsm, i, j) * exp2(MAX_BIT)));
			set(m, rowsm, colsm, i, j, float(m_t));

			set(e, rowse, colse, i, j, float(MAX_BIT - e1));
        }
    }
}*/

/****************************************************adressing methods****************************************************/

//float get(const Tensor A, int rowsA, int colsA, int row, int col)
//{
//	return A[row * colsA + col];
//}

template<typename T> T get(T* A, int rowsA, int colsA, int row, int col)
{
	return A[row * colsA + col];
}

float transposed_get(const Tensor A, int rowsA, int colsA, int row, int col)
{
	return A[col*rowsA + row];
}


//void set(const Tensor A, int rowsA, int colsA, int row, int col, float val)
//{ //TODO: change to inline
//	A[row * colsA + col] = val;
//}
template<typename T> void set(T* A, int rowsA, int colsA, int row, int col, T val)
{
	A[row * colsA + col] = val;
}

void transposed_set(const Tensor A, int rowsA, int colsA, int row, int col, float val)
{
	A[col*rowsA + row] = val;
}

void transpose(const Tensor A, int rowsA, int colsA, Tensor C)
{
#pragma max_concurrency 1
	for (int i = 0; i < rowsA; i++)
	{
#pragma max_concurrency 1
		for (int j = 0; j < colsA; i++)
		{
			set(C, colsA, rowsA, j, i, get(A, rowsA, colsA, i, j));
		}
	}
}

void copy(const Tensor A, int rowsA, int colsA, Tensor C)
{
#pragma max_concurrency 1
	for (int i = 0; i < rowsA; i++)
	{
#pragma max_concurrency 1
		for (int j = 0; j < colsA; j++)
		{
			set(C, rowsA, colsA, i, j, get(A, rowsA, colsA, i, j));
		}
	}
}

void shrinkTensor(const Tensor A, int rowsA, int colsA, Tensor C, int rowsC, int colsC) //use this after a dimention has been collapsed
{
	//we will assume that rows have been collapsed to 1 or cols have been collapsed to 1.
	if (rowsA != rowsC && rowsC ==1)
	{//we have a 2d matrix who has one row but the values are positioned assuming multiple columns. Iterate over that row using different assumptions to collapse to C.
#pragma max_concurrency 1
		for (int i = 0; i < colsA; i++)
		{
			int take = get(A, rowsA, colsA, 0, i);
			set(C, rowsC, colsC, 0, i, take);
		}
	}
	else if (colsA != colsC && colsC == 1)
	{
#pragma max_concurrency 1
		for (int i = 0; i < rowsA; i++)
		{
			int take = get(A, rowsA, colsA, i, 0);
			set(C, rowsC, colsC, i, 0, take);
		}
	}
}

//helper/debugger/verification functions
void print(const Tensor A, int rowsA, int colsA)
{
	
    #ifndef HLS_SYNTHESIS
    std::cout << "Tensor: " << std::endl;
	#endif
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsA; j++) {
            #ifndef HLS_SYNTHESIS
            std::cout << "[" << get(A, rowsA, colsA, i,j) << "] ";
            #endif
        }
        #ifndef HLS_SYNTHESIS
        std::cout << std::endl;
        #endif
    }
}


void print_brief(const Tensor A, int rowsA, int colsA)
{

	#ifndef HLS_SYNTHESIS
	std::cout << "Tensor: " << std::endl;
	#endif
	for (int i = 0; i < rowsA; i++) {
		for (int j = 0; j < colsA; j++) {
			#ifndef HLS_SYNTHESIS
			std::cout << "[" << get(A, rowsA, colsA, i, j) << "] ";
			#endif
			if (j == 2 && (colsA - 4 != 1))
			{
				printf(" ... "); //one two skip a few... 99 100
				j = colsA - 4;
			}
		}
		if (i == 2 && (rowsA - 4 != 1))
		{
			printf("\n ... \n");
			i = rowsA - 4;
		}
		#ifndef HLS_SYNTHESIS
		std::cout << std::endl;
		#endif
	}
}


bool eq(const Tensor A, int rowsA, int colsA, const Tensor B, int rowsB, int colsB)
{//returns true if all elements are the same. No broadcasting.
    int i,j;
    for (i = 0; i < rowsA; i++)
    {
        for (j = 0; j < colsA; j++)
        {
            if(get(A, rowsA, colsA, i,j) == get(B, rowsB, colsB, i,j)){continue;}
            else{return false;}
        }
    }
    return true;  
}


bool eq_verbose(const Tensor A, int rowsA, int colsA, const Tensor B, int rowsB, int colsB)
{//returns true if all elements are the same. No broadcasting.
	bool one = false;
	int i, j;
	for (i = 0; i < rowsA; i++)
	{
		for (j = 0; j < colsA; j++)
		{
			if (fabs(get(A, rowsA, colsA, i, j) - get(B, rowsB, colsB, i, j)) > 0.001f)
			{
				printf("row %d col %d, LHS is %d, and RHS is %d \n", i, j, get(A, rowsA, colsA, i, j), get(B, rowsB, colsB, i, j));
				one = true;
			}
		}
	}
	if (one)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void flopSize(Tensor &lhs, int rowsLHS, int colsLHS, Tensor &rhs, int rowsRHS, int colsRHS)
{//At the end of this function lhs will always point to the larger of the two tensors
	//assert(sameRows(lhs,rhs) || sameCols(lhs,rhs)); //we assume that the tensors share one dimention
	if (colsLHS < colsRHS || rowsLHS < rowsRHS) // if the left hand side has the smaller dimention, flop them
	{
		Tensor temp = lhs;
		lhs = rhs;
		rhs = temp;
	}
}