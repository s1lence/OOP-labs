/***********************************************************************
*file:"ListNode.h"
*synopsis: ListNode class interface
*author: R. Neshta
*written: 01/06/17
*last modified:01/06/17
***********************************************************************/

#ifndef _LISTNODE_H_
#define _LISTNODE_H_

namespace lab4{

	class ListNode{

		char *data;

		ListNode *prev;
		ListNode *next;

	public:

		friend class DoublyLinkedList;

		inline ListNode() :data(nullptr), prev(nullptr), next(nullptr){};//default constructor

		inline ListNode(char *_data) :data(_data), prev(nullptr), next(nullptr){};

		inline ~ListNode(void){};

		inline bool operator==(const ListNode& node){ return (0 == strcmp(data, node.data)); }

	};
	
}

#endif /*_LISTNODE_H_*/
