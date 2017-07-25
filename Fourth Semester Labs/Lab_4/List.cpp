/*
 * `file` 			List.cpp
 * `written` 		July 24 2017 8:26:50
 * `last modified`	July 24 2017 8:26:50
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		list class implementation
 *
 *	Description: 	list is common template class that holds single linked list and manages memory operations
 *
 *	`note`			none
 */
 

#ifndef _LIST_IMPLEMENTATION_
#define _LIST_IMPLEMENTATION_

#ifndef _LIST_H_
#include "List.h"
#endif /* _LIST_H_ */

namespace lab4{

	namespace list{
	

		template <class T>
		void List<T>::clear()
		{
			iterator current = first, next = first->next;

			while (current){
				delete *current;
				current = next;

				if (next)
					next = next->next;
			}
		}

		template <class T>
		typename List<T>::iterator List<T>::find(const node_type & val)
		{
			iterator it = first;
			while (it && it->data != val.data){
				it = it->next;
			}

			return it;
		}

		template <class T>
		void List<T>::pop_front()
		{
			iterator it = first;

			if (it){
				first = first->next;
				head = head->next;
			}

			delete *it;
		}

		template <class T>
		void List<T>::push_front(const node_type val)
		{
			node_type * tmp = new ListNode(val.data);
			tmp->next = head;
			head = tmp;
			first = head;
		}

		template <class T>
		void List<T>::remove(const node_type val)
		{
			iterator it = first, backup = nullptr;
			while (it && it->data != val.data){
				backup = it;
				it = it->next;
			}

			if (it){
				if (backup)
					backup->next = it->next;

				if (it == last)
					last = backup;

				if (it == first)
					first = first->next;

				delete *it;
			}
		}

		template <class T>
		int List<T>::size()
		{
			int size = 0;
			for (iterator it = first; it != nullptr; it = it->next, ++size);

			return size;
		}

		template <class T>
		void List<T>::splice(iterator _Where, List<T>& _Right)
		{
			iterator it = first;
			if (_Where != first){
				for (; it && it->next != _Where; it = it->next);

				it->next = _Where->next;
				if (nullptr == it->next)
					last = it;
			}
			else {
				if (first == last)
					last = last->next;

				first = _Where->next;
				head = first;
			}

			_Where->next = _Right.head;
			_Right.head = _Where;
			_Right.first = _Where;
		}

		template <class T>
		void List<T>::Print()
		{
			for (iterator it = first; it != nullptr; it = it->next){
				std::cout << it->data << std::endl;
			}
		}
	
	}

}

#endif /* _LIST_IMPLEMENTATION_ */