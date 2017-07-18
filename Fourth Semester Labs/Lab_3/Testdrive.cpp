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
	// t.print();

	utility::Appliable < library::CBinTree,
		common::ProtectedBinaryNodeInterface<library::CTreeNode>,
		std::vector < library::CTreeNode* >> callable(&t, nullptr, utility::Operations::PRINT_N_DELETE);

	t.apply2All(callable);

	return 0;
}