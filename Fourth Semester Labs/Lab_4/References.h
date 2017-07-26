/*
 * `file` 			References.h
 * `written` 		July 25 2017 8:40:19
 * `last modified`	July 27 2017 0:52:43
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
 *	`note`			csv string required to follow 'word;page page page;size' format
 */
 

#ifndef _REFERENCES_H_
#define _REFERENCES_H_

#include<iostream>
#include<sstream>

namespace lab4{

	namespace references{
	
		class References{
		public:
			References() = delete;
			References(char* w, int* p, int s);
			References(char* csv);
			~References();

			 /* compares using _size member */
			bool operator<(const References&);

			 /* sets new word */
			void rename(char* word);

			friend std::ostream& operator<<(std::ostream& stream, References &obj);

		private:
			char *word;
			int *pages;//pages numbers
			int _size;//number of pages
		};

		std::ostream& operator<<(std::ostream& stream, References &obj);
	
	}

}

#endif /* _REFERENCES_H_ */