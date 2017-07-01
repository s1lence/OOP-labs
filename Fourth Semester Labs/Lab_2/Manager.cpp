/************************************************
* file: "Manager.cpp"
* synopsis: manager class implementation
* author: R. Neshta
* written: 23/04/16
* last modified: 23/04/16
************************************************/

#include "Manager.h"

using namespace lab2;

using std::list;
using std::cout;
using std::endl;

Manager::Manager(const Manager &m){

	if (NULL != &m)
		*this = m;

}

Manager& Manager::operator = (const Manager &m){

	if (this == &m || NULL == &m)
		return *this;

	f_name = m.f_name;
	l_name = m.l_name;

	age = m.age;
	id = m.id;

	subordinates = m.subordinates;
	return *this;

}

Person* Manager::AddSubordinate(Person* p){

	Person *tmp(p);
	subordinates.push_back(tmp);

	return tmp;

}

void Manager::DisplaySubordinates(){
	
	list <Person*>::iterator it;
	
	cout << "Subordinates:" << endl;
	cout << "\t\t";
	
	for (it = subordinates.begin(); it != subordinates.end(); it++){
	
		(*it)->Display(false);
		cout << endl << "\t\t";
	
	}

}

void Manager::Display(){

	cout << "Employment type: manager" << "id: " << this->id << endl;
	cout << this->f_name << " " << this->l_name << " age: " << this->age << " salary: " << this->salary << endl << endl;

}