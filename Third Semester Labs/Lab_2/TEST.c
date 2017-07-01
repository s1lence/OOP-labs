/***********************************
* file: TEST.c
* synopsis: memory dispatcher test
* author: R. Neshta
* written: 01/06/17
* last modified: 01/06/17
************************************/

#include<conio.h> // for _getch - represents comfortable menu

#include"Dispatcher.h"


int main(){
	
	mem_dispatcher disp;
	int n = 0, i = 0;
	
	mem_chunk *p;
	init(&disp);
	
	do{
	
		system("cls");
		printf("1. Allocate\n");
		printf("2. Deallocate\n");
		printf("3. Show memory map\n");
		printf("4. Defragment\n");
		printf("5. Exit\n");
		printf("Enter command: ");
		scanf_s("%d", &n);
		system("cls");

		switch (n)
		{
		case 1:
			printf("Enter block size: ");
			scanf_s("%d", &i);
			
			if (0 > allocate(&disp, i))
				printf("Allocation failed\n");
			else
				printf("Allocation done\n");
			break;
		
		case 2:
			printf("Enter block id: ");
			scanf_s("%d", &i);
			
			if (0 > deallocate(&disp, i))
				printf("Deallocation failed\n");
			else
				printf("Deallocation done\n");
			break;
		
		case 3:
			show_memory_map(&disp);
			break;
		
		case 4:
			defragment(&disp);
			printf("Defragmentation done\n");
			break;
		
		case 5:
			p = disp.first;
		
			while (p){

				deallocate(&disp, p->id);

				p = p->next;

			}

			free(disp.first);
			break;
		
		default:
			printf("Wrong command\n");
			break;
		
		}
		
		printf("Press any key to continue...\n");
		_getch();
	
	} while (n != 5);

}