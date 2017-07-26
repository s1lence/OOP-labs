/*
 * `file` 			References.cpp
 * `written` 		July 26 2017 12:53:25
 * `last modified`	July 27 2017 0:52:43
 *
 *	Author:			R. Neshta
 *	Contact: 		Ruslan.Neshta@gmail.com
 *
 *	`synopsis` 		references class implementation
 *
 *	Description: 	class has information about references to words:
 *					-word;
 *					-numbers of pages where it appears;
 *					-number of pages where it appears.
 *					
 *	`note`			csv string required to follow 'word;page page page;size' format
 */
 
#include "References.h"

namespace lab4{

	namespace references{

		References::References(char* w, int* p, int s) :pages(p), _size(s)
		{
			int len = strlen(w);
			word = new char[len + 1];
			strncpy_s(word, len + 1, w, len);
		}

		References::References(char* csv)
		{
			int len = strlen(csv);
			char * tmp = new char[len + 1];

			for (int i = 0; i < len; ++i){

				if (';' == csv[i])
					tmp[i] = '\0';
				else
					tmp[i] = csv[i];
			}

			len = strlen(tmp) + 1;
			word = new char[len];
			strncpy_s(word, len, tmp, len - 1);

			int count = 0, newlen = strlen(tmp + len) + 1;
			for (int i = 0; i < newlen; ++i){

				if (' ' == i[tmp + len])
					++count;
			}

			pages = new int[++count];
			std::string s;

			for (int i = 0, j = 0; i <= newlen; ++i){

				if (' ' == i[tmp + len] || '\0' == i[tmp + len]){
					std::stringstream ss(s.c_str());
					ss >> pages[j++];
					s.clear();
				}
				else
					s += i[tmp + len];
			}

			_size = count;
		}

		References::~References()
		{
			delete[] word;
			delete[] pages;
		}

		bool References::operator<(const References& ref)
		{
			return _size < ref._size;
		}

		void References::rename(char* _word)
		{
			int len = strlen(_word);
			delete[] word;
			word = new char[len + 1];
			strncpy_s(word, len + 1, _word, len);
		}

		std::ostream& operator<<(std::ostream& stream, References &obj)
		{
			stream << obj.word << " ";
			for (int i = 0; i < obj._size; ++i)
				stream << obj.pages[i]<<" ";
			stream << " " << obj._size << std::endl;
			return stream;
		}

	}

}