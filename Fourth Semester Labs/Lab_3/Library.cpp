/************************************************
* file: "Library.cpp"
* synopsis: definition classes for first variant of third lab
* author: R. Neshta
* written: 12/07/17
* last modified: 18/07/17
***********************************************/

#include"Library.h"

using namespace lab3::library;

typedef CTreeNode node;
typedef CBinTree tree;

node::CTreeNode(const char *csvData)
{

	/*
	 *	csvData based on this template:
	 *		m_Bookid; m_Author; m_Title; m_Year; m_Quantity
	 *	
	 */
	
	int j = 0, size = std::strlen(csvData);
	std::string buffers[5];

	for (int i = 0; i < size; ++i){
			
		if (csvData[i] == ';')
			++j;
		else
			buffers[j] += csvData[i];
	
	}

	m_Bookid = std::atoi(buffers[0].c_str());

	m_Author = new char[buffers[1].length() + 1];
	m_Title = new char[buffers[2].length() + 1];

	strncpy_s(const_cast<char*>(m_Author), buffers[1].length() + 1, buffers[1].c_str(), buffers[1].length() + 1);
	strncpy_s(const_cast<char*>(m_Title), buffers[2].length() + 1, buffers[2].c_str(), buffers[2].length() + 1);

	m_Year = std::atoi(buffers[3].c_str());
	m_Quantity = std::atoi(buffers[4].c_str());
}

bool node::operator==(const node &nd)
{
	if (nullptr != m_Author)
		return m_Author == nd.m_Author;

	if (nullptr != m_Title)
		return m_Title == nd.m_Title;

	return m_Bookid == nd.m_Bookid;
}

void node::print()const
{
	std::cout << "Book id: " << m_Bookid << std::endl << "Author: " << m_Author << std::endl <<
		"Title: " << m_Title << std::endl << "Year: " << m_Year << std::endl <<
		"Quantity: " << m_Quantity << std::endl << std::endl;
	std::cout.flush();
}

void node::cleanStrings()
{
	delete[] m_Author;
	delete[] m_Title;
}

void tree::addBook(CTreeNode &node)
{
	emplace(node);
}

void tree::deleteBook(unsigned bookid)
{
	CTreeNode item(nullptr, nullptr, bookid);
	remove(find(item));
}

void tree::findByAuthor(const char* author)
{
	CTreeNode stored(author, nullptr, 0);
	common::ProtectedBinaryNodeInterface<CTreeNode> item(stored, nullptr, nullptr);

	utility::Appliable < library::CBinTree
		, common::ProtectedBinaryNodeInterface<library::CTreeNode>,
		std::vector < library::CTreeNode* >> what2call(const_cast<CBinTree*>(this), &item, utility::Operations::FIND_SINGLE);

	apply(what2call, getMin());
}

void tree::findByName(const char *name)
{
	CTreeNode stored(nullptr, name, 0);
	common::ProtectedBinaryNodeInterface<CTreeNode> item(stored, nullptr, nullptr);

	utility::Appliable < library::CBinTree
		, common::ProtectedBinaryNodeInterface<library::CTreeNode>,
		std::vector < library::CTreeNode* >> what2call(const_cast<CBinTree*>(this), &item, utility::Operations::FIND_SINGLE);

	apply(what2call, getMin());
}

void tree::print()const
{
	utility::Appliable < library::CBinTree
		, common::ProtectedBinaryNodeInterface<library::CTreeNode>,
		std::vector < library::CTreeNode* >> funcObj(const_cast<CBinTree*>(this), nullptr, utility::Operations::PRINT);
	
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