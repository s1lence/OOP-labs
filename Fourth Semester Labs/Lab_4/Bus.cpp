/*
 * `file` 			Bus.cpp
 * `written` 		July 25 2017 17:02:49
 * `last modified`	July 27 2017 0:52:43
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		bus class implementation
 *
 *	Description: 	realization of bus class member functions
 *					
 *	`note`			csv string required to follow 'bus;route;driver' format
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
			driver = new char[len];
			strncpy_s(driver, len, drv, len - 1);

			len = strlen(busNmb) + 1;
			bus_number = new char[len];
			strncpy_s(bus_number, len, busNmb, len - 1);
		}

		Bus::Bus(char* routeNmb, nullptr_t) :driver(nullptr), bus_number(nullptr)
		{
			int len = strlen(routeNmb) + 1;
			route_number = new char[len];
			strncpy_s(route_number, len, routeNmb, len - 1);
		}

		Bus::Bus(char* csv)
		{
			int len = strlen(csv);
			char *tmp = new char[len + 1];
			for (int i = 0; i <= len; ++i){
				if (';' == csv[i])
					tmp[i] = '\0';
				else
					tmp[i] = csv[i];
			}

			len = strlen(tmp) + 1;
			bus_number = new char[len];
			strncpy_s(bus_number, len, tmp, len - 1);

			int newlen = strlen(tmp + len) + 1;
			route_number = new char[newlen];
			strncpy_s(route_number, newlen, tmp + len, newlen - 1);

			len += newlen;
			newlen = strlen(tmp + len) + 1;
			driver = new char[newlen];
			strncpy_s(driver, newlen, tmp + len, newlen - 1);
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
				return 
				0 == strcmp(driver, bus.driver) && 
				0 == strcmp(bus_number, bus.bus_number) &&
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
			int len = strlen(name) + 1;
			driver = new char[len];
			strncpy_s(driver, len, name, len - 1);
		}

		std::ostream& operator<<(std::ostream& stream, Bus &obj)
		{
			stream << obj.route_number << " " << obj.bus_number << " " << obj.driver << std::endl;
			return stream;
		}

	}

}