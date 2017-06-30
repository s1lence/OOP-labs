/***
*file: "TEST.c"
*synopsis: testing first part of the first lab
*author: R. Neshta
*written: 30/06/17
*last modified: 30/06/17
****/

#include<stdio.h>

#include"FirstPart.h"
#include"SecondPart.h"


int main(){

	const char* first = "somestringdickistringdick";
	const char* second = "istringdick";
	const char* palindromTest = "pilylip";
	const char* palindromMakeTest = "splllirill";
	char* txtstring = { "3.14;2.78;;511.34;1337;456.2829" };

	printf("Results(first part):\nsubstr(%s,%s) returned %d\n\n", first, second, substr(first,second));

	printf("subseq(%s,%s) returned %d\n\n", first, second, subseq(first, second));

	printf("ispal(%s) returned %c\n\n", palindromTest, ispal(palindromTest));

	printf("makepal(%s) returned %s\n\n", palindromMakeTest, makepal(palindromMakeTest));

	int n;
	double* p = txt2double(txtstring, &n);

	printf("txt2double called with %s:\n", txtstring);

	int i;
	if (NULL == p)
		printf("Can't convert string data.\n");
	else{
		printf("Array consist of:\n");
		for (i = 0; i < n; i++)
			printf("%.4f ", *(p + i));
	}

	free(p);

	printf("\n\n\nResults(second part):\n");

	char string[] = "abc:defg:haski", str[] = "abcklm";
	int k;
	char *arr, *bfr, *entry;
	bfr = "haski";
	size_t size;

	printf("Create function test\n");
	
	argz_create_sep(string, 58, &arr, &size);
	argz_print(arr, size);
	
	printf("\nCount function test\n");
	printf("%d\n", argz_count(arr, size));
	printf("\nAdd function test\n");
	
	argz_add(&arr, &size, str);
	argz_print(arr, size);
	
	printf("\nDelete function test\n");
	argz_delete(&arr, &size, "defg");
	argz_print(arr, size);
	
	printf("\nInsert function test\n");
	argz_insert(&arr, &size, bfr, "entry text");
	argz_print(arr, size);
	
	printf("\n\"Next\" function test\n");
	entry = NULL;
	k = argz_count(arr, size);
	i = 0;
	
	while (i++ < k){
	
		printf("%s ", entry = argz_next(arr, size, entry));
	
	}
	
	printf("\n\nReplace function test\n");
	argz_replace(&arr, &size, "haski", "my cat");
	argz_print(arr, size);
	
	return 0;

}
