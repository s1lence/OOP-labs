/****************************
*file: Dispatcher.c
*synopsis: the functions use malloc to create new elements of list and must be feed by using free.
*This functions declared in "Dispatcher.h".
*related files: none
*author: R. Neshta
*written: 01/06/17
*last modified: 01/06/17
********************************/

#include "Dispatcher.h"

// creates a heap as a single free block  with id 0 and HEAP_SIZE size
void init(mem_dispatcher *md){
	
	if (NULL == (md->first = (mem_chunk*)malloc(sizeof(mem_chunk)))){
	
		printf("Allocation fail");
		exit(1);
	
	}
	
	md->last_id_used = 0;
	md->first->id = md->last_id_used;
	md->first->size = HEAP_SIZE;
	md->first->status = FREE;
	md->first->next = NULL;

}

// returns block id if allocated and -1 otherwise
int allocate(mem_dispatcher *md, int size){
	
	mem_chunk *min_free, *cur_free;
	
	if (size > HEAP_SIZE || size == 0)
		return -1;
	
	// any free block that has sufficient amount
	// of memory is min_free
	min_free = md->first;
	while (NULL != min_free){
		
		if (!min_free->status && min_free->size >= size)
			break;

		min_free = min_free->next;

	}

	if (NULL == min_free)
		return -1;
	// search for minimum enough amount of memory
	cur_free = min_free->next;
	while (NULL != cur_free){

		if (!cur_free->status && cur_free->size >= size
			&& cur_free->size < min_free->size)

			min_free = cur_free;

		cur_free = cur_free->next;

	}

	// allocation
	if (min_free->size != size){

		min_free->size -= size;
		cur_free = min_free->next;

		if (NULL == (min_free->next = (mem_chunk*)malloc(sizeof(mem_chunk)))){

			printf("Allocation fail\n");
			exit(1);

		}

		// adding new allocated block
		min_free->next->size = size;
		min_free->next->id = ++md->last_id_used;
		min_free->next->status = ALLOCATED;
		min_free->next->next = cur_free;

		return min_free->next->id;

	}
	else
		min_free->status = ALLOCATED;

	return min_free->id;

}

// returns nonnegative value if block is deallocated and -1 otherwise
int deallocate(mem_dispatcher *md, int block_id){
	
	mem_chunk *ptr, *p, *tmp;
	ptr = p = md->first;
	
	
	// searching block with corresponding id
	while (ptr && ptr->id != block_id){
	
		// p points to previous element
		if (ptr != md->first)
			p = p->next;
		
		ptr = ptr->next;

	}
	
	// is it's free or not exist - doing nothing
	if (NULL == ptr || ptr->status == FREE)
		return -1;
	
	ptr->status = FREE;

	// if next exist & is free - merge them
	if (ptr->next && !ptr->next->status){

		ptr->size += ptr->next->size;

		tmp = ptr->next;
		ptr->next = tmp->next;
		free(tmp);

	}

	// if previous exist & is free - merge them
	if (p->next == ptr && !p->status){

		p->size += ptr->size;

		p->next = ptr->next;
		free(ptr);
		
		ptr = p->next;

	}

	return 0;

}

// reunites free blocks that were previously stored in various parts of a heap 
// into one successive block 
void defragment(mem_dispatcher *md){
	
	mem_chunk *ptr, *cur, *next;
	ptr = md->first;
	
	//
	while (ptr && ptr->status)
		ptr = ptr->next;
	
	if (NULL == ptr)
		return;
	
	cur = ptr->next;
	do{
	
		if (cur->next && !cur->next->status){
		
			next = cur->next;
			cur->next = next->next;
			ptr->size += next->size;
			free(next);
		
		}
	
	} while (NULL != (cur = cur->next));

}

//displays heap status
void show_memory_map(mem_dispatcher *md){
	
	mem_chunk *ptr;
	ptr = md->first;

	printf("\t Memory Map\n");
	while (ptr){
	
		printf("block id:%d\n", ptr->id);
		
		switch (ptr->status)
		{
		case FREE:
			printf("\tsize:%3d   status: free\n", ptr->size);
			break;
		
		default:
			printf("\tsize:%3d   status: allocated\n", ptr->size);
		
		}
		
		ptr = ptr->next;
	
	}

}