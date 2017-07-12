/************************************************
* file: "Common.h"
* synopsis: declaration common parent classes for third lab
* author: R. Neshta
* written: 08/07/17
* last modified: 12/07/17
***********************************************/

#ifndef _COMMON_H_
#define _COMMON_H_

#include<fstream>
#include<vector>

namespace lab3{

	namespace common{

		template<class StoredDataType>
		struct ProtectedBinaryNodeInterface{

			typedef ProtectedBinaryNodeInterface _bin_node;

			StoredDataType data;

			_bin_node * left;
			_bin_node * right;
			_bin_node * parent;

			// creates empty node
			ProtectedBinaryNodeInterface() :left(nullptr), right(nullptr), parent(nullptr){}

			// creates node with given data
			ProtectedBinaryNodeInterface(const StoredDataType &data,
				_bin_node *left, _bin_node *right, _bin_node *father = nullptr)
				:data(data), left(left), right(right), parent(father){}

			// copy ctor
			ProtectedBinaryNodeInterface(const _bin_node &node)
				:data(node.data), left(node.left), right(node.right), parent(node.parent){}

			// nothing to be destructed here
			~ProtectedBinaryNodeInterface(){}

		};

		template<class StoredData>
		class ProtectedBinaryTreeInterface{

			typedef ProtectedBinaryNodeInterface<StoredData> _bin_node;

		protected:

			// those aren't allowed by task description
			ProtectedBinaryTreeInterface() = delete;
			ProtectedBinaryTreeInterface(const _bin_node&) = delete;
			
			// object can be initialised only from *.csv file
			ProtectedBinaryTreeInterface(const char* csvFileName);

			// cleanes trash
			~ProtectedBinaryTreeInterface();

			// inserts new node
			void emplace(const StoredData& item);

			// applies given function to all elements in given range:
			// first includes, last excludes
			void apply(void(*p2funcExe)(_bin_node&), _bin_node * first, _bin_node * last = nullptr);

			// deletes given node
			void remove(_bin_node &item);

			// erases given tree
			void erase(_bin_node *subtree);

			// searches given data in tree using given predicate function
			_bin_node* find(bool(*p2funcComp)(_bin_node const*, const StoredData&), const StoredData&);
			
			/* functions for sequential passage */
			_bin_node* next(_bin_node &current); // gives next according to order
			_bin_node* prev(_bin_node &current); // gives previous according to order
			
			/* service functions */

			_bin_node* min(_bin_node &root); // gives minimum element of given tree
			_bin_node* max(_bin_node &root); // gives maximum elements of given tree

			std::size_t depth(_bin_node &root, std::size_t current = 0); // returns depth of given tree
			std::size_t heigth(void){ return depth(root); } // returns tree height
			
			_bin_node * buildTree(std::vector<StoredData>&, std::size_t&, std::size_t&); // requires sorted vector of objects

		private:

			_bin_node * root;
			std::size_t size;

		};

	}

}

#endif // !_COMMON_H_