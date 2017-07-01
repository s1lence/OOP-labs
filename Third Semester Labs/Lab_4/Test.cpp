/***********************************************************************
*file:"Test.cpp"
*synopsis: DoublyLinkedList class tests
*author: R. Neshta
*written: 01/06/17
*last modified:01/06/17
***********************************************************************/


#include "DoublyLinkedList.h"

using namespace lab4;
using std::cout;
using std::endl;

int main(){

	// ctors, push_back, push_front, print
	DoublyLinkedList Lst1, Lst2;
	ListNode nd("data"), nd1("elephant"), nd2("shit");

	Lst1.push_back(nd);
	Lst1.push_front(nd2);

	Lst1.push_back(nd1);

	cout <<  "Tests ctors, push_back, push_front, print:" << endl << "first list:" << endl;
	Lst1.print();

	// insert_ord && insert_after
	cout << endl << endl << "Test insert_ord && insert_after:" << endl << "first list before:" << endl;
	Lst1.print();

	Lst1.insert_ord(ListNode("big_dick"));

	cout<< "first list after:" << endl;
	Lst1.print();


	// assign
	Lst2.assign(Lst1, 2, 3);

	cout << endl<<"Test assign:" << endl << "2nd one:" << endl;
	Lst2.print();

	cout << "first list:" << endl;
	Lst1.print();


	// splice(int, const DoublyLinkedList&)
	Lst2.splice(3, Lst1);

	cout << endl << "Tests splice:" << endl << "2nd one:" << endl;
	Lst2.print();

	Lst2.splice(2, Lst1,0,1);

	cout << endl << "2nd one:" << endl;
	Lst2.print();


	// erase
	cout << endl << "Test erase:" << endl << "first before:" << endl;
	Lst1.print();

	Lst1.erase("shit");

	cout << "first after:" << endl;
	Lst1.print();


	// unigue
	Lst2.unique();

	cout << endl << "Test unique:" << endl << "2nd one:" << endl;
	Lst2.print();


	// merge
	Lst2.merge(Lst1);

	cout << endl << "Test merge:" << endl << "2nd one:" << endl;
	Lst2.print();

	Lst2.clear();
	Lst2.push_front(ListNode("text"));

	Lst1.push_back(ListNode("string"));

	Lst1.merge(Lst2);

	cout << endl << "Test merge:" << endl << "2nd one:" << endl;
	Lst1.print_bkw();


	return 0;


}