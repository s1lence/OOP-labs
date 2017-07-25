/*
 * `file` 			Iterator.h
 * `written` 		July 24 2017 7:03:34
 * `last modified`	July 24 2017 7:03:34
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		iterator class
 *
 *	Description: 	template class for traverse trough the container
 *
 *	`note`			this class given by task description
 */
 

#ifndef _ITERATOR_H_
#define _ITERATOR_H_

namespace lab4{

	namespace iterator{
	
		template <typename T>
		class _iterator
		{
			T* ptr;
		
		public:

			typedef T value_type;
			typedef _iterator<T> it_type;

			_iterator() { ptr = nullptr; }
			_iterator(T* _ptr) { ptr = _ptr; }

			T& operator *();
			void operator++();
			//dummy operator to keep compiler quiet
			void operator++(int);

			bool     operator==(const it_type& _iter) const;
			bool     operator!=(const it_type& _iter) const;
			bool empty(){ return ptr == nullptr; }

			T& operator->(){ return *ptr; }
		};

		template <typename T>
		T& _iterator<T>::operator *()
		{
			return *ptr;
		}

		template <typename T>
		void _iterator<T>::operator ++()
		{
			ptr = ptr->next;
		}

		template <typename T>
		void _iterator<T>::operator ++(int)
		{
			ptr = ptr->next;
		}

		template <typename T>
		bool _iterator<T>::operator ==(const it_type &_iter) const
		{
			return (ptr == _iter.ptr);
		}

		template <typename T>
		bool _iterator<T>::operator !=(const it_type &_iter) const
		{
			return !(*this == _iter);
		}

		template<class T>
		bool operator==(std::nullptr_t, _iterator<T> &it)
		{
			return nullptr == ptr;
		}

		template<class T>
		bool operator!=(std::nullptr_t, _iterator<T> &it)
		{
			return nullptr != ptr;
		}
	}

}

#endif /* _ITERATOR_H_ */