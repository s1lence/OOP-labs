/************************************************************************
*file: File.c
*synopsis: this functions are declared in the include file "File.h".
*related files: none
*author: Ruslan Neshta
*written: 16/11/2015
*last modified: 16/11/2015
************************************************************************/


#include "File.h"

// writes data about scaner into binary file
void writedata(const char *fname, RECORD_SET record){

	FILE *f;
	SCAN_INFO *rec;

	int i;
	rec = NULL;

	if (NULL == (f = fopen(fname, "rb+"))){

		if (NULL == (f = fopen(fname, "wb")))
			exit(1);
		else
			record.rec_nmb = 1;

	}
	else{

		fseek(f, 0L, SEEK_SET);
		fread(&record.rec_nmb, sizeof(int), 1, f);

		if (NULL == (rec = (SCAN_INFO*)malloc(sizeof(SCAN_INFO))))
			exit(1);

		i = 0;
		while (i++ <= record.rec_nmb) {

			str2f(f, rec, 0);
			if (rec_cmp(*record.recs, *rec)){

				fclose(f);
				return;

			}

		}

		record.rec_nmb++;
		fseek(f, 0L, SEEK_SET);

	}

	fwrite(&record.rec_nmb, sizeof(int), 1, f);
	fseek(f, 0L, SEEK_END);

	str2f(f, record.recs, 1);
	fclose(f);

	free(rec);

}

// filles binary file from csv file
void csv2dat(const char *csvname, const char *datname){

	FILE *f;
	RECORD_SET record;

	int i, j;
	char str[512];

	if (NULL == (f = fopen(csvname, "r")))
		exit(1);

	if (NULL == (record.recs = (SCAN_INFO*)malloc(sizeof(SCAN_INFO))))
		exit(1);

	while (fgets(str, 512, f)){

		if (0 == (j = strlen(str)))
			continue;

		for (i = 0; i < j; i++){

			if (str[i] == ';')
				str[i] = '\0';

		}

		strcpy(record.recs->manufacturer, str);
		i = strlen(str) + 1;

		strcpy(record.recs->model, (str + i));
		i += strlen((str + i)) + 1;

		if (0 == (record.recs->year = atoi((str + i))))
			continue;

		i += strlen((str + i)) + 1;
		if (0 == (record.recs->price = atof((str + i))))
			continue;

		i += strlen((str + i)) + 1;
		if (0 == (record.recs->x_size = atoi((str + i))))
			continue;

		i += strlen((str + i)) + 1;
		if (0 == (record.recs->y_size = atoi((str + i))))
			continue;

		i += strlen((str + i)) + 1;
		if (0 == (record.recs->optr = atoi((str + i))))
			continue;

		writedata(datname, record);

	}

	free(record.recs);
	fclose(f);

}

// function that create index file sorted by field_name
int make_index(char *dba, char *field_name){

	Arr *A, tmp;
	FILE *_dba, *idx;

	int i, k, n;
	char s[255];

	k = n = 0;
	if (NULL == (_dba = fopen(dba, "rb")))
		exit(1);

	fread(&n, sizeof(int), 1, _dba);
	if (NULL == (A = (Arr*)malloc(n*sizeof(Arr))))
		exit(1);

	fill_arr(A, field_name, _dba, n);
	k = n;

	while (k > 0){

		for (i = 1; i < k; i++){
			if (0 > compare(A[i].buf, A[i - 1].buf, field_name)){

				tmp.val = A[i].val;
				strcpy(tmp.buf, A[i].buf);

				A[i].val = A[i - 1].val;
				strcpy(A[i].buf, A[i - 1].buf);

				A[i - 1].val = tmp.val;
				strcpy(A[i - 1].buf, tmp.buf);

			}

		}

		k--;

	}

	fclose(_dba);
	strcpy(s, field_name);
	strcat(s, ".idx");

	if (NULL == (idx = fopen(s, "w")))
		exit(1);

	for (i = 0; i < n; i++){

		fprintf(idx, "%d ", A[i].val);

	}

	free(A);
	fclose(idx);

	return 0;

}

// returns pointer to set of records, created by given index file
RECORD_SET * get_recs_by_index(char *dba, char *indx_field){

	int i, k;

	FILE *dba_file, *indx;
	RECORD_SET *ptr;

	char index_name[128];

	strcpy(index_name, indx_field);
	strcat(index_name, ".idx");

	if (NULL == (dba_file = fopen(dba, "rb")))
		exit(1);

	if (NULL == (indx = fopen(index_name, "r")))
		exit(1);

	if (NULL == (ptr = (RECORD_SET*)malloc(sizeof(RECORD_SET))))
		exit(1);

	fread(&ptr->rec_nmb, sizeof(int), 1, dba_file);

	if (NULL == (ptr->recs = (SCAN_INFO*)malloc(ptr->rec_nmb*sizeof(SCAN_INFO))))
		exit(1);

	fseek(indx, 0L, SEEK_SET);
	for (i = 0; i < ptr->rec_nmb; i++){

		fscanf(indx, "%d", &k);

		fseek(dba_file, sizeof(int)+k*(sizeof(int)* 4 + sizeof(char)* 255 + sizeof(float)), SEEK_SET);
		str2f(dba_file, &ptr->recs[i], 0);

	}

	fclose(indx);
	fclose(dba_file);

	return ptr;

}

