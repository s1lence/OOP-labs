/***********************************************************************
*file:"DoublyLinkedList.cpp"
*synopsis: implementation of DoublyLinkedList class interface
*author: R. Neshta
*written: 01/06/17
*last modified:01/06/17
***********************************************************************/



#include "DoublyLinkedList.h"

using namespace lab4;

DoublyLinkedList::~DoublyLinkedList(){

	clear();

}


// returns length of the list
int DoublyLinkedList::size() const{

	ListNode *ptr;

	int i;
	ptr = head;

	for (i = 0; ptr; ptr = ptr->next)
		++i;

	return i;

}


// deletes all list
void DoublyLinkedList::clear(){

	ListNode *ptr;

	while (head){

		ptr = head;
		head = head->next;

		delete ptr;

	}

}

// Adds node to the end of the list.
void DoublyLinkedList::push_back(const ListNode &nd){

	ListNode *ptr = this->head;

	if (this->empty()){

		this->head = new ListNode(nd.data);

		return;

	}

	while (ptr->next)
		ptr = ptr->next;

	ptr->next = new ListNode(nd.data);
	ptr->next->prev = ptr;

}

// Adds node to the front of the list.
void DoublyLinkedList::push_front(const ListNode &nd){

	if (!head){
	
		push_back(nd);

		return;

	}

	head->prev = new ListNode(nd.data);

	head->prev->next = head;
	head = head->prev;

}

// Removes the first element of the list.
void DoublyLinkedList::pop_front(){

	ListNode *tmp;

	if (!head)
		return;

	tmp = head->next;
	tmp->prev = nullptr;

	delete head;
	head = tmp;

}

// Removes the last element of the list.
void DoublyLinkedList::pop_back(){

	ListNode *tmp, *ptr;

	if (!head)
		return;

	tmp = head;
	while (tmp->next)
		tmp = tmp->next;

	ptr = tmp->prev;
	ptr->next = nullptr;

	delete tmp;

}

//Inserts node preserving list ordering
void DoublyLinkedList::insert_ord(const ListNode &nd){

	ListNode *ptr;
	ptr = head;

	while (ptr && strcmp(nd.data, ptr->data) > 0)
		ptr = ptr->next;

	if (!ptr){

		push_back(nd);
		return;

	}

	insert_after(ptr->data, nd);

}

//Sorts list in nondescending order
void DoublyLinkedList::sort(){

	int size = this->size();
	const char* *arr = new const char*[size];
	
	ListNode* node = head;

	for (int i = 0; i < size; ++i, node = node->next)
		arr[i] = node->data;

	//qsort(arr, size, sizeof(char*), strcmp);

	for (int i = 0; i < size; ++i, node = node->next)
		strcpy(node->data, arr[i]);

	/*ListNode *ptr_end, *ptr, *tmp;
	bool swapped = true;

	if (nullptr == (ptr_end = head))
		return;

	while (ptr_end->next)
		ptr_end = ptr_end->next;

	while (ptr_end && swapped){

		swapped = false;
		ptr = head->next;

		while (ptr != ptr_end){

			if (strcmp(ptr->prev->data, ptr->data) > 0){

				tmp = ptr->prev;
				tmp->next = ptr->next;

				ptr->prev = tmp->prev;
				ptr->next = tmp;

				tmp->prev = ptr;
				swapped = true;

			}

			ptr = ptr->next;

		}

		ptr_end = ptr_end->prev;

	}*/

}

// Inserts nd after the node with dat. Returns true on success
bool DoublyLinkedList::insert_after(char *dat, const ListNode &nd){

	ListNode *ptr1, *ptr2;

	ptr1 = head;

	while (ptr1 && strcmp(ptr1->data, dat))
		ptr1 = ptr1->next;

	if (!ptr1)
		return false;

	ptr2 = ptr1->next;
	ptr1->next = new(ListNode);

	ptr1->next->data = nd.data;
	ptr1->next->prev = ptr1;

	ptr1->next->next = ptr2;

	if (ptr2)
		ptr2->prev = ptr1->next;

	return true;

}

// Overloaded of the assignment operator
void DoublyLinkedList::operator=(const DoublyLinkedList &nd){

	ListNode *ptr;

	if (head != nd.head){

		if (head)
			clear();

		ptr = nd.head;
		while (ptr){

			push_back(*ptr);
			ptr = ptr->next;

		}

	}

}

//Removes the elements from the argument list, inserts them into the target list,
//and orders the new, combined set of elements in nondescending order
void DoublyLinkedList::merge(DoublyLinkedList &nd){

	ListNode * ptr = head;

	while (ptr->next)
		ptr = ptr->next;

	ptr->next = nd.head;
	nd.head->prev = ptr;

	nd.head = nullptr;

	//sort();

}

// Removes all nodes with dat
void DoublyLinkedList::erase(char *dat){

	ListNode *must_die, *ptr = head;

	ListNode searched(dat);

	while (ptr){

		/*
		 * if and else branches have same statement:
		 * ptr = ptr->next;
		 * it's not an error or misunderstanding.
		 * it is necessary to increment pointer before
		 * destruction any element to be sure that
		 * any element was missed in list
		 */

		if (searched == *ptr){

			must_die = ptr;
			ptr = ptr->next;

			if (nullptr == must_die->prev)
				pop_front();
			else
				_del_mid_o_back(*must_die);

		}
		else
			ptr = ptr->next;

	}

}

// Removes adjacent duplicate elements or adjacent elements
void DoublyLinkedList::unique(){

	ListNode *ptr;

	if (nullptr == (ptr = head))
		return;

	while (ptr && ptr->next){

		if (!strcmp(ptr->data, ptr->next->data))
			_del_mid_o_back(*ptr->next);

		ptr = ptr->next;

	}

}

