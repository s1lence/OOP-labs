/*
 * `file` 			cstring.h
 * `written` 		July 23 2017 8:23:45
 * `last modified`	July 23 2017 16:19:37
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		c string class interface
 *
 *	Description: 	similar to std::string
 *
 *	`note`			none
 */
 

#ifndef _CSTRING_H_
#define _CSTRING_H_

#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdio.h>

namespace lab1{

	namespace cstring{

		class cString{
			
			/* 
			 * `class 			cString
			 *
			 * `in 				lab1::cstring
			 *
			 * `synopsis 		string class
			 *
			 * DESCRIPTION: 	holds and manages memory control on c string
			 *
			 * `notes 			none
			 *
			 * `author 			R. Neshta
			 *
			 * `version 		1.0
			 *
			 * `date 			July 23 2017 8:38:05
			 *
			 * Contact: 		Ruslan.Neshta@gmail.com
			 *
			 */
			 
		public:
			//constructors/destructor
			cString() :buf(nullptr), size(0), reserved(0){}
			cString(const char *psz);
			cString(const cString& stringsrc);

			~cString(){ Empty(); }

			//methods
			int Getlength() const{ return size; }
			bool Isempty()const{ return 0 == size; }
			void Empty();
			void SetAt(int nindex, char ch){ nindex < size ? buf[nindex] = ch : false; }
			int Compare(const cString& s) const{ return strcmp(buf, s.buf); }
			int Find(char ch) const;
			int Find(char *pszsub) const;

			cString Mid(int nfirst, int ncount = 0) const;

			cString Left(int ncount) const{ return Mid(0, ncount); }

			cString Right(int ncount) const{ return ncount < size ? Mid(size - ncount) : Mid(0); }

			//operators
			cString& operator=(const cString& stringsrc);
			const cString& operator=(const char* psz);
			char operator[](int indx){ return  indx < size ? buf[indx] : indx; }

			cString operator+(const cString& string);
			cString& operator+=(const cString& string);

			void Print(){ printf("%s\n", buf); }
		private:
			//put your own data members here
			int size;
			int reserved;
			char* buf;			
		};

		
	}
	
}
  
#endif /* _CSTRING_H_ */