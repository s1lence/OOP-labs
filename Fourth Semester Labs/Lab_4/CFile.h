/*
 * `file` 			CFile.h
 * `written` 		July 25 2017 8:37:21
 * `last modified`	July 27 2017 0:52:43
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
 *	`note`			data expects to follow 'dd/mm/yyyy' format
 *					csv string required to follow 'name;date' format
 */
 

#ifndef _CFILE_H_
#define _CFILE_H_

#include<iostream>

namespace lab4{

	namespace cfile{
	
		class CFile{
		public:
			
			CFile() = delete;
			CFile(char* name, char* date);
			CFile(char* csvData);
			~CFile();

			 /* comparison by data value */
			bool operator<(const CFile&);

			 /* changes file name */
			void rename(char*);

			friend std::ostream& operator<<(std::ostream& stream, CFile &obj);

		private:
			char *_filename;
			char *_creation_date;

		};

		std::ostream& operator<<(std::ostream& stream, CFile &obj);
	
	}

}

#endif /* _CFILE_H_ */