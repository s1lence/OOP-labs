/************************************************
* file: "Tickets.cpp"
* synopsis: definition classes for second variant of third lab
* author: R. Neshta
* written: 19/07/17
* last modified: 19/07/17
***********************************************/

#include"Tickets.h"

using namespace lab3::tickets;

typedef CTreeNode node;
typedef CBinTree tree;

node::CTreeNode(const char *csvData)
{

	/*
	*	csvData based on this template:
	*		m_Destination; m_Flight; m_PassengerName;m_FlightDate
	*
	*/

	int j = 0, size = std::strlen(csvData);
	std::string buffers[4];

	for (int i = 0; i < size; ++i){

		if (csvData[i] == ';')
			++j;
		else
			buffers[j] += csvData[i];

	}

	m_Flight = std::atoi(buffers[1].c_str());

	m_Destination = new char[buffers[0].length() + 1];
	m_PassengerName = new char[buffers[2].length() + 1];
	m_FlightDate = new char[buffers[3].length() + 1];

	strncpy_s(const_cast<char*>(m_Destination), buffers[0].length() + 1, buffers[0].c_str(), buffers[0].length() + 1);
	strncpy_s(const_cast<char*>(m_PassengerName), buffers[2].length() + 1, buffers[2].c_str(), buffers[2].length() + 1);
	strncpy_s(const_cast<char*>(m_FlightDate), buffers[3].length() + 1, buffers[3].c_str(), buffers[3].length() + 1);
}

bool node::operator==(const node &nd)
{
	if (nullptr != m_PassengerName && nullptr != nd.m_PassengerName) /* if we searching by name then also compare it */
		return (0 == strcmp(m_PassengerName, nd.m_PassengerName)) &&
		(m_Flight == nd.m_Flight) && (0 == strcmp(m_FlightDate, nd.m_FlightDate));

	return (m_Flight == nd.m_Flight) && (0 == strcmp(m_FlightDate, nd.m_FlightDate));
}

void node::cleanStrings()
{
	delete[] m_Destination;
	delete[] m_PassengerName;
	delete[] m_FlightDate;
}

void node::print()const
{
	std::cout << "Flight number: " << m_Flight << std::endl << "Passenger name: " << m_PassengerName << std::endl << "Target destination: " << m_Destination << std::endl <<
		"Flight date: " << m_FlightDate << std::endl << std::endl;
	std::cout.flush(); /* instant print */
}

void tree::addApplication(CTreeNode &node)
{
	emplace(node);
}

void tree::deleteApplication(unsigned flight, const char* name, const char *date)
{
	CTreeNode item(name, date, flight);
	remove(find(item));
}

void tree::printNdelete(unsigned flight, const char* date)
{

	CTreeNode stored(nullptr,date,flight); /* binary node interface takes StoredDataType object in ctor */
	common::ProtectedBinaryNodeInterface<CTreeNode> item(stored, nullptr, nullptr);
	std::vector<CTreeNode*> found;

	/* appliable takes binary node interface object in ctor */
	utility::Appliable < CBinTree
		, common::ProtectedBinaryNodeInterface<CTreeNode>,
		std::vector < CTreeNode* >> what2call(const_cast<CBinTree*>(this), &item, utility::Operations::PRINT_N_DELETE, &found);

	apply(what2call, getMin()); /* applies to all */
}

void tree::print()const
{
	/* simlple print doesn't require any node object because doesn't perform any comparisons */
	utility::Appliable < CBinTree
		, common::ProtectedBinaryNodeInterface<CTreeNode>,
		std::vector < CTreeNode* >> funcObj(const_cast<CBinTree*>(this), nullptr, utility::Operations::PRINT, nullptr);

	apply(funcObj, getMin());
}