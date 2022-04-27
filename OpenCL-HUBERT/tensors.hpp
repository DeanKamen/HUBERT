//tensors.hpp
//Basic HLS tensor implementation for the HUBERT project.
//created by Hunter Messner on 6/6/2021

#include "HLS/hls.h"
#include "HLS/math.h"
#include "HLS/stdio.h"
#include <iostream>
/*                    DEFINITIONS                      */

template<typename tint, typename loc>
void add( tint* A, loc rowsA, loc colsA,  tint* B, loc rowsB, loc colsB, tint* C) 
//with basic broadcasting
{
	loc rowMod;
	loc colMod;
	tint* larger = A; //more rows or cols
	tint* smaller = B; //one row or one col
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
		loc temp1 = rowsA;
		loc temp2 = colsA;
		rowsA = rowsB;
		colsA = colsB;
		rowsB = temp1;
		colsB = temp2;
	}

	//now for the actual math
    loc i,j;

#pragma ivdep
    for (i = 0; i < rowsA; i++)
    {
#pragma ivdep
        for (j = 0; j < colsA; j++)
        {
			tint data = get(larger, rowsA, colsA, i, j) + get(smaller, rowsB, colsB, i % rowMod, j % colMod);
            set(C, rowsA, colsA, i,j, data);
        }
    }
}

template<typename tint, typename loc>
void sub( tint* A, loc rowsA, loc colsA,  tint* B, loc rowsB, loc colsB, tint* C)
{
	loc rowMod;
	loc colMod;
	tint* larger = A; //more rows or cols
	tint* smaller = B; //one row or one col
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
		loc temp1 = rowsA;
		loc temp2 = colsA;
		rowsA = rowsB;
		colsA = colsB;
		rowsB = temp1;
		colsB = temp2;
	}

	//now for the actual math
	loc i, j;

#pragma ivdep
	for (i = 0; i < rowsA; i++)
	{

#pragma ivdep
		for (j = 0; j < colsA; j++)
		{
			set(C, rowsA, colsA, i, j, get(larger, rowsA, colsA, i, j) - get(smaller, rowsB, colsB, i % rowMod, j % colMod));
		}
	}
}

template<typename tint, typename loc>
void mul_dot( tint* A, loc rowsA, loc colsA,  tint* B, loc rowsB, loc colsB, tint* C)
{
	loc rowMod;
	loc colMod;
	tint* larger = A; //more rows or cols
	tint* smaller = B; //one row or one col
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
		loc temp1 = rowsA;
		loc temp2 = colsA;
		rowsA = rowsB;
		colsA = colsB;
		rowsB = temp1;
		colsB = temp2;
	}

	//now for the actual math
	loc i, j;

#pragma ivdep
	for (i = 0; i < rowsA; i++)
	{

#pragma ivdep
		for (j = 0; j < colsA; j++)
		{
			tint data = get(larger, rowsA, colsA, i, j) * get(smaller, rowsB, colsB, i % rowMod, j % colMod);
			set(C, rowsA, colsA, i, j, data);
		}
	}
}

template<typename tint, typename loc>
void div_dot( tint* A, loc rowsA, loc colsA,  tint* B, loc rowsB, loc colsB, tint* C)
{
	loc rowMod;
	loc colMod;
	tint* larger = A; //more rows or cols
	tint* smaller = B; //one row or one col
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
		loc temp1 = rowsA;
		loc temp2 = colsA;
		rowsA = rowsB;
		colsA = colsB;
		rowsB = temp1;
		colsB = temp2;
	}

	//now for the actual math
	loc i, j;

#pragma ivdep
	for (i = 0; i < rowsA; i++)
	{

#pragma ivdep
		for (j = 0; j < colsA; j++)
		{
			set(C, rowsA, colsA, i, j, get(larger, rowsA, colsA, i, j) / get(smaller, rowsB, colsB, i % rowMod, j % colMod));
		}
	}
}

