/************************************************
* file: "Tickets.h"
* synopsis: declaration classes for second variant of third lab
* author: R. Neshta
* written: 18/07/17
* last modified: 18/07/17
***********************************************/

#ifndef _TICKETS_H_
#define _TICKETS_H_

#include<iostream>

#include"Common.h"
#include"Utility.h"

namespace lab3{

	namespace tickets{
		class CTreeNode{
		public:
			// empty node is not allowed
			CTreeNode() = delete;

			// special ctor for search nodes
			CTreeNode(const char* name,const char * date, int number) :
				m_PassengerName(name),
				m_FlightDate(date), 
				m_Flight(number){}

			// by default initialisation made with *.csv file
			CTreeNode(const char* csvData);

			// creates copy from existing node
			CTreeNode(const CTreeNode& nd) :
				m_Flight(nd.m_Flight),
				m_Destination(nd.m_Destination),
				m_PassengerName(nd.m_PassengerName),
				m_FlightDate(nd.m_FlightDate){}

			~CTreeNode(){}

			// less node has less book id
			bool operator<(const CTreeNode& nd)const{ return strcmp(m_PassengerName, nd.m_PassengerName) < 0; }

			// equality determines by specific pointers analyse
			bool operator==(const CTreeNode& nd);

			void print()const;

			void cleanStrings();
		private:

			unsigned m_Flight;
			const char* m_Destination;
			const char* m_PassengerName;
			const char* m_FlightDate;

		};

		class CBinTree : common::ProtectedBinaryTreeInterface<CTreeNode>{
		public:

			// these is not allowed
			CBinTree() = delete;
			CBinTree(const CBinTree&) = delete;

			CBinTree(const char *csvFileName) :ProtectedBinaryTreeInterface(csvFileName){}

			void addApplication(CTreeNode&);

			void deleteApplication(unsigned flight, const char* name, const char *date);

			void printNdelete(unsigned flight, const char* date);

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

#endif /* _TICKETS_H_ */
