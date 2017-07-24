/************************************************
* file: "Utility.h"
* synopsis: declaration utility for common apply function
* author: R. Neshta
* written: 14/07/17
* last modified: 19/07/17
***********************************************/

#ifndef _UTILITY_H_
#define _UTILITY_H_

namespace lab3{

	namespace utility{

		// describes what operations allowed in Appliable class
		enum class Operations{ FIND_SINGLE, FIND_MULTIPLE, PRINT_N_DELETE, PRINT_N_DELETE_ALL, PRINT };

		template<class Self, class Comparable, class Container>
		class Appliable{

			/*
			*	Template relations:
			*	class Self expected to be derived from ProtectedBinaryTreeInterface;
			*	class Comparable requires to be ProtectedBinaryNodeInterface and be able 
			*		to print out his stored members;
			*	class Container required to have push_back function.
			*
			*	This class requires Container holding pointers to Comparable,
			*	otherwise - expected behavior can't be guaranteed.
			*
			*/

		public:

			// these is not allowed
			Appliable() = delete;
			Appliable(const Appliable&) = delete;

			/* *item2compare must be created and handle it's destruction outside */
			Appliable(Self * whoCalls, Comparable *item2compare, Operations whatToDo, Container *storage) :
				data(item2compare),
				option(whatToDo),
				creator(whoCalls),
				results(storage){}

			~Appliable(){}

			void operator()(Comparable &item);

			bool isValid()const{ return callable; }

			void eraseContainer();

			void setOperationTo(Operations op){ option = op; }

		private:
			bool callable = true; // permission to call
			Comparable *data; // data which will be compared
			Container *results; // container for storing searched elements
			Operations option; // operation performed
			Self *creator; // pointer to object derived from ProtectedBinaryTreeInterface
		};

		template<class S,class C1, class C2>
		bool operator==(std::nullptr_t null, Appliable<S, C1, C2>& obj){ return !obj.isValid(); }

		template<class S, class C1, class C2>
		bool operator!=(std::nullptr_t null, Appliable<S, C1, C2>& obj){ return obj.isValid(); }
	}

}

#ifndef _UTILITY_REALISATION_
#include"Utility.cpp"
#endif /*_UTILITY_REALISATION_*/

#endif /*_UTILITY_H_*/
