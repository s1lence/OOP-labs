/***********************************************************************
*file:"DoublyLinkedList.h"
*synopsis: DoublyLinkedList class interface
*author: R. Neshta
*written: 01/06/17
*last modified:01/06/17
***********************************************************************/

#ifndef _DOUBLYLINKEDLIST_H_
#define _DOUBLYLINKEDLIST_H_


#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstring>

#include"ListNode.h"


namespace lab4{

	class DoublyLinkedList{

		ListNode *head;

	public:

		// default constructor
		DoublyLinkedList(void) :head(nullptr){}

		// destructor
		~DoublyLinkedList(void);

		// member functions

		// Returns the number of elements in the list.
		int size() const;

		// Returns true if empty, false otherwise.
		inline bool empty() const{ return (head == nullptr); }

		// Removes all elements from the list.
		void clear();

		// Adds node to the end of the list.
		void push_back(const ListNode &);

		// Adds node to the front of the list.
		void push_front(const ListNode &);

		// Removes the first element of the list.
		void pop_front();

		// Removes the last element of the list.
		void pop_back();

		// Inserts node preserving list ordering
		void insert_ord(const ListNode &);

		// Sorts list in nondescending order
		void sort();

		// Inserts nd after the the node with dat. Returns true on success	
		bool insert_after(char *dat, const ListNode &nd);

		// Overloaded of the assignment operator
		void operator=(const DoublyLinkedList &);

		// Removes the elements from the argument list, inserts them into the target list,
		// and orders the new, combined set of elements in nondescending order
		void merge(DoublyLinkedList &);

		// Removes all nodes with dat
		void erase(char *dat);

		// Removes adjacent duplicate elements or adjacent elements
		void unique();

		// deletes elements from argument list between first and last 
		// positions and adds them to the end of target list 
		void assign(DoublyLinkedList &dl, int first, int last);

		//inserts elements of argument list in target list starting from where position
		void splice(int where, const DoublyLinkedList &dl);

		// inserts elements of argument list from first to 
		// last positions in target list starting from where position
		void splice(int where, const DoublyLinkedList &dl, int first, int last);

		// prints list
		void print() const;

		// prints list backward
		void print_bkw() const;

	private:
		// service functions 

		// function that deletes given node from 
		// the middle and from the end of the list
		void _del_mid_o_back(ListNode &nd);

	};

}


#endif /*_DOUBLYLINKEDLIST_H_*/
