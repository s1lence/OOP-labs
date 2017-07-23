/*
 * `file` 			Test.cpp
 * `written` 		01/06/17
 * `last modified`	July 23 2017 7:51:30
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		this is test drive file
 *
 *	Description: 	testing platform  for all four variants
 *
 *	`note`			none
 */
 
 
#include <iostream>

#include "cArray.h"
#include "multistring.h"

using namespace lab1;
using std::cout;
using std::endl;

int main(){

	/*
	 *	multi string tests
	 */
	/*
	multistring::MultiString m(5),v;
	m.SetAt(0, "string at 0 position");
	m.SetAt(1, "string at 1 position");
	m.SetAt(2, "string at 2 position");
	m.SetAt(3, "string at 3 position");
	m.SetAt(4, "string at 4 position");

	std::cout << "vector m:" << std::endl;
	for (int i = 0; i < 5; ++i){
		m.PrintStr(i);
		std::cout << std::endl;
	}
	std::cout.flush();
	v = m;

	std::cout << "vector v copy-assigned from m:" << std::endl;
	for (int i = 0; i < 5; ++i){
		v.PrintStr(i);
		std::cout << std::endl;
	}


	v += m;
	std::cout << "vector v after v+=m operation:" << std::endl;
	for (int i = 0; i < 5; ++i){
		v.PrintStr(i);
		std::cout << std::endl;
	}

	m.SetAt(2, v[2]);
	multistring::MultiString &merged = v.MergeMultiStringExclusive(m);
	for (int i = 0; i < merged.GetLength(); ++i)
		merged.PrintStr(i);

	std::cout << "Find test:" << std::endl << m.Find("string at 4 position") << std::endl;
	*/

	/*
	 * c string tests
	 */

	/*
	 *	c array tests
	 */
	/*
	carray::cArray A, B;
	
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
	*/

	/*
	 *	string list tests
	 */

	return 0;

}