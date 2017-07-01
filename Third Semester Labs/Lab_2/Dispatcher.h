/***********************************
* file: Dispatcher.h
* synopsis: memory dispatcher interface
* author: R. Neshta
* written: 01/06/17
* last modified: 01/06/17
************************************/


#ifndef _DISPATCHER_H_
#define _DISPATCHER_H_

#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#define HEAP_SIZE 10

typedef  enum{ FREE, ALLOCATED } STATUS;

typedef struct tag_mem_chunk{

	int id;
	int size;
	STATUS status;
	struct tag_mem_chunk* next;//pointer to the next memory block

}mem_chunk;

typedef struct {

	int last_id_used;
	mem_chunk* first;//pointer to the first memory block

}mem_dispatcher;


//creates a heap as a single free block  with id 0 and HEAP_SIZE size
void init(mem_dispatcher *md);

//returns block id if allocated and -1 otherwise
int allocate(mem_dispatcher *md, int size);

//returns nonnegative value if block is deallocated and -1 otherwise
int deallocate(mem_dispatcher *md, int block_id);

//reunites free blocks that were previously stored in various parts of a heap //into one successive block 
void defragment(mem_dispatcher *md);

//displays heap status
void show_memory_map(mem_dispatcher *md);

#endif /*_DISPATCHER_H_*/
