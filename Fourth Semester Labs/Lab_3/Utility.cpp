/************************************************
* file: "Utility.cpp"
* synopsis: definition utility
* author: R. Neshta
* written: 08/07/17
* last modified: 19/07/17
***********************************************/

#ifndef _UTILITY_REALISATION_
#define _UTILITY_REALISATION_

#ifndef _UTILITY_H_
#include"Utility.h"
#endif /*_UTILITY_H_*/

namespace lab3{

	namespace utility{

		template<class Self, class Comparable, class Container>
		void Appliable<Self, Comparable, Container>::operator()(Comparable &item){

			switch (option){

			case Operations::FIND_SINGLE:

				if (data && *data == item.data){
					results->push_back(&item.data);
					callable = false;
				}
				break;

			case Operations::FIND_MULTIPLE:

				if (data && *data == item.data)
					results->push_back(&item.data);
				break;

			case Operations::PRINT_N_DELETE:

				if (data && *data == item.data){
					item.data.print();
					results->push_back(&item.data);
				}
				break;

			case Operations::PRINT_N_DELETE_ALL:

				item.data.print();
				results->push_back(&item.data);
				break;

			case Operations::PRINT:

				item.data.print();
				break;
			}
		}

		template<class Self, class Comparable, class Container>
		void Appliable<Self, Comparable, Container>::eraseContainer(){

			if (option != Operations::PRINT_N_DELETE && option != Operations::PRINT_N_DELETE_ALL)
				return;

			for (auto &i : *results){
				creator->remove(creator->find(*i));
			}

		}

	}

}

#endif /*_UTILITY_REALISATION_*/