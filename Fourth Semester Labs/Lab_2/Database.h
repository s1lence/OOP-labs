/************************************************
* file: "Database.h"
* synopsis: database class interface
* author: R. Neshta
* written: 23/04/16
* last modified: 23/04/16
************************************************/


#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <vector>

#include "Manager.h"

namespace lab2{

	class Database{

	public:

		Database(){}
		
		~Database(){}

		// creates “flat” database
		bool LoadFromFile(const char *file);
		
		// arranges "flat" database after loading from the file
		void ArrangeSubordinates();
		
		// hire a new employee
		Person* HireEmployee(Person *p){ employees.push_back(p); }
		
		void DisplayDepartmentEmployees(string _department);
		
		// fire the employee
		bool FireEmployee(int id);
		
		void DisplayAll();
		
		// Add here whatever you need

	private:
		
		std::vector<Person*> employees;
	
	};

}

#endif /*_DATABASE_H_*/
