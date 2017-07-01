/************************************************
* file: "Employee.cpp"
* synopsis: employee class implementation
* author: R. Neshta
* written: 23/04/16
* last modified: 23/04/16
************************************************/

#include "Employee.h"

using namespace lab2;

using std::cout;
using std::endl;

Employee::Employee(const Employee &e){

	if (NULL != &e)
		*this = e;

}

Employee& Employee::operator = (const Employee &e){

	if (this == &e || NULL == &e)
		return *this;
	
	f_name = e.f_name;
	l_name = e.l_name;
	
	age = e.age;
	id = e.id;
	
	salary = e.salary;
	department = e.department;
	
	return *this;

}

void Employee::Display(bool flag){

	string line = "";
	
	if (flag)
		line = "\t\t";
	
	cout << line << "Employment type: employee" << endl;
	cout << line << "id: " << this->id << endl;
	
	cout << line << this->f_name << " " << this->l_name << " age: " << this->age << " salary: " << this->salary << endl;
	
	if (!flag)
		cout << "department: " << this->department << endl;
	
	cout << endl;

}
