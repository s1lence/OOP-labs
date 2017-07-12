/************************************************
* file: "Library.h"
* synopsis: declaration classes for first variant of third lab
* author: R. Neshta
* written: 12/07/17
* last modified: 12/07/17
***********************************************/


#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include"Common.h"

using namespace lab3;

namespace lab3{
	namespace library{

		class CTreeNode{
		
			CTreeNode() = delete;

			// by default initialisation made with *.csv file
			CTreeNode(const char* csvData);

			CTreeNode(const CTreeNode& nd)
				:m_Bookid(nd.m_Bookid), m_Year(nd.m_Year),
				m_Quantity(nd.m_Quantity), m_Author(nd.m_Author),
				m_Title(nd.m_Title){}

			bool operator<(const CTreeNode& nd)const{ return m_Bookid < nd.m_Bookid; }

		private:

			unsigned m_Bookid;
			unsigned m_Year;
			unsigned m_Quantity;
			const char* m_Author;
			const char* m_Title;
		};

		class CBinTree : common::ProtectedBinaryTreeInterface<CTreeNode>{



		};

	}
}

#endif /*_LIBRARY_H_*/
