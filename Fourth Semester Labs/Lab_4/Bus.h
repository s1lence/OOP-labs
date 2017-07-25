/*
 * `file` 			Bus.h
 * `written` 		July 25 2017 8:29:59
 * `last modified`	July 25 2017 17:25:24
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
 *	`note`			none
 */
 

#ifndef _BUS_H_
#define _BUS_H_

#include<iostream>

namespace lab4{

	namespace bus{
	
		class Bus{
		public:
			Bus(char* drv, char* busNmb, char* rtNmb);
			Bus(char* routeNmb);
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

		std::ostream& operator<<(std::ostream& stream, Bus &obj){
			stream << obj.route_number << " " << obj.bus_number << " " << obj.driver << std::endl;
		}
	
	}

}

#endif /* _BUS_H_ */