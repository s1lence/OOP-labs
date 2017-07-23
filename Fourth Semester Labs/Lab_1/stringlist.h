/*
 * `file` 			stringlist.h
 * `written` 		July 23 2017 7:57:40
 * `last modified`	July 23 2017 19:44:07
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		string list class interface
 *
 *	Description: 	string list class hold and manages doubly linked list with strings
 *					memory management according to RAII
 *
 *	`note`			none
 */
 

#ifndef _STRINGLIST_H_
#define _STRINGLIST_H_

#include <string.h>
#include <stdio.h>

namespace lab1{

	namespace stringlist{
	
		struct ListNode{
			char *str;
			ListNode* next;
			ListNode* prev;

			ListNode() :str(nullptr), next(nullptr), prev(nullptr){}
			~ListNode(){}
		};

		typedef const ListNode* POSITION;

		class StringList{
			
			/* 
			 * `class 			StringList
			 *
			 * `in 				lab1::stringlist
			 *
			 * `synopsis 		string list holds strings in doubly linked list
			 *
			 * DESCRIPTION: 	nodes holds c strings and class manages memory control
			 *					about list and strings inside it
			 *
			 * `notes 			none
			 *
			 * `author 			R. Neshta
			 *
			 * `version 		1.0
			 *
			 * `date 			July 23 2017 8:06:13
			 *
			 * Contact: 		Ruslan.Neshta@gmail.com
			 *
			 */
			 
		public:
			//Constructs an empty list for ListNode objects.
			StringList(void) :size(0), head(nullptr), tail(nullptr), iterator(nullptr){}
			~StringList(void){ RemoveAll(); }

			//Head/Tail Access 
			//Returns the head element of the list 
			POSITION GetHead(){ return head; }
			//Returns the tail element of the list 
			POSITION GetTail(){ return tail; }

			//Operations 
			//Adds an element to the head of the list (makes a new head).
			void AddHead(const char *);
			//Adds all the elements in another list to the head of the list (makes a new head).
			void AddHead(const StringList *);
			//Adds an element to the tail of the list (makes a new tail).
			void AddTail(const char *);
			//Adds all the elements in another list to the tail of the list (makes a new tail).
			void AddTail(const StringList *);
			//Removes all the elements from this list.
			void RemoveAll();
			//Removes the element from the head of the list.
			void RemoveHead();
			//Removes the element from the tail of the list.
			void RemoveTail();
			void AppendExclusively(const StringList *);
			void Splice(POSITION where, StringList *sl, POSITION first, POSITION last);
			//removes all duplicate elements
			void Unique();


			//Iteration 
			//Gets the next element for iterating.
			POSITION GetNext(){ return iterator ? iterator = iterator->next : nullptr; }
			//Gets the previous element for iterating.
			POSITION GetPrev(){ return iterator ? iterator = iterator->prev : nullptr; }


			//Retrieval/Modification
			POSITION GetHeadPosition(){ return iterator = head; }


			//Gets the element at a given position.
			const char* GetAt(int)const;
			//Removes an element from this list as specified by position.
			void RemoveAt(int);
			//Sets the element at a given position.
			void SetAt(char *, int);

			//Insertion 
			//Inserts a new element after a given position.
			void InsertAfter(char *, int);
			//Inserts a new element before a given position.
			void InsertBefore(char *, int);

			//Searching 
			//Gets the position of an element specified by string value.
			POSITION Find(char *);
			//Gets the position of an element specified by a zero-based index.
			int FindIndex(char *)const;

			//Status 
			//Returns the number of elements in this list.
			int Getsize()const{ return size; }
			//Tests for the empty list condition (no elements).
			bool IsEmpty()const{ return 0 == size; }
			//Prints out stored data
			void Printnode(POSITION p)const{ printf("%s\n", p->str); }

		private:
			//put your own data members here

			int size;
			ListNode * head;
			ListNode * tail;

			POSITION iterator;
		};

		
	}
	
}
  
#endif /* _STRINGLIST_H_ */