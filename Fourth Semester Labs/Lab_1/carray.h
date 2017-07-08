/***
* file:"carray.h"
* synopsis: carray class interface
* author: R. Neshta
* written:01/06/17
* last modified: 01/06/17
****/

#ifndef _CARRAY_H_
#define _CARRAY_H_

#include <string.h>
#include <stdio.h>

namespace lab1{

	class cArray{

		// The minimum number of element slots to allocate if a size increase is necessary. 
#define GROWBY 10

	public:

		// Constructs an empty array.
		cArray(void){ buf = new int[GROWBY]; size = GROWBY; }
		
		~cArray(void){ delete[]buf; }


		// Attributes
		// Gets the number of elements in this array.
		int Getsize() const{ return size; }
		
		// Gets the number of elements in this array.
		int Getcount() const{ return counter; }


		// Returns the largest valid index.
		int Getupperbound() const;
		
		// Determines whether the array is empty.
		bool IsEmpty()const{ return counter == 0; }
		
		// Establishes the size of an empty or existing array; allocates memory if necessary.
		void SetSize(int nnewsize);



		// Operations
		// Frees all unused memory above the current upper bound.
		// This function has no effect on the upper bound of the array.
		void FreeExtra();

		// Removes all the elements from this array.
		void RemoveAll(){ counter = 0; }

		// Element Access
		// Returns the value at a given index.
		int GetAt(int indx)const{ if (buf) return buf[indx]; }
		
		// Sets the value for a given index; array not allowed to grow.
		void SetAt(int n, int indx){ if (buf) buf[indx] = n; }

		// Growing the Array
		// Adds an element to the end of the array; grows the array if necessary.
		void Add(int);

		// Appends another array to the array; grows the array if necessary
		void Append(cArray *);

		// Copies another array to the array; grows the array if necessary.
		void Copy(cArray *);

		// Insertion/Removal
		// Inserts an element at a specified index.
		void InsertAt(int n, int indx){ buf[indx] = n; }

		// Removes an element at a specific index.
		void RemoveAt(int);

		// Operators
		// Sets or gets the element at the specified index.
		int& operator[](int i){ return buf[i]; }

	private:
		// put your own data members here

		int *buf = NULL, size = 0, counter = 0;

	};

}

#endif /*_CARRAY_H_*/