// deletes elements from argument list between first and last
// positions and adds them to the end of target list
void DoublyLinkedList::assign(DoublyLinkedList &dl, int first, int last){

	ListNode *firstNode, *lastNode, *after = head;

	firstNode = dl.head;
	for (int i = 0; i < first && firstNode->next; ++i, firstNode = firstNode->next);

	lastNode = firstNode;
	for (int i = first; i < last && lastNode->next; ++i, lastNode = lastNode->next);

	if (nullptr == after){

		head = firstNode;
		firstNode->prev->next = lastNode->next;

		if (lastNode->next)
			lastNode->next->prev = firstNode->prev;

		firstNode->prev = lastNode->next = nullptr;

		return;

	}

	while (after->next)
		after = after->next;

	firstNode->prev->next = lastNode->next;

	if (lastNode->next)
		lastNode->next->prev = firstNode->prev;

	lastNode->next = nullptr;

	after->next = firstNode;
	firstNode->prev = after;

	/*ListNode *ptr, *nd;
	int i = 0;
	if (dl.empty())
	return;
	ptr = dl.head;
	while (ptr){
	i++;
	/*if (i >= first && i <= last){
	push_back(*ptr);
	nd = ptr->next;
	dl._del_mid_o_back(*ptr);
	}
	ptr = nd;
	if (i > last)
	break;*-/
	if (i >= first){
	if (i <= last){
	push_back(*ptr);
	nd = ptr->next;
	dl._del_mid_o_back(*ptr);
	ptr = nd;
	}
	else
	break;
	}
	else
	ptr = ptr->next;
	}*/
}

// inserts elements of 
// argument list in target list starting from 
// where position
void DoublyLinkedList::splice(int where, const DoublyLinkedList &dl){


	this->splice(where, dl, 0, dl.size() - 1);

	/*
	//int i = 0;

	//if (nullptr == (ptr = head))
	//	*this = dl;

	//while (ptr->next && ++i <= where)
	//	ptr = ptr->next;
	//tmp = dl.head;
	//while (tmp){
	//	insert_after(ptr->data, *tmp);
	//	tmp = tmp->next;
	//}*/
	/*if (!head){
	*this = dl;
	return;
	}
	tmp = dl;
	while (head->prev)
	head = head->prev;
	ptr = head;
	while (ptr){
	if (++i <= where)
	tmp.push_front(*ptr);
	else
	tmp.push_back(*ptr);
	ptr = ptr->next;
	}
	clear();
	*this = tmp;*/
}

// inserts elements of argument list from first to 
// last positions in target list starting from  
// where position
void DoublyLinkedList::splice(int where, const DoublyLinkedList &dl, int first, int last){

	ListNode *firstNode, *lastNode, *after = head;

	if (nullptr == after)
		return;

	for (int i = 0; i < where && after->next; ++i, after = after->next);

	firstNode = dl.head;
	for (int i = 0; i < first && firstNode->next; ++i, firstNode = firstNode->next);

	lastNode = firstNode;
	for (int i = first; i < last && lastNode->next; ++i, lastNode = lastNode->next);

	while (firstNode != lastNode->next){

		ListNode *tmp = after->next;
		after->next = new ListNode(firstNode->data);

		after->next->prev = after;
		after->next->next = tmp;

		if (nullptr != tmp)
			tmp->prev = after->next;

		after = after->next;
		firstNode = firstNode->next;

	}

	// searching correct postiton:
	/*for (int i = 0; i < where && after->next; ++i, after = after->next);

	ListNode *tmpNode = after->next;

	after->next = tmp.head;
	tmp.head->prev = after;

	tmp.head = nullptr;

	ListNode *insertionTail = after->next;

	while (insertionTail->next)
	insertionTail = insertionTail->next;

	insertionTail->next = tmpNode;
	tmpNode->prev = insertionTail;*/


	/*ListNode *ptr, *tmp;
	int i = 0, j = 0;

	tmp = dl;
	while (tmp.head->prev)
	tmp.head = tmp.head->prev;
	while (++i < first)
	tmp.pop_front();
	while (++i <= last)
	tmp.head = tmp.head->next;
	while (tmp.head->next)
	tmp.pop_back();
	i = 0;
	if (!head){
	*this = tmp;
	return;
	}
	while (head->prev)
	head = head->prev;
	ptr = head;
	while (++i <= where && ptr){
	tmp.push_front(*ptr);
	ptr = ptr->next;
	}
	while (ptr){
	tmp.push_back(*ptr);
	ptr = ptr->next;
	}
	clear();
	*this = tmp;*/
}

// prints list
void DoublyLinkedList::print()const{

	ListNode *ptr;
	if (this->empty()){

		std::cout << "List is empty" << std::endl;
		return;

	}

	ptr = head;
	while (ptr){

		std::cout << ptr->data << " ";
		ptr = ptr->next;

	}

	std::cout << std::endl;

}

// prints list backward
void DoublyLinkedList::print_bkw()const{

	ListNode *ptr;
	if (this->empty()){

		std::cout << "List is empty" << std::endl;
		return;

	}

	ptr = head;

	while (ptr->next)
		ptr = ptr->next;

	while (ptr){

		std::cout << ptr->data << " ";
		ptr = ptr->prev;

	}

	std::cout << std::endl;

}

// additional functions

// deleting element from the middle of the list and from the end of the list
void DoublyLinkedList::_del_mid_o_back(ListNode &nd){

	ListNode *tmp = nd.next;

	if (nullptr == tmp){

		nd.prev->next = nullptr;
		delete &nd;

		nd = nullptr;
		return;

	}

	nd.prev->next = tmp;
	tmp->prev = nd.prev;

	delete &nd;
	nd = *tmp;

}
