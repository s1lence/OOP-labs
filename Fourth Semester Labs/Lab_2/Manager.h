/************************************************
* file: "Manager.h"
* synopsis: manager class interface
* author: R. Neshta
* written: 23/04/16
* last modified: 23/04/16
************************************************/

#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <list>

#include "Employee.h"

namespace lab2{

	class Manager : public Employee {

	public:
		
		Manager(){};
		
		Manager(string _f_name, string _l_name, int _age, int _id) :
			Employee(_f_name, _l_name, _age, _id){}
		
		Manager(const Manager &m);
		
		Manager& operator=(const Manager &m);
		
		virtual void Display();
		
		// add an employee to the subordinates list
		Person* AddSubordinate(Person *p);
		
		void DisplaySubordinates();
		
		// Add here whatever you need

	private:
		
		std::list<Person *> subordinates; // list subordinates
	
	};

}

#endif /*_MANAGER_H_*/
