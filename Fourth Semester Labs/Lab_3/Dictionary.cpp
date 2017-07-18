/************************************************
* file: "Dictionary.cpp"
* synopsis: definition classes for fourth variant of third lab
* author: R. Neshta
* written: 18/07/17
* last modified: 19/07/17
***********************************************/

#include"Dictionary.h"

using namespace lab3::dictionary;

typedef CTreeNode node;
typedef CBinTree tree;

node::CTreeNode(const char *csvData)
{

	/*
	*	csvData based on this template:
	*		m_EngWord; m_ItaWord;m_Page
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

	m_Page = std::atoi(buffers[2].c_str());

	m_EngWord = new char[buffers[0].length() + 1];
	m_ItaWord = new char[buffers[1].length() + 1];

	strncpy_s(const_cast<char*>(m_EngWord), buffers[0].length() + 1, buffers[0].c_str(), buffers[0].length() + 1);
	strncpy_s(const_cast<char*>(m_ItaWord), buffers[1].length() + 1, buffers[1].c_str(), buffers[1].length() + 1);
}

bool node::operator==(const node &nd)
{
	if (nullptr != m_EngWord && nullptr != nd.m_EngWord) /* if we searching not by word then pass it */
		return 0 == strcmp(m_EngWord, nd.m_EngWord);

	return m_Page == nd.m_Page;
}

void node::print()const
{
	std::cout << "English word: " << m_EngWord << std::endl << "Italian word: " << m_ItaWord << std::endl <<
		"Page number: " << m_Page << std::endl << std::endl;
	std::cout.flush(); /* instant print */
}

void node::cleanStrings()
{
	delete[] m_EngWord;
	delete[] m_ItaWord;
}

void tree::deleteByWord(const char *word)
{
	CTreeNode item(word, 0);
	remove(find(item));
}

const char* tree::operator[](const char *word)
{
	CTreeNode local(word, 0); /* binary node interface takes StoredDataType object in ctor */
	common::ProtectedBinaryNodeInterface<CTreeNode> item(local, nullptr, nullptr);

	std::vector<CTreeNode*> v;

	utility::Appliable<CBinTree, common::ProtectedBinaryNodeInterface<CTreeNode>, std::vector<CTreeNode*>>
		callable(const_cast<CBinTree*>(this), &item, utility::Operations::FIND_SINGLE, &v);

	apply(callable, getMin()); /* applies to all */

	return v[0]->m_ItaWord;
}

void tree::getPageInfo(unsigned number, std::vector<CTreeNode*> *p2vector)
{
	CTreeNode local(nullptr, number); /* binary node interface takes StoredDataType object in ctor */
	common::ProtectedBinaryNodeInterface<CTreeNode> item(local, nullptr, nullptr);

	utility::Appliable<CBinTree, common::ProtectedBinaryNodeInterface<CTreeNode>, std::vector<CTreeNode*>>
		callable(const_cast<CBinTree*>(this), &item, utility::Operations::FIND_MULTIPLE, p2vector);

	apply(callable, getMin()); /* applies to all */
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
