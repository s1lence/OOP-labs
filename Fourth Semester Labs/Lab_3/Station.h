/************************************************
* file: "Station.h"
* synopsis: declaration classes for third variant of third lab
* author: R. Neshta
* written: 18/07/17
* last modified: 18/07/17
***********************************************/

#ifndef _STATION_H_
#define _STATION_H_

#include<iostream>

#include"Common.h"
#include"Utility.h"

using namespace lab3;

namespace lab3{

	namespace station{

		class CTreeNode{
		public:
			// empty node is not allowed
			CTreeNode() = delete;

			// special ctor for search nodes
			CTreeNode(const char * destination, int number) : m_Destination(destination), m_TrainNumber(number){}

			// by default initialisation made with *.csv file
			CTreeNode(const char* csvData);

			// creates copy from existing node
			CTreeNode(const CTreeNode& nd) :
				m_DepartureTime(nd.m_DepartureTime),
				m_Destination(nd.m_Destination),
				m_TrainNumber(nd.m_TrainNumber){}

			~CTreeNode(){}

			// less node has less book id
			bool operator<(const CTreeNode& nd)const{ return m_TrainNumber < nd.m_TrainNumber; }

			// equality determines by specific pointers analyse
			bool operator==(const CTreeNode& nd);

			void print()const;

			void cleanStrings();
		private:

			unsigned m_TrainNumber;
			const char* m_Destination;
			const char* m_DepartureTime;

		};

		class CBinTree : common::ProtectedBinaryTreeInterface<CTreeNode>{
		public:
			
			// these is not allowed
			CBinTree() = delete;
			CBinTree(const CBinTree&) = delete;

			CBinTree(const char *csvFileName) :ProtectedBinaryTreeInterface(csvFileName){}

			void deleteTrain(unsigned number);

			void getStationInfo(const char *name,std::vector<CTreeNode*> *p2vector);

			void findByNumber(unsigned number, std::vector<CTreeNode*> *p2vector);

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

#endif /* _STATION_H_ */
