/***
*file: "TEST.c"
*synopsis: testing first part of the first lab
*author: R. Neshta
*written: 30/06/17
*last modified: 30/06/17
****/

#include<stdio.h>

#include"FirstPart.h"


int main(){

	const char* first = "somestringdickistringdick";
	const char* second = "istringdick";
	const char* palindromTest = "pilylip";
	const char* palindromMakeTest = "splllirill";
	char* txtstring = { "3.14;2.78;;511.34;1337;456.2829" };

	printf("Results:\nsubstr(%s,%s) returned %d\n", first, second, substr(first,second));

	printf("subseq(%s,%s) returned %d\n", first, second, subseq(first, second));

	printf("ispal(%s) returned %c\n", palindromTest, ispal(palindromTest));

	printf("makepal(%s) returned %s\n", palindromMakeTest, makepal(palindromMakeTest));

	int n;
	double* p = txt2double(txtstring, &n);

	printf("txt2double called with %s\n", txtstring);

	if (NULL == p)
		printf("Can't convert string data.\n");
	else{
		printf("Array consist of:\n");
		int i;
		for (i = 0; i < n; i++)
			printf("%.4f ", *(p + i));
	}
	printf("\n");

	free(p);
	
	return 0;

}
