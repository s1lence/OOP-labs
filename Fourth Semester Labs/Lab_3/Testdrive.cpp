/************************************************
* file: "Testdrive.cpp"
* synopsis: testing third lab
* author: R. Neshta
* written: 17/07/17
* last modified: 18/07/17
***********************************************/

#include<iostream>

using std::cout;
using std::endl;

#include"Library.h"
#include"Station.h"

using namespace lab3;

int main(){

	/* library tests */
	/*
	library::CBinTree t("../Lab_3/library.csv");

	
	std::cout << "Library has:" << std::endl;
	
	library::CTreeNode book("10;Stewen King;The Gunslinger;2000;10");
	t.addBook(book);

	t.deleteBook(5);

	library::CTreeNode book2("5;Stewen King;The Shining;2012;7");
	t.addBook(book2);

	// 
	// t.print();

	// std::cout << t.height();

	t.printBackward();


	/*
	std::vector<library::CTreeNode*> v;
	t.findByAuthor("Stewen King", &v);
	for (auto &i : v)
		i->print();


	/*
	std::vector<library::CTreeNode*> trash;

	utility::Appliable < library::CBinTree,
		common::ProtectedBinaryNodeInterface<library::CTreeNode>,
		std::vector < library::CTreeNode* >> callable(&t, nullptr, utility::Operations::PRINT_N_DELETE, &trash);

	t.apply2All(callable); // direct call from client code
	std::cout << t.isEmpty() << std::endl;
	*/
	
	/* station tests */

	station::CBinTree st("../Lab_3/station.csv");

	std::vector<station::CTreeNode*> v;

	// st.print();

	st.getStationInfo("Vydubychi", &v);

	for (auto &i : v)
		i->print();


	return 0;
}