/*********************
*file: File.h
*purpose: declarations for File functions, types, constants
*author: Ruslan Neshta
*written: 16/11/2015
*last modified: 16/11/2015
*******************************/


#ifndef _FILE_H
#define _FILE_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {

	char manufacturer[127];
	int year;
	char model[128];
	float price;
	int x_size;
	int y_size;
	int optr;

} SCAN_INFO;

typedef struct{

	int rec_nmb;		//number of records
	SCAN_INFO *recs;	//records 

}RECORD_SET;

//structure special for make_index function
typedef struct{

	int val;
	char buf[255];

}Arr;

//function prototypes

// writes data about scaner into binary file
void writedata(const char *fname, RECORD_SET record);

// filles binary file from csv file
void csv2dat(const char *csvname, const char *datname);

// function that create index file sorted by field_name
int make_index(char *dba, char *field_name);

// returns pointer to set of records, created by given index file
RECORD_SET * get_recs_by_index(char *dba, char *indx_field);

// creates index files by every field in SCAN_INFO struct
void reindex(char *dba);

// deletes from dba record that corresponds given index
int del_scan(char *dba, int n);

// function that writes data from dba to txt file
void dba2txt(const char *dba_name, const char *txt_name, float cost);

// my custom functions

// this function print dba files
void My_func_printfile(const char *fname, RECORD_SET newrec);

// this function compares two SCAN_INFO structures
int rec_cmp(SCAN_INFO rec1, SCAN_INFO rec2);

// function that filling array of strings & int's (array for sorting index's)
// (special function for make_index function)
void fill_arr(Arr *ptr, const char *name, FILE *f, int num);

// function that compares two structures on the field "field"
int compare(const char *s1, const char *s2, const char *field);

// function for reading(mode == 0) / writing(!= 0) structure from / to file
void str2f(FILE *f, SCAN_INFO *rec, int mode);


#endif
