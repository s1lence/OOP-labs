/*
 * `file` 			CFile.h
 * `written` 		July 25 2017 8:37:21
 * `last modified`	July 25 2017 17:25:24
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		c file class interface
 *
 *	Description: 	class has information about file:
 *					-name;
 *					-creation date;
 *					-size.
 *					Methods must provide ability of creation and future work with List<CFile>.
 *					
 *	`note`			none
 */
 

#ifndef _CFILE_H_
#define _CFILE_H_

#include<iostream>

namespace lab4{

	namespace cfile{
	
		class CFile{
		public:
			

			friend std::ostream& operator<<(std::ostream& stream, CFile &obj);

		private:
			char *_filename;
			char *_creation_date;

		};

		std::ostream& operator<<(std::ostream& stream, CFile &obj){
			stream << obj._filename << " " << obj._creation_date << std::endl;
		}
	
	}

}

#endif /* _CFILE_H_ */