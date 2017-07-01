/********
* Test file for file functions
* Functions are declared in "File.h"
* related files: File.h, File.c;
********/


#include "File.h"

int main(){

	int i, k;

	FILE *f;
	RECORD_SET *rec = NULL;

	//csv2dat use writedata function so I don't need to call writedata
	csv2dat("Scaners.csv", "Scaners.dba");

	//reindex use make_index function so I don't need to call make_index
	reindex("Scaners.dba");

	dba2txt("Scaners.dba", "Scaners.txt", 985);

	/*
	 * for testing get_recs_by_index I create another test-file "TEST.dba"
	 * and print results to the console
	 */

	rec = get_recs_by_index("Scaners.dba", "model");

	if (NULL == (f = fopen("Scaners.dba", "rb")))
		exit(1);

	fread(&k, sizeof(int), 1, f);
	fclose(f);

	if (NULL == (f = fopen("TEST.dba", "w")))
		exit(1);

	fwrite(&k, sizeof(int), 1, f);
	for (i = 0; i < k; i++)
		str2f(f, &rec->recs[i], 1);

	fclose(f);

	printf("get_recs function test:\n");
	My_func_printfile("TEST.dba", *rec);

	printf("get_recs function test ended.\n\n");

	/*
	 * delete-function test
	 * one of the records will be absent
	 */

	i = 5;

	printf("File BEFORE deleting %dth element\n", i);
	My_func_printfile("Scaners.dba", *rec);

	del_scan("Scaners.dba", i);

	printf("File AFTER deleting %dth element\n", i);
	My_func_printfile("Scaners.dba", *rec);


	return 0;

}