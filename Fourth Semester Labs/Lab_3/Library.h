/************************************************
* file: "Library.h"
* synopsis: declaration classes for first variant of third lab
* author: R. Neshta
* written: 12/07/17
* last modified: 19/07/17
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
				m_Quantity(0), m_Author(author),
				m_Title(title){}

			// by default initialisation made with *.csv file
			CTreeNode(const char* csvData);

			// creates copy from existing node
			CTreeNode(const CTreeNode& nd)
				:m_Bookid(nd.m_Bookid), m_Year(nd.m_Year),
				m_Quantity(nd.m_Quantity), m_Author(nd.m_Author),
				m_Title(nd.m_Title){}

			~CTreeNode(){}

			// less node has less book id
			bool operator<(const CTreeNode& nd)const{ return m_Bookid < nd.m_Bookid; }

			// equality determines by specific pointers analyse
			bool operator==(const CTreeNode& nd);

			void print()const;

			void cleanStrings();

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

			/* required functions */
			void addBook(CTreeNode&);

			void deleteBook(unsigned bookid);

			void findByAuthor(const char* author, std::vector<library::CTreeNode*> *p2vector);

			void findByName(const char *name, std::vector<library::CTreeNode*> *p2vector);

			/* custom functions */
			void print()const;

			void apply2All(
				utility::Appliable <
				CBinTree,
				common::ProtectedBinaryNodeInterface<CTreeNode>,
				std::vector < CTreeNode* >>& );

			std::size_t height()const{ return heigth(); }

			std::size_t getDepth(common::ProtectedBinaryNodeInterface<CTreeNode>&nd)const{ return depth(nd); }

			void printBackward()const;

			bool isEmpty()const{ return empty(); }

			friend utility::Appliable<CBinTree, common::ProtectedBinaryNodeInterface<CTreeNode>, std::vector<CTreeNode*>>;

		};

	}
}

#endif /*_LIBRARY_H_*/
