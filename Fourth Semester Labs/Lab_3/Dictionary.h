/************************************************
* file: "Dictionary.h"
* synopsis: declaration classes for fourth variant of third lab
* author: R. Neshta
* written: 18/07/17
* last modified: 18/07/17
***********************************************/

#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include<iostream>

#include"Common.h"
#include"Utility.h"

using namespace lab3;

namespace lab3{

	namespace dictionary{

		class CTreeNode{
		public:
			// empty node is not allowed
			CTreeNode() = delete;

			// special ctor for search nodes
			CTreeNode(const char * word, unsigned number) : m_EngWord(word), m_Page(number){}

			// by default initialisation made with *.csv file
			CTreeNode(const char* csvData);

			// creates copy from existing node
			CTreeNode(const CTreeNode& nd) :m_Page(nd.m_Page), m_EngWord(nd.m_EngWord), m_ItaWord(nd.m_ItaWord){}

			~CTreeNode(){}

			// less node has less book id
			bool operator<(const CTreeNode& nd)const{ return strcmp(m_EngWord, nd.m_EngWord) < 0; }

			// equality determines by specific pointers analyse
			bool operator==(const CTreeNode& nd);

			void print()const;

			void cleanStrings();

			friend class CBinTree;

		private:

			unsigned m_Page;
			const char* m_EngWord;
			const char* m_ItaWord;

		};

		class CBinTree : common::ProtectedBinaryTreeInterface<CTreeNode>{
		public:

			// these is not allowed
			CBinTree() = delete;
			CBinTree(const CBinTree&) = delete;

			CBinTree(const char *csvFileName) :ProtectedBinaryTreeInterface(csvFileName){}

			void deleteByWord(const char *word);

			const char* operator[](const char *word);

			void getPageInfo(unsigned number, std::vector<CTreeNode*> *p2vector);

			void print()const;

			void apply2All(
				utility::Appliable <
				CBinTree,
				common::ProtectedBinaryNodeInterface<CTreeNode>,
				std::vector < CTreeNode* >> &);

			friend utility::Appliable<CBinTree, common::ProtectedBinaryNodeInterface<CTreeNode>, std::vector<CTreeNode*>>;

		};

	}

}

#endif /* _DICTIONARY_H_ */