// creates index files by every field in SCAN_INFO struct
void reindex(char *dba){

	make_index("Scaners.dba", "manufacturer");
	make_index("Scaners.dba", "year");

	make_index("Scaners.dba", "model");
	make_index("Scaners.dba", "price");

	make_index("Scaners.dba", "x_size");
	make_index("Scaners.dba", "y_size");

	make_index("Scaners.dba", "optr");

}

// deletes from dba record that corresponds given index
int del_scan(char *dba, int n){

	int i, sz;

	FILE *tmp, *dbaf;
	SCAN_INFO record;

	if (NULL == (dbaf = fopen(dba, "rb")))
		exit(1);

	if (NULL == (tmp = fopen("tmp.dba", "w")))
		exit(1);

	fread(&sz, sizeof(int), 1, dbaf);
	--sz; --n;

	fwrite(&sz, sizeof(int), 1, tmp);
	sz++;

	for (i = 0; i <= sz; i++){

		if (i != n){

			str2f(dbaf, &record, 0);
			str2f(tmp, &record, 1);

		}
		else
			fseek(dbaf, sizeof(float)+255 * sizeof(char)+4 * sizeof(int), SEEK_CUR);

	}

	fclose(dbaf);
	fclose(tmp);

	if (0 != remove(dba))
		exit(3);

	rename("tmp.dba", dba);
	reindex(dba);

	return 0;

}

// function that writes data from dba to txt file
void dba2txt(const char *dba_name, const char *txt_name, float cost){

	FILE *dba, *txt;
	RECORD_SET record;

	char *buf;
	int i;
	buf = NULL;

	if (NULL == (record.recs = (SCAN_INFO*)malloc(sizeof(SCAN_INFO))))
		exit(1);

	if (NULL == (dba = fopen(dba_name, "rb")))
		exit(1);

	if (NULL == (txt = fopen(txt_name, "w")))
		exit(1);

	fseek(dba, 0L, SEEK_SET);
	fseek(txt, 0L, SEEK_SET);

	fread(&record.rec_nmb, sizeof(int), 1, dba);
	for (i = 0; i < record.rec_nmb; i++){

		str2f(dba, record.recs, 0);
		if (record.recs->price < cost)
			fprintf(txt, "%s %d %s %.2f %d %d %d\n",
			record.recs->manufacturer,
			record.recs->year,
			record.recs->model,
			record.recs->price,
			record.recs->x_size,
			record.recs->y_size,
			record.recs->optr);

	}

	fclose(dba);
	fclose(txt);

	free(record.recs);

}


// my custom functions

// function for output *.dba files to console
void My_func_printfile(const char *fname, RECORD_SET newrec){

	FILE *f;
	int i;

	if (NULL == (f = fopen(fname, "rb")))
		exit(1);

	fseek(f, 0L, SEEK_SET);
	fread(&newrec.rec_nmb, sizeof(int), 1, f);

	printf("Number of records in file: %d.\n", newrec.rec_nmb);
	for (i = 0; i < newrec.rec_nmb; i++){

		str2f(f, newrec.recs, 0);
		printf("\t%5s;", newrec.recs->manufacturer);
		printf(" %4d;", newrec.recs->year);

		printf(" %10s;", newrec.recs->model);
		printf(" %6.2f;", newrec.recs->price);

		printf(" %5d;", newrec.recs->x_size);
		printf(" %5d;", newrec.recs->y_size);

		printf(" %5d\n", newrec.recs->optr);

	}

	fclose(f);

}

// function for comparing two structures
int rec_cmp(SCAN_INFO rec1, SCAN_INFO rec2){

	if (0 != strcmp(rec1.manufacturer, rec2.manufacturer))
		return 0;

	if (0 != strcmp(rec1.model, rec2.model))
		return 0;

	if (rec1.optr != rec2.optr)
		return 0;

	if (rec1.price != rec2.price)
		return 0;

	if (rec1.x_size != rec2.x_size)
		return 0;

	if (rec1.year != rec2.year)
		return 0;

	if (rec1.y_size != rec2.y_size)
		return 0;

	return 1;

}

