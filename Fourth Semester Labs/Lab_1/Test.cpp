/***
* file:"carray.h"
* synopsis: carray class interface
* author: R. Neshta
* written:01/06/17
* last modified: 01/06/17
****/

#include <iostream>

#include "cArray.h"

using namespace lab1;
using std::cout;
using std::endl;

int main(){

	cArray A, B;
	
	cout << "size: \n" << A.Getsize() << endl;
	A.SetSize(21);
	
	cout << "size: \n" << A.Getsize() << endl;
	
	A.Add(1);
	A.Add(2);
	
	A.FreeExtra();
	cout << "size: \n" << A.Getsize() << endl;
	
	for (int i = 0; i <= A.Getupperbound(); i++)
		cout << "A[" << i << "]=" << A[i] << "\n";
	cout << endl;
	
	B.Copy(&A);
	for (int i = 0; i < 3; i++)
		B.Append(&A);
	
	A.RemoveAll();
	if (A.IsEmpty())
		cout << "A is empty" << endl;
	else
		cout << "A isn't empty" << endl;
	
	for (int i = 0; i <= B.Getupperbound(); i++)
		cout << "B[" << i << "]=" << B[i] << "\n";
	cout << endl;
	
	B.InsertAt(21, 3);
	B.RemoveAt(7);
	
	for (int i = 0; i <= B.Getupperbound(); i++)
		cout << "B[" << i << "]=" << B[i] << "\n";
	
	return 0;

}