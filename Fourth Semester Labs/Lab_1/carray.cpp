/*
 * `file` 			carray.cpp
 * `written` 		01/06/17
 * `last modified`	01/06/17
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		c array class implementation
 *
 *	Description: 	c array class is similar to vector but holds int values
 *
 *	`note`			re factored July 23 2017 7:54:13
 */
 
 

#include "cArray.h"

using namespace lab1::carray;


//Attributes
//Returns the largest valid index.
int cArray::Getupperbound() const{

	if (counter)
		return counter - 1;
	
	return counter;
}

//Establishes the size of an empty or existing array; allocates memory if necessary.
void cArray::SetSize(int nnewsize){
	
	int *tmp, n;
	if (size == nnewsize)
		return;
	
	tmp = new int[nnewsize];
	if (size > nnewsize)
		n = nnewsize;
	else
		n = size;
	
	for (int i = 0; i < n; i++)
		tmp[i] = buf[i];
	
	delete[] buf;
	
	size = nnewsize;
	buf = tmp;
}



//Operations
//Frees all unused memory above the current upper bound.
//This function has no effect on the upper bound of the array.
void cArray::FreeExtra(){
	
	if (counter == size)
		return;
	
	SetSize(counter);
}

//Growing the Array
//Adds an element to the end of the array; grows the array if necessary.
void cArray::Add(int value){
	
	if (counter == size)
		SetSize(size + growBy);
	
	buf[counter++] = value;
}

//Appends another array to the array; grows the array if necessary
void cArray::Append(cArray *Arr){
	
	if (Arr == this)
		return;
	
	int k = Arr->counter;
	if (size - counter < k){
	
		if (k < growBy)
			k = growBy;
		
		SetSize(size + k);
	}
	
	for (int i = 0; i < Arr->counter; i++)
		buf[counter++] = Arr->buf[i];

}

//Copies another array to the array; grows the array if necessary.
void cArray::Copy(cArray *Arr){

	if (Arr == this)
		return;

	counter = Arr->counter;

	if (size < counter)
		SetSize(counter);

	for (int i = 0; i < counter; i++)
		buf[i] = Arr->buf[i];
}

//Removes an element at a specific index.
void cArray::RemoveAt(int n){

	--counter;

	for (int i = n; i < counter; i++)
		buf[i] = buf[i + 1];
}
