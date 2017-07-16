/************************************************
* file: "Library.cpp"
* synopsis: definition classes for first variant of third lab
* author: R. Neshta
* written: 12/07/17
* last modified: 12/07/17
***********************************************/

#include"Library.h"

using namespace lab3::library;

typedef CTreeNode node;
typedef CBinTree tree;

node::CTreeNode(const char *csvData){

	/*
	 *	csvData created on this template:
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

	m_Author = buffers[1].c_str();
	m_Title = buffers[2].c_str();

	m_Year = std::atoi(buffers[3].c_str());
	m_Quantity = std::atoi(buffers[4].c_str());
}

bool node::operator==(const node &nd){
	if (nullptr == m_Author)
		return m_Title == nd.m_Title;
	
	return m_Author == nd.m_Author;
}

void node::print()const{
	std::cout << m_Bookid << " " << m_Author <<
		" " << m_Title << " " << m_Year <<
		" " << m_Quantity;
}

void tree::addBook(CTreeNode &node){
	emplace(node);
}

void tree::deleteBook(unsigned bookid){

}

void tree::findByAuthor(utility::Appliable<tree,const char*, node, std::vector<node*>> &what2call){

	apply(what2call, getMin());
}

void tree::findByName(utility::Appliable<tree,const char*, node, std::vector<node*>> &what2call){
	apply(what2call, getMin());
}
