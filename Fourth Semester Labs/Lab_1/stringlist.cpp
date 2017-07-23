/*
 * `file` 			stringlist.cpp
 * `written` 		July 23 2017 16:31:58
 * `last modified`	July 23 2017 19:44:07
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		implementation of string list class
 *
 *	Description: 	each node holdes c string; resources manages automatically
 *
 *	`note`			none
 */
 
#include "stringlist.h"

void lab1::stringlist::StringList::AddHead(const char *s)
{
	ListNode * p = new ListNode;
	int len = strlen(s) + 1;
	
	p->str = new char[len];
	strncpy_s(p->str, len, s, len - 1);

	if (nullptr == head)
		tail = p;
	else{
		p->next = head;
		head->prev = p;
	}
	head = p;
	++size;
}

void lab1::stringlist::StringList::AddHead(const StringList *p2l)
{
	ListNode *p = p2l->head;

	while (p){
		AddHead(p->str);
		p = p->next;
	}
}

void lab1::stringlist::StringList::AddTail(const char *s)
{
	ListNode * p = new ListNode;
	int len = strlen(s) + 1;

	p->str = new char[len];
	strncpy_s(p->str, len, s, len - 1);

	if (nullptr == tail)
		head = p;
	else{
		p->prev = tail;
		tail->next = p;
	}
	tail = p;
	++size;
}

void lab1::stringlist::StringList::AddTail(const StringList *p2l)
{
	ListNode *p = p2l->head;

	while (p){
		AddTail(p->str);
		p = p->next;
	}
}

void lab1::stringlist::StringList::RemoveAll()
{
	ListNode *p = head;

	while (p){
		head = p->next;
		delete[] p->str;
		delete p;
		p = head;
	}
	size = 0;
}

void lab1::stringlist::StringList::RemoveHead()
{
	ListNode *p = head;

	if (nullptr == p)
		return;

	head = head->next;
	if (head)
		head->prev = nullptr;
	else
		tail = head;

	delete[] p->str;
	delete p;
	--size;
}

void lab1::stringlist::StringList::RemoveTail()
{
	ListNode *p = tail;

	if (nullptr == p)
		return;

	tail = tail->prev;
	if (tail)
		tail->next = nullptr;
	else
		head = tail;

	delete[] p->str;
	delete p;
	--size;
}

void lab1::stringlist::StringList::AppendExclusively(const StringList *nd)
{
	ListNode *p = nd->head;

	while (p){
		if (nullptr == Find(p->str))
			AddTail(p->str);

		p = p->next;
	}
}

void lab1::stringlist::StringList::Splice(POSITION where, StringList *sl, POSITION first, POSITION last)
{
	ListNode *pos = const_cast<ListNode*>(where), *ptrf = const_cast<ListNode*>(first),
		*ptrs = const_cast<ListNode*>(last);

	 /* deleting sequence of elements: */
	if (ptrf == sl->head)
		sl->head = ptrs->next;

	if (ptrs == sl->tail)
		sl->tail = ptrf->prev;

	if(ptrf->prev)
		ptrf->prev->next = ptrs->next;

	if(ptrs->next)
		ptrs->next->prev = ptrf->prev;

	 /* insertion */
	
	if(pos->next)
		pos->next->prev = ptrs;
	ptrs->next = pos->next;

	pos->next = ptrf;
	ptrf->prev = pos;

	if (pos == tail)
		tail = ptrs;

	while (ptrf != ptrs){
		++size;
		sl->size--;
		ptrf = ptrf->next;
	}
	++size;
	sl->size--;
}

void lab1::stringlist::StringList::Unique()
{
	int current = 0;
	ListNode *ptr = head;

	while (ptr){
		ListNode *backup = ptr->next;
		int index = FindIndex(ptr->str);
		
		if (current > index) /* when i remove element i don't need to increase counter */
			RemoveAt(current);
		else
			++current;

		ptr = backup;
	}
}

const char* lab1::stringlist::StringList::GetAt(int position) const
{
	int index = 0;
	ListNode *ptr = head;

	while (ptr && index != position){
		ptr = ptr->next;
		++index;
	}

	if (ptr)
		return ptr->str;
	return nullptr;
}

void lab1::stringlist::StringList::RemoveAt(int position)
{
	int index = 0;
	ListNode *ptr = head;

	while (ptr && index != position){
		ptr = ptr->next;
		++index;
	}

	if (ptr){
		if(ptr->prev)
			ptr->prev->next = ptr->next;

		if(ptr->next)
			ptr->next->prev = ptr->prev;

		if (head == ptr)
			head = ptr->next;

		if (tail == ptr)
			tail = ptr->prev;

		delete[] ptr->str;
		delete ptr;
	}
	--size;
}

void lab1::stringlist::StringList::SetAt(char *str, int position)
{
	int index = 0;
	ListNode *ptr = head;

	while (ptr && index != position){
		ptr = ptr->next;
		++index;
	}

	if (ptr){
		unsigned len = strlen(str);
		if (len > strlen(ptr->str)){
			delete[] ptr->str;
			ptr->str = new char[len + 1];
		}
		strncpy_s(ptr->str, len + 1, str, len);
	}
}

void lab1::stringlist::StringList::InsertAfter(char *str, int position)
{
	int index = 0;
	ListNode *ptr = head;

	if (position <= 0)
		AddHead(str);

	if (position >= size - 1){
		AddTail(str);
		return;
	}

	while (ptr && index != position){
		ptr = ptr->next;
		++index;
	}

	int len = strlen(str);
	ListNode *tmp = new ListNode;

	tmp->str = new char[len + 1];
	strncpy_s(tmp->str, len + 1, str, len);

	if(ptr->next)
		ptr->next->prev = tmp;
	tmp->next = ptr->next;

	ptr->next = tmp;
	tmp->prev = ptr;
}

void lab1::stringlist::StringList::InsertBefore(char *str, int position)
{
	int index = 0;
	ListNode *ptr = head;

	if (position <= 0)
		AddHead(str);

	if (position >= size - 1)
		AddTail(str);

	while (ptr && index != position){
		ptr = ptr->next;
		++index;
	}
	
	int len = strlen(str);
	ListNode *tmp = new ListNode;

	tmp->str = new char[len + 1];
	strncpy_s(tmp->str, len + 1, str, len);

	if(ptr->prev)
		ptr->prev->next = tmp;
	tmp->prev = ptr->prev;

	ptr->prev = tmp;
	tmp->next = ptr;
}

lab1::stringlist::POSITION lab1::stringlist::StringList::Find(char *str)
{
	ListNode *ptr = head;

	while (ptr && 0 != strcmp(ptr->str, str)){
		ptr = ptr->next;
	}

	return ptr;
}

int lab1::stringlist::StringList::FindIndex(char *str) const
{
	int index = 0;
	ListNode *ptr = head;

	while (ptr && 0 != strcmp(ptr->str, str)){
		ptr = ptr->next;
		++index;
	}

	return index;
}
