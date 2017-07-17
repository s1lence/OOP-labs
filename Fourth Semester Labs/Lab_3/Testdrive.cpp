/************************************************
* file: "Testdrive.cpp"
* synopsis: testing third lab
* author: R. Neshta
* written: 17/07/17
* last modified: 17/07/17
***********************************************/

#include<iostream>

using std::cout;
using std::endl;

#include"Library.h"

using namespace lab3;

int main(){

	library::CBinTree t("../Lab_3/library.csv");

	

	t.print();

	return 0;
}