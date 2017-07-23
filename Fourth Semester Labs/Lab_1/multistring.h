/*
 * `file` 			multistring.h
 * `written` 		July 20 2017 19:45:55
 * `last modified`	July 21 2017 0:17:26
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		declaration multi string class
 *
 *	Description: 	multi string class is a container that holds and manages operations with them
 *
 *	`note`			none
 */
 
 
#ifndef _MULTISTRING_H_
#define _MULTISTRING_H_
  
#include <iostream>
#include <string.h>
#include <stdio.h>

namespace lab1{

	namespace multistring{
	
		class MultiString{
			
			/* 
			 * `class 			MultiString
			 *
			 * `in 				lab2::multistring
			 *
			 * `synopsis 		manages operations with strings
			 *
			 * DESCRIPTION: 	holds and manages operations with strings
			 *					memory management accordingly to RAII
			 *
			 * `notes 			none
			 *
			 * `author 			R. Neshta
			 *
			 * `version 		1.0
			 *
			 * `date 			July 20 2017 19:46:41
			 *
			 * Contact: 		Ruslan.Neshta@gmail.com
			 *
			 */
			 
		public:
			//constructors destructor
			MultiString() :buf(nullptr), str_nmb(0){}
			MultiString(int n);
			~MultiString();

			//methods
			MultiString & operator=(const MultiString &ms);

			char * operator[] (int nindex) const;
			
			MultiString & operator+=(const MultiString &);
			
			MultiString & MergeMultiStringExclusive(const MultiString &);
			
			char *Find(const char *pszsub) const;
			
			int GetLength() const{ return str_nmb; }
			
			bool IsEmpty()const{ return str_nmb == 0; };
			
			void Empty();
			
			void SetAt(int nindex, const char* str);
			
			void PrintStr(int nindex) const;
		
		private:
			//forbidden copy constructor
			MultiString(const MultiString & ms){}

			//attributes
			char **buf;//pointer to vector
			int str_nmb;//strings number
		};

		
	}
	
}
  
#endif /* _MULTISTRING_H_ */