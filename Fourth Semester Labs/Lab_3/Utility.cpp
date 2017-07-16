/************************************************
* file: "Utility.cpp"
* synopsis: definition utility
* author: R. Neshta
* written: 08/07/17
* last modified: 12/07/17
***********************************************/

#ifndef _UTILITY_REALISATION_
#define _UTILITY_REALISATION_

#ifndef _UTILITY_H_
#include"Utility.h"
#endif /*_UTILITY_H_*/

namespace lab3{

	namespace utility{

		template<class Self, class Initialiser, class Comparable, class Container>
		void Appliable<Self, Initialiser, Comparable, Container>::operator()(Comparable &item){

			switch (option){

			case Operations::FIND_SINGLE:

				if (*data == item.data){
					results.push_back(&item.data);
					callable = false;
				}
				break;

			case Operations::FIND_MULTIPLE:

				if (*data == item.data)
					results.push_back(&item.data);
				break;

			case Operations::PRINT_N_DELETE:

				item.data.print();
				creator->remove(&item);
				break;

			case Operations::PRINT:

				item.data.print();
				break;
			}
		}

		template<class Comparable>
		int compare(const Comparable &data1, const Comparable &data2){

			return data1.cCompare(data2);
		}

	}

}

#endif /*_UTILITY_REALISATION_*/