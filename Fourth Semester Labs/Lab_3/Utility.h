/************************************************
* file: "Utility.h"
* synopsis: declaration utility for common apply function
* author: R. Neshta
* written: 14/07/17
* last modified: 18/07/17
***********************************************/

#ifndef _UTILITY_H_
#define _UTILITY_H_

namespace lab3{

	namespace utility{

		// describes what operations allowed in Appliable class
		enum class Operations{ FIND_SINGLE, FIND_MULTIPLE, PRINT_N_DELETE, PRINT };

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
			*	otherwise - expected behaviour can't be garanteed.
			*
			*/

		public:

			bool callable = true;

			// these is not allowed
			Appliable() = delete;
			Appliable(const Appliable&) = delete;

			Appliable(Self * whoCalls, Comparable *item2compare, Operations whatToDo) :
				data(item2compare),
				option(whatToDo),
				creator(whoCalls){}

			~Appliable(){ delete data; }

			void operator()(Comparable &item);

			void eraseContainer();

		private:

			Comparable *data; // data which will be compared
			Container results; // container for storing seeked elements
			Operations option; // operation performed
			Self *creator; // pointer to object derived from ProtectedBinaryTreeInterface
		};

	}

}

#ifndef _UTILITY_REALISATION_
#include"Utility.cpp"
#endif /*_UTILITY_REALISATION_*/

#endif /*_UTILITY_H_*/
