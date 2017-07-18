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

using namespace lab3;

int main(){

	library::CBinTree t("../Lab_3/library.csv");

	
	std::cout << "Library has:" << std::endl;
	
	library::CTreeNode book("10;Stewen King;The Gunslinger;2000;10");
	t.addBook(book);
	t.deleteBook(5);
	t.print();

	/*
	std::vector<library::CTreeNode*> trash;

	utility::Appliable < library::CBinTree,
		common::ProtectedBinaryNodeInterface<library::CTreeNode>,
		std::vector < library::CTreeNode* >> callable(&t, nullptr, utility::Operations::PRINT_N_DELETE, &trash);

	t.apply2All(callable); // direct call from client code
	*/

	return 0;
}