/*
 * `file` 			List.h
 * `written` 		July 23 2017 21:32:32
 * `last modified`	July 27 2017 0:52:43
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		list class interface
 *
 *	Description: 	list is common template class that holds single linked list and manages memory operations
 *
 *	`note`			none
 */
 

#ifndef _LIST_H_
#define _LIST_H_

#include<iostream>

#include "Iterator.h"

namespace lab4{

	namespace list{
	
		template <class T>
		class List{

			struct ListNode{
				T data;
				ListNode * next;
				ListNode() :next(nullptr){}
				ListNode(T dat) :data(dat), next(nullptr){}
				void Print(){ std::cout << data << std::endl; }
			};

		public:
			
			typedef ListNode node_type;
			typedef lab4::iterator::_iterator<ListNode> iterator;

			//constructors / destructor
			List() :head(nullptr), first(nullptr), last(nullptr){}
			~List(){ clear(); }

			//methods
			iterator begin(){ return first; }//Returns an iterator addressing the first element 
			iterator end(){ return last; }//Returns an iterator that addresses the location 
			//succeeding the last element


			void clear();//Erases all the elements of a list.
			bool empty(){ return nullptr == head; }//Tests if a list is empty.

			iterator find(const node_type & val);//Returns an iterator to the 
			// first element in a list that 
			//match a specified value.

			void pop_front();//Deletes the element at the beginning of a list.

			void push_front(const node_type val);//Adds an element to the beginning 
			//of a list.
			void remove(const node_type val);//Erases first element in a list that 
			//match a specified value.


			int size();//Returns the number of elements in a list.

			void splice(iterator _Where, List<T>& _Right);//Removes element from 
			//the target list and inserts it in first
			// position of the argument list.
			
			void Print();//Dumps list into the screen
		private:
			node_type *head;
			iterator first, last;
		};

	}

}

#ifndef _LIST_IMPLEMENTATION_
#include "List.cpp"
#endif /* _LIST_IMPLEMENTATION_ */

#endif /* _LIST_H_ */