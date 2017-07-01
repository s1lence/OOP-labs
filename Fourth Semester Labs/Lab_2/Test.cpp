/************************************************
* file: "Test.cpp"
* synopsis: testing database class
* author: R. Neshta
* written: 23/04/16
* last modified: 23/04/16
************************************************/

#include "Database.h"

using namespace lab2;

using std::cout;

int main(){

	Database db;
	
	db.LoadFromFile("input.csv");
	db.ArrangeSubordinates();

	db.DisplayAll();

	cout << "\n\n";

	db.FireEmployee(1);
	db.DisplayAll();
	
	return 0;

}