// function for filling array (special function for make_index function)
void fill_arr(Arr *ptr, const char *name, FILE *f, int num){

	int i;
	SCAN_INFO rec;

	if (0 == strcmp("manufacturer", name)){

		for (i = 0; i < num; i++){

			fread(rec.manufacturer, sizeof(char), 127, f);
			strcpy(ptr[i].buf, rec.manufacturer);

			ptr[i].val = i;
			fseek(f, 4 * sizeof(int)+sizeof(char)* 128 + sizeof(float), SEEK_CUR);

		}

		return;

	}

	if (0 == strcmp("year", name)){

		fseek(f, sizeof(char)* 127, SEEK_CUR);
		for (i = 0; i < num; i++){

			fread(&rec.year, sizeof(int), 1, f);
			sprintf(ptr[i].buf, "%d", rec.year);

			ptr[i].val = i;
			fseek(f, 3 * sizeof(int)+sizeof(char)* 255 + sizeof(float), SEEK_CUR);

		}

		return;

	}

	if (0 == strcmp("model", name)){

		fseek(f, sizeof(char)* 127 + sizeof(int), SEEK_CUR);
		for (i = 0; i < num; i++){

			fread(rec.model, sizeof(char), 128, f);
			strcpy(ptr[i].buf, rec.model);

			ptr[i].val = i;
			fseek(f, 4 * sizeof(int)+sizeof(char)* 127 + sizeof(float), SEEK_CUR);

		}

		return;

	}

	if (0 == strcmp("price", name)){

		fseek(f, sizeof(char)* 255 + sizeof(int), SEEK_CUR);
		for (i = 0; i < num; i++){

			fread(&rec.price, sizeof(float), 1, f);
			sprintf(ptr[i].buf, "%f", rec.price);

			ptr[i].val = i;
			fseek(f, 4 * sizeof(int)+sizeof(char)* 255, SEEK_CUR);

		}

		return;

	}

	if (0 == strcmp("x_size", name)){

		fseek(f, sizeof(char)* 255 + sizeof(int)+sizeof(float), SEEK_CUR);
		for (i = 0; i < num; i++){

			fread(&rec.x_size, sizeof(int), 1, f);
			sprintf(ptr[i].buf, "%d", rec.x_size);

			ptr[i].val = i;
			fseek(f, 3 * sizeof(int)+sizeof(char)* 255 + sizeof(float), SEEK_CUR);

		}

		return;

	}

	if (0 == strcmp("y_size", name)){

		fseek(f, sizeof(char)* 255 + 2 * sizeof(int)+sizeof(float), SEEK_CUR);
		for (i = 0; i < num; i++){

			fread(&rec.y_size, sizeof(int), 1, f);
			sprintf(ptr[i].buf, "%d", rec.y_size);

			ptr[i].val = i;
			fseek(f, 3 * sizeof(int)+sizeof(char)* 255 + sizeof(float), SEEK_CUR);

		}

		return;

	}

	if (0 == strcmp("optr", name)){

		fseek(f, sizeof(char)* 255 + 3 * sizeof(int)+sizeof(float), SEEK_CUR);
		for (i = 0; i < num; i++){

			fread(&rec.optr, sizeof(int), 1, f);
			sprintf(ptr[i].buf, "%d", rec.optr);

			ptr[i].val = i;
			fseek(f, 3 * sizeof(int)+sizeof(char)* 255 + sizeof(float), SEEK_CUR);

		}

		return;

	}

	exit(2);

}

// function that compares two structures on the field "field"
int compare(const char *s1, const char *s2, const char *field){

	if (0 == strcmp(field, "manufacturer") || 0 == strcmp(field, "model"))
		return strcmp(s1, s2);

	if (0 == strcmp(field, "price"))
		return 0 == (atof(s1) - atof(s2));

	return atoi(s1) - atoi(s2);

}

// function for reading(mode == 0) / writing(!= 0) structure from / to file
void str2f(FILE *f, SCAN_INFO *rec, int mode){

	if (0 == mode){

		fread(rec->manufacturer, sizeof(char), 127, f);
		fread(&rec->year, sizeof(int), 1, f);

		fread(rec->model, sizeof(char), 128, f);
		fread(&rec->price, sizeof(float), 1, f);
		
		fread(&rec->x_size, sizeof(int), 1, f);
		fread(&rec->y_size, sizeof(int), 1, f);
		
		fread(&rec->optr, sizeof(int), 1, f);

		return;

	}

	fwrite(rec->manufacturer, sizeof(char), 127, f);
	fwrite(&rec->year, sizeof(int), 1, f);

	fwrite(rec->model, sizeof(char), 128, f);
	fwrite(&rec->price, sizeof(float), 1, f);
	
	fwrite(&rec->x_size, sizeof(int), 1, f);
	fwrite(&rec->y_size, sizeof(int), 1, f);
	
	fwrite(&rec->optr, sizeof(int), 1, f);

}
