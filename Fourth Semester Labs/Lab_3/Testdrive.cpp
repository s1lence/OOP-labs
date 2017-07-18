/************************************************
* file: "Testdrive.cpp"
* synopsis: testing third labs
* author: R. Neshta
* written: 17/07/17
* last modified: 19/07/17
***********************************************/

#include<iostream>

using std::cout;
using std::endl;

#include"Library.h"
#include"Tickets.h"
#include"Station.h"
#include"Dictionary.h"

using namespace lab3;

int main(){

	/*
	*
	*	Uncomment any line below to see some result in console(ctors required).
	*	All four variant checked. They all works. Hope You'll enjoy :]
	*
	*/

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
		std::vector < library::CTreeNode* >> callable(&t, nullptr, utility::Operations::PRINT_N_DELETE_ALL, &trash);

	t.apply2All(callable); // direct call from client code
	std::cout << t.isEmpty() << std::endl;
	*/
	
	/* tickets tests */
	/*
	tickets::CBinTree ts("../Lab_3/tickets.csv");

	// ts.print();

	
	tickets::CTreeNode nd("Julyany;121;Mr. Watson;9/11/01");
	ts.addApplication(nd);

	//ts.print();
	
	ts.printNdelete(12, "19/07/17");
	
	ts.deleteApplication(24, "Mr. Smith", "21/07/17");
	std::cout << "after" << std::endl;
	ts.print();
	*/

	/* station tests */
	/*
	station::CBinTree st("../Lab_3/station.csv");

	std::vector<station::CTreeNode*> v;


	st.findByNumber(3, &v);

	for (auto &i : v)
		i->print();

	/*
	st.deleteTrain(1);
	st.deleteTrain(6);
	st.deleteTrain(8);

	st.print();
	/*
	st.getStationInfo("Vydubychi", &v);

	for (auto &i : v)
		i->print();

	*/

	/* dictionary tests */
	/*
	dictionary::CBinTree dc("../Lab_3/dictionary.csv");
	
	dc.print();

	std::cout << "English: Incredible" << std::endl << "Italian: " << dc["Incredible"] << std::endl;

	dc.deleteByWord("Incredible");
	dc.print();

	std::vector<dictionary::CTreeNode*> v;
	dc.getPageInfo(56, &v);

	std::cout << "56 page:" << std::endl;
	for (auto &i : v)
		i->print();/*
*/

	return 0;
}