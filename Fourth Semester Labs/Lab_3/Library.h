/************************************************
* file: "Library.h"
* synopsis: declaration classes for first variant of third lab
* author: R. Neshta
* written: 12/07/17
* last modified: 12/07/17
***********************************************/


#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include<iostream>

#include"Common.h"
#include"Utility.h"

using namespace lab3;

namespace lab3{

	namespace library{
		
		class CTreeNode{
		
		public:
			// empty node is not allowed
			CTreeNode() = delete;

			// special ctor for search nodes
			CTreeNode(const char * author, const char *title, int bookid)
				: m_Bookid(bookid), m_Year(0),
				m_Quantity(0), m_Author(nullptr),
				m_Title(title){}

			// by default initialisation made with *.csv file
			CTreeNode(const char* csvData);

			// creates copy from existing node
			CTreeNode(const CTreeNode& nd)
				:m_Bookid(nd.m_Bookid), m_Year(nd.m_Year),
				m_Quantity(nd.m_Quantity), m_Author(nd.m_Author),
				m_Title(nd.m_Title){}

			// less node has less book id
			bool operator<(const CTreeNode& nd)const{ return m_Bookid < nd.m_Bookid; }

			// equality determines by specific pointers analyse
			bool operator==(const CTreeNode& nd);

			void print()const;

			int cCompare(const CTreeNode& node)const{ return m_Bookid - node.m_Bookid; }

		private:

			unsigned m_Bookid;
			unsigned m_Year;
			unsigned m_Quantity;
			const char* m_Author;
			const char* m_Title;
		};

		class CBinTree : common::ProtectedBinaryTreeInterface<CTreeNode>{
		public:

			// these is not allowed
			CBinTree() = delete;
			CBinTree(const CBinTree&) = delete;

			CBinTree(const char *csvFileName) :ProtectedBinaryTreeInterface(csvFileName){}

			void addBook(CTreeNode&);

			void deleteBook(unsigned bookid);

			void findByAuthor(
				utility::Appliable<
				CBinTree, 
				const char*, 
				common::ProtectedBinaryNodeInterface<CTreeNode>, 
				std::vector<CTreeNode*>> &what2call);

			void findByName(
				utility::Appliable<
				CBinTree, 
				const char*, 
				common::ProtectedBinaryNodeInterface<CTreeNode>, 
				std::vector<CTreeNode*>> &what2call);

		};

	}
}

#endif /*_LIBRARY_H_*/
