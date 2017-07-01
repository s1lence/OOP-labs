/************************************************
* file: "Employee.h"
* synopsis: employee class interface
* author: R. Neshta
* written: 23/04/16
* last modified: 23/04/16
************************************************/

#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

#include "Person.h"

namespace lab2{

	class Employee : public Person{

	public:
		
		Employee(){}
		
		Employee(string _f_name, string _l_name, int _age, int _id) :
			Person(_f_name, _l_name, _age), id(_id){}
		
		Employee(const Employee &e);
		
		Employee& operator=(const Employee &e);
		
		void SetSalary(int s){ salary = s; }
		
		void SetDepartment(string dept){ department = dept; }
		
		void SetId(int n){ id = n; }
		
		int GetId()const{ return id; }
		
		string GetDepartment()const{ return department; }
		
		virtual void Display(bool);
		
		//Add here whatever you need

	protected:

		string department;
		
		int salary;
		
		int id;
	
	};

}

#endif /*_EMPLOYEE_H_*/
