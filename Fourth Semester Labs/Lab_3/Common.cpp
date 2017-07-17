/************************************************
* file: "Common.cpp"
* synopsis: definition common parent class for third lab
* author: R. Neshta
* written: 08/07/17
* last modified: 17/07/17
***********************************************/


#ifndef _COMMON_REALISATION_
#define _COMMON_REALISATION_

#ifndef _COMMON_H_
#include"Common.h"
#endif

namespace lab3{

	namespace common{

		template<class StoredData>
		ProtectedBinaryTreeInterface<StoredData>::ProtectedBinaryTreeInterface(
			const char *csvFileName)
		{

			std::ifstream input(csvFileName, std::ios_base::in);
			std::vector<StoredData> objects;
			char readed[500];

			while (!input.eof()){
				input.getline(readed, 500);
				objects.push_back(*(new StoredData(readed)));
			}

			int begins = 0, size = objects.size() - 1;
			std::sort(objects.begin(), objects.end());
			
			root = buildTree(objects, begins, size);
			input.close();
		}

		template<class StoredData>
		ProtectedBinaryTreeInterface<StoredData>::~ProtectedBinaryTreeInterface()
		{

			erase(root);

		}

		template<class StoredData>
		void ProtectedBinaryTreeInterface<StoredData>::emplace(
			const StoredData& item)
		{
			ProtectedBinaryNodeInterface<StoredData> *previous = root, *current = root;

			while (current){
				previous = current;
				if (current->data < item)
					current = current->right;
				else
					current = current->left;
			}

			if (previous->data < item)
				previous->right = new ProtectedBinaryNodeInterface<StoredData>(item, nullptr, nullptr, previous);
			else
				previous->left = new ProtectedBinaryNodeInterface<StoredData>(item, nullptr, nullptr, previous);
			++size;
		}

		template<class StoredData>
		template<class Callable>
		void ProtectedBinaryTreeInterface<StoredData>::apply(
			Callable &obj2call,
			ProtectedBinaryNodeInterface<StoredData> *first,
			ProtectedBinaryNodeInterface<StoredData> *last) const
		{
			ProtectedBinaryNodeInterface<StoredData> *current = first;

			if (nullptr == last)
				last = getMax();

			while (current != last){

				obj2call(*current);
				current = next(*current);

			}

			obj2call(*current);
		}

		template<class StoredData>
		void ProtectedBinaryTreeInterface<StoredData>::remove(
			ProtectedBinaryNodeInterface<StoredData> *item)
		{
			if (nullptr == item)
				return;

			if (item->right){

				ProtectedBinaryNodeInterface<StoredData> * 
					willRemoved = min(*item->right);

				item->data = willRemoved->data;

				willRemoved->parent->left = nullptr;
				delete willRemoved;

			}
			else{

				if (item->left)
					item->left->parent = item->parent;

				if (item->parent){
					if (item == item->parent->left)
						item->parent->left = item->left;
					else
						item->parent->right = item->left;
				}

				delete item;
			}
			--size;
		}

		template<class StoredData>
		void 
			ProtectedBinaryTreeInterface<StoredData>::erase(
			ProtectedBinaryNodeInterface<StoredData> *subtree)
		{

			if (nullptr == subtree)
				return;

			erase(subtree->left);
			erase(subtree->right);

			delete subtree;
			--size;
		}

		template<class StoredData>
		ProtectedBinaryNodeInterface<StoredData>*
			ProtectedBinaryTreeInterface<StoredData>::find(
			const StoredData& item)const
		{
				ProtectedBinaryNodeInterface<StoredData> *p = getMin();

				while (p){
					if (p->data == item)
						return p;

					p = next(*p);
				}

				return nullptr;
		}

		template<class StoredData>
		ProtectedBinaryNodeInterface<StoredData>* 
			ProtectedBinaryTreeInterface<StoredData>::next(
			ProtectedBinaryNodeInterface<StoredData> &current)const
		{
			ProtectedBinaryNodeInterface<StoredData> *next;

			if (nullptr == current.right){
				next = &current;

				while (next->parent && next->parent->left != next)
					next = next->parent;

				return next->parent;
			}
			else{
				next = current.right;

				while (next->left)
					next = next->left;
			}

			return next;
		}

		template<class StoredData>
		ProtectedBinaryNodeInterface<StoredData>* 
			ProtectedBinaryTreeInterface<StoredData>::prev(
			ProtectedBinaryNodeInterface<StoredData> &current)const
		{
			ProtectedBinaryNodeInterface<StoredData> *prev;

			if (nullptr == current.left){
				prev = current;

				while (prev->parent && prev->parent->right != prev)
					prev = prev->parent;
			}
			else{
				prev = current->left;

				while (prev->right)
					prev = prev->right;
			}

			return prev;
		}

		template<class StoredData>
		ProtectedBinaryNodeInterface<StoredData>* 
			ProtectedBinaryTreeInterface<StoredData>::min(
			ProtectedBinaryNodeInterface<StoredData> &root)const
		{
			ProtectedBinaryNodeInterface<StoredData> *min = &root;

			while (min->left)
				min = min->left;

			return min;
		}

		template<class StoredData>
		ProtectedBinaryNodeInterface<StoredData>* 
			ProtectedBinaryTreeInterface<StoredData>::max(
			ProtectedBinaryNodeInterface<StoredData> &root)const
		{
			ProtectedBinaryNodeInterface<StoredData> *max = &root;

			while (max->right)
				max = max->right;

			return max;
		}

		template<class StoredData>
		std::size_t ProtectedBinaryTreeInterface<StoredData>::depth(
			ProtectedBinaryNodeInterface<StoredData> &root,
			std::size_t current)
		{

			std::size_t left = depth(root->left, current + 1);
			std::size_t right = depth(root->right, current + 1);

			return left > right ? left : right;
		}

		template<class StoredData>
		ProtectedBinaryNodeInterface<StoredData> * 
			ProtectedBinaryTreeInterface<StoredData>::buildTree(
			std::vector<StoredData> &objects, 
			int leftBound, 
			int rightBound)
		{
			if (rightBound < leftBound)
				return nullptr;

			int middle = (rightBound - leftBound) / 2;

			ProtectedBinaryNodeInterface<StoredData> * 
				root = new ProtectedBinaryNodeInterface<StoredData>(objects[middle + leftBound], nullptr, nullptr, nullptr);

			root->left = buildTree(objects, leftBound, leftBound + middle - 1);
			if (root->left)
				root->left->parent = root;

			root->right = buildTree(objects, leftBound + middle + 1, rightBound);
			if (root->right)
				root->right->parent = root;

			return root;
		}

	}
	
}

#endif /*_COMMON_REALISATION_*/
