/************************************************
* file: "Person.h"
* synopsis: person class interface
* author: R. Neshta
* written: 23/04/16
* last modified: 23/04/16
************************************************/

#ifndef _PERSON_H_
#define _PERSON_H_

#include <iostream>
#include <string>

using std::string;

namespace lab2{

	//An abstract class
	class Person{
	
	public:
	
		Person(){}
		
		Person(string _f_name, string _l_name, int _age) : age(_age),
			f_name(_f_name), l_name(_l_name){}
		
		virtual void Display(bool) = 0;
	
	protected:
	
		string f_name; //first name
		
		string l_name; //last name
		
		int age;

	};

}

#endif /*_PERSON_H_*/
