/************************************************
* file: "Tickets.h"
* synopsis: declaration classes for second variant of third lab
* author: R. Neshta
* written: 18/07/17
* last modified: 18/07/17
***********************************************/

#ifndef _TICKETS_H_
#define _TICKETS_H_

#include"Common.h"
#include"Utility.h"

namespace lab3{

	namespace tickets{
		class CTreeNode{

		private:

			unsigned m_Flight;
			const char* m_Destination;
			const char* m_PassengerName;
			const char* m_FlightDate;

		};

		class CBinTree : common::ProtectedBinaryTreeInterface<CTreeNode>{
		public:

		};

	}

}

#endif /* _TICKETS_H_ */
