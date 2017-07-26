/*
 * `file` 			Bus.h
 * `written` 		July 25 2017 8:29:59
 * `last modified`	July 27 2017 0:52:43
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		bus class interface
 *
 *	Description: 	class has information about bus:
 *					-car number;
 *					-driver name;
 *					-route number.
 *					Methods must provide ability of creation and future work with List<Bus>.
 *					
 *	`note`			csv string required to follow 'bus;route;driver' format
 */
 

#ifndef _BUS_H_
#define _BUS_H_

#include<iostream>

namespace lab4{

	namespace bus{
	
		class Bus{
		public:
			Bus() = delete;
			Bus(char* drv, char* busNmb, char* rtNmb);
			Bus(char* routeNmb, nullptr_t);
			Bus(char* csv);
			~Bus();

			bool operator==(const Bus& bus);
			bool operator!=(const Bus& bus);

			void changeDriver(char* name);
			friend std::ostream& operator<<(std::ostream& stream, Bus &obj);
		
		private:
			char *driver;
			char *bus_number;
			char *route_number;
		};

		std::ostream& operator<<(std::ostream& stream, Bus &obj);
	
	}

}

#endif /* _BUS_H_ */