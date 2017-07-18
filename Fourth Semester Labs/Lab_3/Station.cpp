/************************************************
* file: "Station.cpp"
* synopsis: definition classes for third variant of third lab
* author: R. Neshta
* written: 18/07/17
* last modified: 19/07/17
***********************************************/

#include"Station.h"

using namespace lab3::station;

typedef CTreeNode node;
typedef CBinTree tree;

node::CTreeNode(const char *csvData)
{

	/*
	*	csvData based on this template:
	*		m_TrainNumber; m_Destination; m_DepartureTime
	*
	*/

	int j = 0, size = std::strlen(csvData);
	std::string buffers[3];

	for (int i = 0; i < size; ++i){

		if (csvData[i] == ';')
			++j;
		else
			buffers[j] += csvData[i];

	}

	m_TrainNumber = std::atoi(buffers[0].c_str());

	m_Destination = new char[buffers[1].length() + 1];
	m_DepartureTime = new char[buffers[2].length() + 1];

	strncpy_s(const_cast<char*>(m_Destination), buffers[1].length() + 1, buffers[1].c_str(), buffers[1].length() + 1);
	strncpy_s(const_cast<char*>(m_DepartureTime), buffers[2].length() + 1, buffers[2].c_str(), buffers[2].length() + 1);
}

bool node::operator==(const node &nd)
{
	if (nullptr != m_Destination && nullptr != nd.m_Destination) /* if we searching not by destination then pass it */
		return 0 == strcmp(m_Destination, nd.m_Destination);

	return m_TrainNumber == nd.m_TrainNumber;
}

void node::print()const
{
	std::cout << "Train number id: " << m_TrainNumber << std::endl << "Destination station: " << m_Destination << std::endl <<
		"Departure time: " << m_DepartureTime << std::endl << std::endl;
	std::cout.flush(); /* instant print */
}

void node::cleanStrings()
{
	delete[] m_DepartureTime;
	delete[] m_Destination;
}

void tree::deleteTrain(unsigned number)
{
	CTreeNode item(nullptr, number);
	remove(find(item));
}

void tree::getStationInfo(const char *name, std::vector<station::CTreeNode*> *p2vector)
{
	CTreeNode local(name, 0); /* binary node interface takes StoredDataType object in ctor */
	common::ProtectedBinaryNodeInterface<CTreeNode> item(local, nullptr, nullptr);

	utility::Appliable<station::CBinTree, common::ProtectedBinaryNodeInterface<CTreeNode>, std::vector<CTreeNode*>>
		callable(const_cast<CBinTree*>(this), &item, utility::Operations::FIND_MULTIPLE, p2vector);

	apply(callable, getMin()); /* applies to all */
}


void tree::findByNumber(unsigned number, std::vector<CTreeNode*> *p2vector)
{
	CTreeNode stored(nullptr, number); /* binary node interface takes StoredDataType object in ctor */
	common::ProtectedBinaryNodeInterface<CTreeNode> item(stored, nullptr, nullptr);

	/* appliable takes binary node interface object in ctor */
	utility::Appliable < CBinTree
		, common::ProtectedBinaryNodeInterface<CTreeNode>,
		std::vector < CTreeNode* >> what2call(const_cast<CBinTree*>(this), &item, utility::Operations::FIND_SINGLE, p2vector);

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


void tree::apply2All(
	utility::Appliable <
	CBinTree,
	common::ProtectedBinaryNodeInterface<CTreeNode>,
	std::vector < CTreeNode* >> &callable)
{
	apply(callable, getMin());
}
