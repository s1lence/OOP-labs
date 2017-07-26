/*
 * `file` 			List.cpp
 * `written` 		July 24 2017 8:26:50
 * `last modified`	July 27 2017 0:52:43
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
			iterator current = first, next = first;
			if(nullptr != next)
				next++;
			
			while (nullptr != current){
				delete &*current;
				current = next;

				if (nullptr != next)
					next++;
			}
		}

		template <class T>
		typename List<T>::iterator List<T>::find(const node_type & val)
		{
			iterator it = first;
			while (nullptr != it && (*it).data != val.data){
				it++;
			}

			return it;
		}

		template <class T>
		void List<T>::pop_front()
		{
			iterator it = first;

			if (nullptr != it){
				first++;
				head++;
			}

			delete &*it;
		}

		template <class T>
		void List<T>::push_front(const node_type val)
		{
			List<T>::iterator tmp(new node_type(val.data));
			(*tmp).next = head;
			head = &(*tmp);
			first = head;
			if (nullptr == last)
				last = first;
		}

		template <class T>
		void List<T>::remove(const node_type val)
		{
			iterator it = first, backup = nullptr;
			while (nullptr != it && (*it).data != val.data){
				backup = it;
				++it;
			}

			if (nullptr != it){
				if (nullptr != backup)
					(*backup).next = (*it).next;

				if (it == last)
					last = backup;

				if (it == first)
					first++;

				delete &*it;
			}
		}

		template <class T>
		int List<T>::size()
		{
			int size = 0;
			for (iterator it = first; it != nullptr; ++it, ++size);

			return size;
		}

		template <class T>
		void List<T>::splice(iterator _Where, List<T>& _Right)
		{
			iterator it = first;
			if (_Where != first){
				for (; nullptr != it && (*it).next != &*_Where; it++);

				(*it).next = (*_Where).next;
				if (nullptr == (*it).next)
					last = it;
			}
			else {
				if (first == last)
					last++;

				first = (*_Where).next;
				head = &*first;
			}

			(*_Where).next = _Right.head;
			_Right.head = &*_Where;
			_Right.first = _Where;
		}

		template <class T>
		void List<T>::Print()
		{
			for (iterator it = first; it != nullptr; it++){
				std::cout << (*it).data << std::endl;
			}
		}
	
	}

}

#endif /* _LIST_IMPLEMENTATION_ */