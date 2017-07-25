/*
 * `file` 			References.h
 * `written` 		July 25 2017 8:40:19
 * `last modified`	July 25 2017 17:25:24
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		references class interface
 *
 *	Description: 	class has information about references to words:
 *					-word;
 *					-numbers of pages where it appears;
 *					-number of pages where it appears.
 *					Methods must provide ability of creation and future work with List<References>.
 *					
 *	`note`			none
 */
 

#ifndef _REFERENCES_H_
#define _REFERENCES_H_

#include<iostream>

namespace lab4{

	namespace references{
	
		class References{
		public:
			

			friend std::ostream& operator<<(std::ostream& stream, References &obj);

		private:
			char *word;
			int *pages;//pages numbers
			int _size;//number of pages
		};

		std::ostream& operator<<(std::ostream& stream, References &obj){
			stream << obj.word << " " << obj.pages << " " << obj._size << std::endl;
		}
	
	}

}

#endif /* _REFERENCES_H_ */