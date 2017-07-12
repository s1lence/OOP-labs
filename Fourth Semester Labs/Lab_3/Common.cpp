/************************************************
* file: "Common.cpp"
* synopsis: definition common parent class for third lab
* author: R. Neshta
* written: 08/07/17
* last modified: 12/07/17
***********************************************/


#include"Common.h"

namespace lab3{

	namespace common{

		template<class StoredData>
		ProtectedBinaryTreeInterface<StoredData>::ProtectedBinaryTreeInterface(
			const char *csvFileName)
		{

			std::ifstream input(csvFileName, std::ios_base::in);
			std::vector<StoredData> objects;
			const char* readed;

			while (!std::ios_base::eof){
				std::ifstream::getline(readed);
				objects.push_back(StoredData(readed));
			}

			int size = objects.size();
			std::qsort(&objects, objects.size(), sizeof(StoredData));

			root = buildTree(objects, 0, size);
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
			ProtectedBinaryNodeInterface<StoredData> *previous, *current = root;

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
		}

		template<class StoredData>
		void ProtectedBinaryTreeInterface<StoredData>::apply(
			void(*p2funcExe)(ProtectedBinaryNodeInterface<StoredData>&),
			ProtectedBinaryNodeInterface<StoredData> *first,
			ProtectedBinaryNodeInterface<StoredData> *last)
		{

			ProtectedBinaryNodeInterface<StoredData> *current = first;
			while (current != last){

				p2funcExe(current);
				current = next(current);

			}
		}

		template<class StoredData>
		void ProtectedBinaryTreeInterface<StoredData>::remove(
			ProtectedBinaryNodeInterface<StoredData> &item)
		{

			if (item->right){

				ProtectedBinaryNodeInterface<StoredData> * 
					willRemoved = min(item->right);

				item->data = willRemoved->data;

				willRemoved->parent->left = nullptr;
				delete willRemoved;

			}
			else{

				if (item->left)
					item->left->parent = item->parent;

				if (item->parent){
					if (item->parent->left == item)
						item->parent->left = item->left;
					else
						item->parent->right = item->left;
				}

				delete item;
			}
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
		}

		template<class StoredData>
		ProtectedBinaryNodeInterface<StoredData>* 
			ProtectedBinaryTreeInterface<StoredData>::next(
			ProtectedBinaryNodeInterface<StoredData> &current)
		{
			ProtectedBinaryNodeInterface<StoredData> *next;

			if (nullptr == current.right){
				next = current;

				while (next->parent && next->parent->left != next)
					next = next->parent;
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
			ProtectedBinaryNodeInterface<StoredData> &current)
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
			ProtectedBinaryNodeInterface<StoredData> &root)
		{
			ProtectedBinaryNodeInterface<StoredData> *min = root;

			while (min->left)
				min = min->left;

			return min;
		}

		template<class StoredData>
		ProtectedBinaryNodeInterface<StoredData>* 
			ProtectedBinaryTreeInterface<StoredData>::max(
			ProtectedBinaryNodeInterface<StoredData> &root)
		{
			ProtectedBinaryNodeInterface<StoredData> *max = root;

			while (max->right)
				max = max->right;

			return max;
		}

		template<class StoredData>
		std::size_t ProtectedBinaryTreeInterface<StoredData>::depth(
			ProtectedBinaryNodeInterface<StoredData> &root,
			std::size_t current)
		{

			std::size_t left = depth(root->left);
			std::size_t right = depth(root->right);

			return left > right ? left : right;
		}

		template<class StoredData>
		ProtectedBinaryNodeInterface<StoredData> * 
			ProtectedBinaryTreeInterface<StoredData>::buildTree(
			std::vector<StoredData> &objects, 
			std::size_t &leftBound, 
			std::size_t &rightBound)
		{

			std::size_t middle = (rightBound - leftBound) / 2;
			ProtectedBinaryNodeInterface<StoredData> * 
				root = new ProtectedBinaryNodeInterface<StoredData>(objects[middle + leftBound], nullptr, nullptr, nullptr);

			root->left = buildTree(objects, leftBound, middle - 1);
			root->left->parent = root;

			root->right = buildTree(objects, middle + 1, rightBound);
			root->right->parent = root;

			return root;
		}

	}

}