template<typename tint, typename loc>
void pow_dot( tint* A, loc rowsA, loc colsA,  tint* B, loc rowsB, loc colsB, tint* C)
{// A = B^C, note that there are more efficient functions for 2^X or e^X or 10^X
	loc rowMod;
	loc colMod;
	tint* larger = A; //more rows or cols
	tint* smaller = B; //one row or one col
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
		loc temp1 = rowsA;
		loc temp2 = colsA;
		rowsA = rowsB;
		colsA = colsB;
		rowsB = temp1;
		colsB = temp2;
	}

	//now for the actual math
	loc i, j;

#pragma ivdep
	for (i = 0; i < rowsA; i++)
	{

#pragma ivdep
		for (j = 0; j < colsA; j++)
		{
			set(C, rowsA, colsA, i, j, (tint)pow(get(larger, rowsA, colsA, i, j), get(smaller, rowsB, colsB, i % rowMod, j % colMod)));
		}
	}
}

template<typename tint, typename loc>
void rightShift( tint* A,  loc rowsA,  loc colsA,  tint* B,  loc rowsB,  loc colsB, tint* C)//specialized, no broadcasting
{
	loc i, j;

#pragma ivdep
	for (i = 0; i < rowsA; i++)
	{

#pragma ivdep
		for (j = 0; j < colsA; j++)
		{
			set(C, rowsA, colsA, i, j, get(A, rowsA, colsA, i, j) >> get(B, rowsB, colsB, i, j));
		}
	}
}

template<typename tint, typename loc>
void add_scalar( tint* A, loc rowsA, loc colsA, tint B, tint* C)
{
    loc i,j;

#pragma ivdep
    for (i = 0; i < rowsA; i++)
    {

#pragma ivdep
        for (j = 0; j < colsA; j++)
        {
			tint data = get(A, rowsA, colsA, i, j) + tint(B);
            set(C, rowsA, colsA, i,j, data);
        }
    }
}

template<typename tint, typename loc>
void mul_scalar( tint* A, loc rowsA, loc colsA, tint B, tint* C)
{
    loc i,j;

#pragma ivdep
    for (i = 0; i < rowsA; i++)
    {

#pragma ivdep
        for (j = 0; j < colsA; j++)
        {
			tint data = get(A, rowsA, colsA, i, j) * tint(B);
            set(C, rowsA, colsA, i,j, data);
        }
    }
}

template<typename tint, typename loc>
void sub_scalar( tint* A, loc rowsA, loc colsA, tint B, tint* C)
{
    loc i,j;

#pragma ivdep
    for (i = 0; i < rowsA; i++)
    {

#pragma ivdep
        for (j = 0; j < colsA; j++)
        {
            set(C, rowsA, colsA, i,j,get(A, rowsA, colsA, i,j) - B);
        }
    }
}

template<typename tint, typename loc>
void sub_scalar(tint B,  tint* A, loc rowsA, loc colsA, tint* C)
{
	loc i, j;

#pragma ivdep
	for (i = 0; i < rowsA; i++)
	{

#pragma ivdep
		for (j = 0; j < colsA; j++)
		{
			set(C, rowsA, colsA, i, j, B - get(A, rowsA, colsA, i, j));
		}
	}
}

template<typename tint, typename loc>
void div_scalar( tint* A, loc rowsA, loc colsA, tint B, tint* C)
{
    loc i,j;

#pragma ivdep
    for (i = 0; i < rowsA; i++)
    {

#pragma ivdep
        for (j = 0; j < colsA; j++)
        {
			tint data = tint(get(A, rowsA, colsA, i, j)) / tint(B);
            set(C, rowsA, colsA, i,j, data);
        }
    }
}

template<typename tint, typename loc>
void pow_scalar( tint* A, loc rowsA, loc colsA, tint B, tint* C)
{// A = B^C, note that there are more efficient functions for 2^X or e^X or 10^X
    loc i,j;

#pragma ivdep
    for (i = 0; i < rowsA; i++)
    {

#pragma ivdep
        for (j = 0; j < colsA; j++)
        {
            set(C, rowsA, colsA, i,j, (tint)pow(get(A, rowsA, colsA, i,j), B));
        }
    }  
}

