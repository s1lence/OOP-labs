/************************************************
* file: "Dictionary.h"
* synopsis: declaration classes for fourth variant of third lab
* author: R. Neshta
* written: 18/07/17
* last modified: 18/07/17
***********************************************/

#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include"Common.h"
#include"Utility.h"

namespace lab3{

	namespace dictionary{

		class CTreeNode{

		private:

			unsigned m_Page;
			const char* m_EngWord;
			const char* m_ItaWord;

		};

		class CBinTree : common::ProtectedBinaryTreeInterface<CTreeNode>{
		public:

		};

	}

}

#endif /* _DICTIONARY_H_ */
