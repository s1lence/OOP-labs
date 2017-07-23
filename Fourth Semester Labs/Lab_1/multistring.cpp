/*
 * `file` 			multistring.cpp
 * `written` 		July 20 2017 19:48:21
 * `last modified`	July 23 2017 7:50:54
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		realization of multi string class
 *
 *	Description: 	non-inline functions implemented here
 *
 *	`note`			none
 */
 
 
#include "multistring.h"

using namespace lab1::multistring;

MultiString::MultiString(int n):str_nmb(n){
	buf = new char *[n];
	/* as str_num != 0 items must be initialized */
	for (int i = 0; i < n; ++i)
		buf[i] = nullptr;
}

MultiString::~MultiString(){
	Empty();
}

MultiString & MultiString::operator=(const MultiString &ms){
	if (this == &ms) /* self assignment check */
		return *this;
	/*
	 *	function destroys old members
	 *	and copies new from given object
	 */

	Empty();
	buf = new char *[ms.str_nmb];
	str_nmb = ms.str_nmb;
	
	for (int i = 0; i < str_nmb; ++i){
		int length = strlen(ms[i]);
		buf[i] = new char[length + 1];
		strncpy_s(buf[i], length + 1, ms[i], length);
	}

	return *this;
}

char * MultiString::operator[] (int nindex) const{
	if (nindex<str_nmb) /* if element exists */
		return buf[nindex];

	return nullptr;
}

MultiString & MultiString::operator+=(const MultiString &str){
	int i, size = str.GetLength();
	if (size>str_nmb) /* size contains the less length of given objects */
		size = str_nmb;

	for (i = 0; i < size; ++i){ /* concatenate while we can */
		int len = strlen(buf[i]) + strlen(str[i]) + 1;
		char *tmp = new char[len];
		strncpy_s(tmp, len, buf[i], strlen(buf[i]));
		
		strncat_s(tmp, len, str[i], strlen(str[i]));

		delete[] buf[i];
		buf[i] = tmp;
	}

	if (i != str.GetLength()){

		/*
		 *	if there is missed objects
		 *	we copied them to the end of current
		 *	this requires some memory management
		 */

		char ** tmp = buf;
		str_nmb = str_nmb + str.GetLength() - i;
		buf = new char *[str_nmb];
		
		
		for (int j = 0; j < i; ++j)
			buf[j] = tmp[j];

		for (; i < str_nmb; ++i){
			int len = strlen(str[i]);
			buf[i] = new char[len + 1];
			strncpy_s(buf[i], len + 1, str[i], len);
		}
	}

	return *this;
}

MultiString & MultiString::MergeMultiStringExclusive(const MultiString &str){
	char **tmp = new char *[str_nmb + str.str_nmb]; 
	
	/* tmp will contain pointers to actual objects: */
	for (int i = 0; i < str_nmb; ++i)
		tmp[i] = buf[i];
	int actualtmpsize = str_nmb;

	for (int i = 0; i < str.GetLength(); ++i){
		if (nullptr == Find(str[i])){ /* if not a duplicate - copy */
			int len = strlen(str[i]);
			tmp[actualtmpsize] = new char[len + 1];
			strncpy_s(tmp[actualtmpsize++], len + 1, str[i], len);
		}
	}

	MultiString* result = new MultiString();
	result->buf = new char *[actualtmpsize];
	result->str_nmb = actualtmpsize;

	for (int i = 0; i < actualtmpsize; ++i)
		result->buf[i] = tmp[i];
	return *result;
}

char *MultiString::Find(const char *pszsub) const{
	// linear search
	for (int i = 0; i < str_nmb; ++i){
		if (!strncmp(buf[i], pszsub, strlen(buf[i])))
			return buf[i];
	}

	return nullptr;
}

void MultiString::Empty(){
	 /* erasing every single object */
	for (int i = 0; i < str_nmb; ++i)
		delete[] buf[i];

	delete[] buf;
}

void MultiString::SetAt(int nindex, const char* str){
	if (nindex > str_nmb) /* can't set non-existing item */
		return;

	int stringlen = strlen(str);
	if (nullptr != buf[nindex] && strlen(buf[nindex]) != stringlen)
		delete[]  buf[nindex];
	
	buf[nindex] = new char[stringlen + 1];
	strncpy_s(buf[nindex], stringlen + 1, str, stringlen);
}

void MultiString::PrintStr(int nindex) const{
	std::cout << buf[nindex] << std::endl;
}