template<typename tint, typename loc>
void max( tint* A, loc rowsA, loc colsA, int dim, tint* C)
//functions similar to https://pytorch.org/docs/stable/generated/torch.max.html#torch.max
//but only works on 2d tensors and only returns a tensor with the maximums, no indexes. 
//dim=0 means you find the biggest in each column,
//dim=1 means you find the biggest in each row. 
//Note that the result of this operation is always stored in the first few elements of C.
{
    if(dim == 0)
    {
        loc i,j;
        tint largest;
        bool first = true;

#pragma ivdep
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
        loc i,j;
        tint largest;
        bool first = true;

#pragma ivdep
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

template<typename tint, typename loc>
void min( tint* A, loc rowsA, loc colsA, int dim, tint* C)
//virtually same code as MAX
//dim=0 means you find the smallest in each column,
//dim=1 means you find the smallest in each row. 
{
    if(dim == 0)
    {
        loc i,j;
        tint smallest;
        bool first = true;

#pragma ivdep
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
        loc i,j;
        tint smallest;
        bool first = true;

#pragma ivdep
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

template<typename tint, typename loc>
void sum( tint* A, loc rowsA, loc colsA, int dim, tint* C)
{
	//dim=0 means you find the sum of each column,
	//dim=1 means you find the sum of each row. 
	loc i, j;
	tint running = 0;
	if (dim == 0)
	{

#pragma ivdep
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

#pragma ivdep
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

template<typename tint, typename loc>
void max_scalar( tint* A, loc rowsA, loc colsA, tint compare, tint* C)
{ //similar to clamp but more readable
	loc i, j;

#pragma ivdep
	for (i = 0; i < rowsA; i++)
	{

#pragma ivdep
		for (j = 0; j < colsA; j++)
		{
			tint mat = get(A, rowsA, colsA, i, j);
			if (mat < compare) { set(C, rowsA, colsA, i, j, compare); }
			else { set(C, rowsA, colsA, i, j, mat); }
		}
	}
}

template<typename tint, typename loc>
void min_scalar( tint* A, loc rowsA, loc colsA, loc compare, tint* C)
{
	loc i, j;

#pragma ivdep
	for (i = 0; i < rowsA; i++)
	{

#pragma ivdep
		for (j = 0; j < colsA; j++)
		{
			tint mini = get(A, rowsA, colsA, i, j);
			if (mini > compare) { set(C, rowsA, colsA, i, j, compare); }
			else { set(C, rowsA, colsA, i, j, mini); }
		}
	}
}

template<typename tint, typename loc>
void min_dot( tint* A, loc rowsA, loc colsA,  tint* B, tint* C)
{//element wise min that assumes a and b are the same size
	//assert(sameSize(A, B));
	loc i, j;

#pragma ivdep
	for (i = 0; i < rowsA; i++)
	{

#pragma ivdep
		for (j = 0; j < colsA; j++)
		{
			tint left = get(A, rowsA, colsA, i, j);
			tint right = get(B, rowsA, colsA, i, j);

			if (left > right) { set(C, rowsA, colsA, i, j, right); }
			else { set(C, rowsA, colsA, i, j, left); }
		}
	}
}

template<typename tint, typename loc>
void abs_tensor( tint* A, loc rowsA, loc colsA, tint* C)
{
	loc i, j;

#pragma ivdep
	for (i = 0; i < rowsA; i++)
	{

#pragma ivdep
		for (j = 0; j < colsA; j++)
		{
			tint el = get(A, rowsA, colsA, i, j);
			el = abs(el);
			set(C, rowsA, colsA, i, j, el);
		}
	}
}



template<typename tint, typename loc>
void exp2_tensor( tint* A, loc rowsA, loc colsA, tint* C)
{
	loc i, j;

#pragma ivdep
	for (i = 0; i < rowsA; i++)
	{

#pragma ivdep
		for (j = 0; j < colsA; j++)
		{
			set(C, rowsA, colsA, i, j, 1 << (get(A, rowsA, colsA, i, j))); //who needs exp2 when you can just left shift.
		}
	}
}

template<typename tint, typename loc>
void clamp( tint* A, loc rowsA, loc colsA, tint min, tint max, tint* C)
{
    loc i,j;

#pragma ivdep
    for (i = 0; i < rowsA; i++)
    {

#pragma ivdep
        for (j = 0; j < colsA; j++)
        {
            tint viq = get(A, rowsA, colsA, i,j);
            if(viq > max) {set(C, rowsA, colsA, i,j,max);}
            else if (viq < min) {set(C, rowsA, colsA, i,j,min);}
			else { set(C, rowsA, colsA, i, j, viq); }
        }
    }     
}

template<typename tint, typename loc>
void sign( tint* A, loc rowsA, loc colsA, tint* C)
{
	loc i, j;

#pragma ivdep
	for (i = 0; i < rowsA; i++)
	{

#pragma ivdep
		for (j = 0; j < colsA; j++)
		{
			if (get(A, rowsA, colsA, i, j) < 0)
			{
				set(C, rowsA, colsA, i, j, (tint)-1);
			}
			else if (get(A, rowsA, colsA, i, j) > 0)
			{
				set(C, rowsA, colsA, i, j, (tint)1);
			}
			else
			{
				set(C, rowsA, colsA, i, j, (tint)0);
			}
		}
	}
}

template<typename tint, typename loc>
void mean( tint* A, loc rowsA, loc colsA, tint* C)
{// assume a row vector. can be expanded upon like max and min to work along multiple dimentions
	//assert(rowsA == 1);
	tint running = 0;

#pragma ivdep
	for (loc j = 0; j < colsA; j++)
	{
		running += get(A, rowsA, colsA, 0, j);
	}
	set(C, rowsA, colsA, 0, 0, running / colsA);
}


/****************************************************manipulation****************************************************/
template<typename tint, typename loc>
void fill( tint* A, loc rowsA, loc colsA, tint fill)
{
    loc i,j;

#pragma ivdep
    for (i = 0; i < rowsA; i++)
    {

#pragma ivdep
        for (j = 0; j < colsA; j++)
        {
            set(A, rowsA, colsA, i,j, fill);
        }
    }     
}



/****************************************************adressing methods****************************************************/


template<typename tint, typename loc> tint get(tint* A, loc rowsA, loc colsA, loc row, loc col)
{
	return A[row * colsA + col];
}

template<typename tint, typename loc> tint transposed_get( tint* A, loc rowsA, loc colsA, loc row, loc col)
{
	return A[col*rowsA + row];
}


template<typename tint, typename loc> void set(tint* A, loc rowsA, loc colsA, loc row, loc col, tint val)
{
	A[row * colsA + col] = val;
}

template<typename tint, typename loc> void transposed_set( tint* A, loc rowsA, loc colsA, loc row, loc col, tint val)
{
	A[col*rowsA + row] = val;
}

template<typename tint, typename loc>
void transpose( tint* A, loc rowsA, loc colsA, tint* C)
{

#pragma ivdep
	for (loc i = 0; i < rowsA; i++)
	{

#pragma ivdep
		for (loc j = 0; j < colsA; i++)
		{
			set(C, colsA, rowsA, j, i, get(A, rowsA, colsA, i, j));
		}
	}
}

template<typename tint, typename loc>
void copy( tint* A, loc rowsA, loc colsA, tint* C)
{

#pragma ivdep
	for (loc i = 0; i < rowsA; i++)
	{

#pragma ivdep
		for (loc j = 0; j < colsA; j++)
		{
			set(C, rowsA, colsA, i, j, get(A, rowsA, colsA, i, j));
		}
	}
}

template<typename tint, typename loc>
void shrinkTensor( tint* A, loc rowsA, loc colsA, tint* C, loc rowsC, loc colsC) //use this after a dimention has been collapsed
{
	//we will assume that rows have been collapsed to 1 or cols have been collapsed to 1.
	if (rowsA != rowsC && rowsC ==1)
	{//we have a 2d matrix who has one row but the values are positioned assuming multiple columns. Iterate over that row using different assumptions to collapse to C.

#pragma ivdep
		for (loc i = 0; i < colsA; i++)
		{
			tint take = get(A, rowsA, colsA, 0, i);
			set(C, rowsC, colsC, 0, i, take);
		}
	}
	else if (colsA != colsC && colsC == 1)
	{

#pragma ivdep
		for (loc i = 0; i < rowsA; i++)
		{
			tint take = get(A, rowsA, colsA, i, 0);
			set(C, rowsC, colsC, i, 0, take);
		}
	}
}

//helper/debugger/verification functions
template<typename tint, typename loc>
void print( tint* A, loc rowsA, loc colsA)
{
	
    #ifndef HLS_SYNTHESIS
    std::cout << "Tensor: " << std::endl;
	#endif
    for (loc i = 0; i < rowsA; i++) {
        for (loc j = 0; j < colsA; j++) {
            #ifndef HLS_SYNTHESIS
            std::cout << "[" << get(A, rowsA, colsA, i,j) << "] ";
            #endif
        }
        #ifndef HLS_SYNTHESIS
        std::cout << std::endl;
        #endif
    }
}

template<typename tint, typename loc>
void print_brief( tint* A, loc rowsA, loc colsA)
{

	#ifndef HLS_SYNTHESIS
	std::cout << "Tensor: " << std::endl;
	#endif
	for (loc i = 0; i < rowsA; i++) {
		for (loc j = 0; j < colsA; j++) {
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

template<typename tint, typename loc>
bool eq( tint* A, loc rowsA, loc colsA,  tint* B, loc rowsB, loc colsB)
{//returns true if all elements are the same. No broadcasting.
    loc i,j;
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

template<typename tint, typename loc>
bool eq_verbose( tint* A, loc rowsA, loc colsA,  tint* B, loc rowsB, loc colsB)
{//returns true if all elements are the same. No broadcasting.
	bool one = false;
	loc i, j;
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

template<typename tint, typename loc>
void flopSize(tint* &lhs, loc rowsLHS, loc colsLHS, tint* &rhs, loc rowsRHS, loc colsRHS)
{//At the end of this function lhs will always point to the larger of the two tensors
	//assert(sameRows(lhs,rhs) || sameCols(lhs,rhs)); //we assume that the tensors share one dimention
	if (colsLHS < colsRHS || rowsLHS < rowsRHS) // if the left hand side has the smaller dimention, flop them
	{
		tint* temp = lhs;
		lhs = rhs;
		rhs = temp;
	}
}

/*
void floor_tensor( Tensor A, int rowsA, int colsA, Tensor C)
{//does a cast to a float and then floors it.
	int i,j;

	for (i = 0; i < rowsA; i++)
	{

		for (j = 0; j < colsA; j++)
		{
			float temp = get(A, rowsA, colsA, i,j);
			temp = floorf(temp);
			set(C, rowsA, colsA, i,j,temp);
		}
	}
}*/
/*
void roundTensor( Tensor A, int rowsA, int colsA, Tensor C)
{
	int i,j;

	for (i = 0; i < rowsA; i++)
	{

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
void reciprocal( Tensor A, int rowsA, int colsA, Tensor C)
{
	int i,j;

	for (i = 0; i < rowsA; i++)
	{

		for (j = 0; j < colsA; j++)
		{
			float recip = get(A, rowsA, colsA, i,j);
			recip = 1.f/recip;
			set(C, rowsA, colsA, i,j,recip);
		}
	}
}*/
/*
void reciprocal( Flensor A, int rowsA, int colsA, Flensor C)
{//incoming big tensor array
	int i, j;

	for (i = 0; i < rowsA; i++)
	{

		for (j = 0; j < colsA; j++)
		{
			auto recip = get(A, rowsA, colsA, i, j);
			recip = reciprocal_fixed(recip);
			set(C, rowsA, colsA, i, j, recip);
		}
	}
}
*/
/*
void sqrt_tensor( Tensor A, int rowsA, int colsA, Tensor C)
{
	int i, j;

	for (i = 0; i < rowsA; i++)
	{

		for (j = 0; j < colsA; j++)
		{
			set(C, rowsA, colsA, i, j, sqrt(get(A, rowsA, colsA, i,j)));
		}
	}
}*/

/* TODO: this is probably not a necessary function anymore
void view( Tensor A, int rowsA, int colsA,  int rows,  int cols, Tensor space)
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
	 int MAX_BIT = 31;
	int i,j;

	for (i = 0; i < rowsIn; i++)
	{

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