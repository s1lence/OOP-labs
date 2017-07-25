/*
 * `file` 			Bus.cpp
 * `written` 		July 25 2017 17:02:49
 * `last modified`	July 25 2017 17:25:24
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		bus class implementation
 *
 *	Description: 	realization of bus class member functions
 *					
 *	`note`			none
 */
 
#include "Bus.h"

namespace lab4{

	namespace bus{

		Bus::Bus(char* drv, char* busNmb, char* rtNmb)
		{
			int len = strlen(rtNmb) + 1;
			route_number = new char[len];
			strncpy_s(route_number, len, rtNmb, len - 1);

			len = strlen(drv) + 1;
			route_number = new char[len];
			strncpy_s(route_number, len, drv, len - 1);

			len = strlen(busNmb) + 1;
			route_number = new char[len];
			strncpy_s(route_number, len, busNmb, len - 1);
		}

		Bus::Bus(char* routeNmb) :driver(nullptr), bus_number(nullptr)
		{
			int len = strlen(routeNmb) + 1;
			route_number = new char[len];
			strncpy_s(route_number, len, routeNmb, len - 1);
		}

		Bus::~Bus()
		{
			delete[] route_number;
			delete[] driver;
			delete[] bus_number;
		}

		bool Bus::operator==(const Bus& bus)
		{
			if (bus.driver)
				return 0 == strcmp(driver, bus.driver) && 0 == strcmp(bus_number, bus.bus_number) &&
				0 == strcmp(route_number, bus.route_number);

			return 0 == strcmp(route_number, bus.route_number);
		}

		bool Bus::operator!=(const Bus& bus)
		{
			return !(*this == bus);
		}

		void Bus::changeDriver(char* name)
		{
			delete[] driver;
			int len = strlen(name);
			driver = new char[len] + 1;
			strncpy_s(driver, len, name, len - 1);
		}


	}

}