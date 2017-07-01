/************************************************
* file: "Database.cpp"
* synopsis: database class implementation
* author: R. Neshta
* written: 23/04/16
* last modified: 23/04/16
************************************************/

#include <fstream>
#include <string>

#include "Database.h"

using namespace lab2;

using std::ifstream;
using std::cout;
using std::endl;
using std::vector;

// creates “flat” database
bool Database::LoadFromFile(const char *file){

	// 1 -- manager;
	// 0 -- employee;

	string str, fName, lName, department;
	int id, age, salary, type;
	
	char ch;
	ifstream input(file);
	
	if (input.is_open()){
	
		while (input){
		
			input >> type >> ch >> id >> ch;
			
			getline(input, fName, ';');
			getline(input, lName, ';');
			
			input >> age >> ch;
			getline(input, department, ';');
			
			input >> salary;
			if (0 == type){
			
				Employee *employee = new Employee(fName, lName, age, id);
				
				employee->SetSalary(salary);
				employee->SetDepartment(department);
				
				this->employees.push_back(employee);
			
			}
			else{
			
				Manager *manager = new Manager(fName, lName, age, id);
				
				manager->SetSalary(salary);
				manager->SetDepartment(department);
				
				this->employees.push_back(manager);
			
			}

		}

		return true;
	
	}
	else{
	
		cout << "Error opening file" << endl;
		exit(1);
	
	}
	
	return false;

}

// arranges "flat" database after loading from the file
void Database::ArrangeSubordinates(){

	for (vector<Person*>::iterator it = employees.begin(); it != employees.end(); ++it){
		if (typeid(Manager) == typeid(**it)){
		
			for (vector<Person*>::iterator iter = employees.begin(); iter != employees.end(); ++iter){
				if (typeid(Employee) == typeid(**iter)){
			
					if (dynamic_cast<Employee*>(*iter)->GetDepartment() == dynamic_cast<Manager*>(*it)->GetDepartment())
						dynamic_cast<Manager*>(*it)->AddSubordinate(*iter);

				}

			}

		}
	}

}


void Database::DisplayDepartmentEmployees(string _department){

	for (vector<Person*>::iterator it = employees.begin(); it != employees.end(); ++it){
		if (typeid(Employee) == typeid(**it)){
		
			if (_department == dynamic_cast<Employee*>(*it)->GetDepartment())
				(*it)->Display(false);
		
		}
	
	}

}

// fire the employee
bool Database::FireEmployee(int id){

	for (vector<Person*>::iterator it = employees.begin(); it != employees.end(); ++it){
		if (typeid(Employee) == typeid(**it)){
		
			if (id == dynamic_cast<Employee*>(*it)->GetId()){
			
				it = employees.erase(it);
				return true;
			
			}
		
		}
	
	}

	return false;

}

void Database::DisplayAll(){

	for (vector<Person*>::iterator iter = employees.begin(); iter != employees.end(); ++iter)
		(*iter)->Display(true);

}
