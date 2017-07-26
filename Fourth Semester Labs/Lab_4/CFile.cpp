/*
 * `file` 			CFile.cpp
 * `written` 		July 26 2017 12:17:45
 * `last modified`	July 26 2017 12:52:23
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		implementation of c file class
 *
 *	Description: 	class has information about file:
 *					-name;
 *					-creation date;
 *					-size.
 *					
 *	`note`			data expects to follow 'dd/mm/yyyy' format
 *					csv string required to follow 'name;date' format
 */
 
#include "CFile.h"

namespace lab4{

	namespace cfile{
	
		CFile::CFile(char* name, char* date)
		{
			int len = strlen(name);
			_filename = new char[len + 1];
			strncpy_s(_filename, len + 1, name, len);

			len = strlen(date);
			_creation_date = new char[len + 1];
			strncpy_s(_creation_date, len + 1, date, len);
		}

		CFile::CFile(char* csv)
		{
			int len = strlen(csv);
			char * tmp = new char[len + 1];
			for (int i = 0; i <= len; ++i){
				if (';' == csv[i])
					tmp[i] = '\0';
				else
					tmp[i] = csv[i];
			}

			len = strlen(tmp) + 1;
			_filename = new char[len];
			strncpy_s(_filename, len, tmp, len - 1);

			int newlen = strlen(tmp + len) + 1;
			_creation_date = new char[newlen];
			strncpy_s(_creation_date, newlen, tmp + len, newlen - 1);
		}

		CFile::~CFile()
		{
			delete[] _creation_date;
			delete[] _filename;
		}

		bool CFile::operator<(const CFile& cf)
		{
			return
				0 > strncmp(_creation_date + 6, cf._creation_date + 6, 4) ||
				0 > strncmp(_creation_date + 3, cf._creation_date + 3, 2) ||
				0 > strncmp(_creation_date, cf._creation_date, 2);
		}

		void CFile::rename(char* name)
		{
			int nLen;
			if (strlen(_filename) != (nLen = strlen(name))){
				delete[] _filename;
				_filename = new char[nLen + 1];
			}
			strncpy_s(_filename, nLen + 1, name, nLen);
		}

		std::ostream& operator<<(std::ostream& stream, CFile &obj)
		{
			stream << obj._filename << " " << obj._creation_date << std::endl;
			return stream;
		}

	}

}