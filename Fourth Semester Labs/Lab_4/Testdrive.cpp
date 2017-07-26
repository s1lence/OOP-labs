/*
 * `file` 			Testdrive.cpp
 * `written` 		July 25 2017 8:25:37
 * `last modified`	July 27 2017 0:52:43
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		testing fourth lab
 *
 *	Description: 	fourth lab includes tree variants:
 *					-bus;
 *					-c file;
 *					-references.
 *					
 *	`note`			none
 */
 
#include "List.h"
#include "Bus.h"
#include "CFile.h"
#include "References.h"

int main(){
	/*
	 *	testing list functions
	 */
	/*
	lab4::list::List<int> l1,l2;
	l1.push_front(0);
	l1.push_front(1);
	l1.push_front(2);
	l1.Print();
	std::cout << "Is l2 empty:" << std::endl;
	std::cout << l2.empty() << std::endl;
	
	//l1.pop_front();
	//l1.Print();

	//l1.remove(0);
	//l1.Print();

	//std::cout << l1.size() << std::endl;
	std::cout << "l1 after splice:" << std::endl;
	l1.splice(l1.find(1), l2);
	l1.Print();
	std::cout << "l2 after splice:" << std::endl;
	l2.Print();
	*/

	/*
	 *	testing bus functions
	 *	
	 */
	/*
	char* s = "2149;144230987;Sashok";
	lab4::bus::Bus b1("Vasya Pupkin", "4967", "211556877"), b2(s), b_comp("211556877", nullptr);

	if (b1 == b_comp)
		std::cout << b1 << std::endl;

	std::cout << b2 << std::endl;
	b2.changeDriver("Ivanich");
	std::cout << b2 << std::endl;

	*/

	/*
	 *	testing c file functions
	 */
	/*
	lab4::cfile::CFile f1("example.txt;27/07/2017"), f2("another.txt", "22/07/2017"), f_comp("", "25/07/2017");

	if(f2<f_comp)
		std::cout << f2 << std::endl;

	f1.rename("new name");
	std::cout << f1 << std::endl;

	*/

	/*
	 *	testing references functions
	 */
	/*
	int* pages = new int[4];
	for (int i = 0; i < 4; ++i)
		pages[i] = i + 3 * i - 1;

	lab4::references::References r1("reference", pages, 4), r2("pointer;3 26 132;3");

	if(r2<r1)
		std::cout << r1 << std::endl;

	r2.rename("const pointer");
	std::cout << r2 << std::endl;

	*/

	return 0;
}