/*
 * `file` 			cstring.cpp
 * `written` 		July 23 2017 8:40:19
 * `last modified`	July 23 2017 16:19:37
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		c string class implementation
 *
 *	Description: 	realization methods of c string class
 *
 *	`note`			none
 */
 
#include "cstring.h"

lab1::cstring::cString::cString(const char *psz) :size(strlen(psz)), reserved(size + 1)
{
	buf = new char[reserved];
	strncpy_s(buf, reserved, psz, size);

}

lab1::cstring::cString::cString(const cString& stringsrc) :size(stringsrc.size), reserved(size + 1)
{
	buf = new char[reserved];
	strncpy_s(buf, reserved, stringsrc.buf, size);
}

void lab1::cstring::cString::Empty()
{
	if (nullptr != buf){
		delete[] buf;
		size = reserved = 0;
	}
}

int lab1::cstring::cString::Find(char ch) const
{	
	if (!Isempty()){
		char* position = strchr(buf, ch);
		
		if (position)
			return (position - buf) / sizeof(char);
	}

	return -1;
}

int lab1::cstring::cString::Find(char *pszsub) const
{
	if (!Isempty()){
		char* position = strstr(buf, pszsub);
		
		if (position)
			return (position - buf) / sizeof(char);
	}

	return -1;
}

lab1::cstring::cString lab1::cstring::cString::Mid(int nfirst, int ncount) const
{
	if (nfirst + ncount >= size || nfirst < 0)
		return cString();

	int length = ncount;
	if (0 == length)
		length = size - nfirst;
	
	char *buffer = new char[length + 1];
	strncpy_s(buffer, length + 1, buf + nfirst, length);

	return cString(buffer);
}

lab1::cstring::cString& lab1::cstring::cString::operator=(const cString& stringsrc)
{
	*this = stringsrc.buf;
	return *this;
}

const lab1::cstring::cString& lab1::cstring::cString::operator=(const char* psz)
{
	int strsize = strlen(psz);
	if (strsize > size){

		delete[] buf;
		size = strsize;

		reserved = size + 1;
		buf = new char[reserved];
	}
	else
		size = strsize;

	strncpy_s(buf, reserved, psz, size);
	return *this;
}

lab1::cstring::cString lab1::cstring::cString::operator+(const cString& string)
{
	int len = size + string.size + 1;
	char* buffer = new char[size + string.size + 1];
	
	strncpy_s(buffer, len, buf, size);
	strncat(buffer, string.buf, string.size);

	return cString(buffer);
}

lab1::cstring::cString& lab1::cstring::cString::operator+=(const cString& string)
{
	if (size < string.size){
		reserved = size + string.size + 1;
		char * tmp = new char[reserved];

		strncpy_s(tmp, reserved, buf, size);
		size = reserved - 1;

		delete[] buf;
		buf = tmp;
	}

	strncat(buf, string.buf, string.size);
	return *this;
}

