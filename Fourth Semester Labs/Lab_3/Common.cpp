/************************************************
* file: "Common.cpp"
* synopsis: definition common parent class for third lab
* author: R. Neshta
* written: 08/07/17
* last modified: 18/07/17
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

			if (input.eof()){ /* skip if sth goes wrong */
				std::cerr << "Error opening file. Program terminated";
				exit(1);
			}

			/* reading line and creating vector of objects */
			while (!input.eof()){
				input.getline(readed, 500);
				objects.push_back(*(new StoredData(readed)));
			}

			/* sorting objects to build perfectly balanced tree */
			size = objects.size();
			std::sort(objects.begin(), objects.end());
			
			/* building tree */
			root = buildTree(objects, 0, size - 1);
			input.close();
		}

		template<class StoredData>
		ProtectedBinaryTreeInterface<StoredData>::~ProtectedBinaryTreeInterface()
		{
			/* recursively deletes all elements */
			erase(root);

		}

		template<class StoredData>
		void ProtectedBinaryTreeInterface<StoredData>::emplace(
			const StoredData& item)
		{
			ProtectedBinaryNodeInterface<StoredData> *previous = root, *current = root;

			/* searching place to insertion */
			while (current){
				previous = current;
				if (current->data < item)
					current = current->right;
				else
					current = current->left;
			}

			/* insertion */
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

			/* if !last - applies to all */
			if (nullptr == last)
				last = getMax();

			while (current != last){
				obj2call(*current);
				current = next(*current);
			}

			/* 
			*	call on last element out of the cycle;
			*	if deletion required eraseContainer'll do all dirty job
			*
			*/

			obj2call(*current);
			obj2call.eraseContainer();
		}

		template<class StoredData>
		void ProtectedBinaryTreeInterface<StoredData>::remove(
			ProtectedBinaryNodeInterface<StoredData> *item)
		{
			if (nullptr == item)
				return;

			/* get item that will replace target in tree */
			ProtectedBinaryNodeInterface<StoredData> *replacer = min(*item->right);
						
			if (replacer){

				/* direct binding nodes */
				if (replacer != item->right) /* recursion safety */
					replacer->right = item->right;

				if (replacer != item->left) /* recursion safety */
					replacer->left = item->left;
				
				replacer->parent->left = replacer->left;
				replacer->parent = item->parent;
				
				/* reverce binding nodes */
				if (replacer->right)
					replacer->right->parent = replacer;

				if (replacer->left)
					replacer->left->parent = replacer;

				if (replacer->parent){ /* means if(replacer != root) */
					if (item == replacer->parent->left)
						replacer->parent->left = replacer;
					else
						replacer->parent->right = replacer;
				}
				else /* root needs to be repointed */
					root = replacer;
			}
			else{	/* item->right == nullptr */
				if (item->parent){	/* saving left subtree */
					if (item == item->parent->left)
						item->parent->left = item->left;
					else
						item->parent->right = item->left;
					
					if (item->left)
						item->left->parent = item->parent;
				}
				else{	/* item == root */
					root = item->left;
					if (item->left)
						item->left->parent = nullptr;
				}
			}

			/* deleting target */
			item->data.cleanStrings();
			delete item;
			--size;
		}

		template<class StoredData>
		void 
			ProtectedBinaryTreeInterface<StoredData>::erase(
			ProtectedBinaryNodeInterface<StoredData> *subtree)
		{
			/* quit out of recursion */
			if (nullptr == subtree)
				return;

			/* recursive descent */
			erase(subtree->left);
			erase(subtree->right);

			/* deleting elements */
			subtree->data.cleanStrings();
			delete subtree;
			--size;
		}

		template<class StoredData>
		ProtectedBinaryNodeInterface<StoredData>*
			ProtectedBinaryTreeInterface<StoredData>::find(
			const StoredData& item)const
		{
				ProtectedBinaryNodeInterface<StoredData> *p = getMin();

				while (p){ /* searching trough all tree */
					if (p->data == item)
						return p;

					p = next(*p);
				}

				return nullptr; /* search fails */
		}

		template<class StoredData>
		ProtectedBinaryNodeInterface<StoredData>* 
			ProtectedBinaryTreeInterface<StoredData>::next(
			ProtectedBinaryNodeInterface<StoredData> &current)const
		{
			ProtectedBinaryNodeInterface<StoredData> *next;

			if (nullptr == current.right){ /* taking the largest */
				next = &current;

				/* next will be the parent of the first element which is left of his own parent(the next) */
				while (next->parent && next->parent->left != next)
					next = next->parent;

				return next->parent;
			}
			else{ /* searching the smalest of the right subtree */
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

			if (nullptr == current.left){ /* taking the smallest */
				prev = &current;

				/* the next will be the parent of the first element which is the right of his own parent(next) */
				while (prev->parent && prev->parent->right != prev)
					prev = prev->parent;

				return prev->parent;
			}
			else{ /* searching the largest of the left subtree */
				prev = current.left;

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

			if (nullptr == min) /* min of empty tree is nullptr */
				return min;

			while (min->left) /* min is the most left element of the left subtree */
				min = min->left;

			return min;
		}

		template<class StoredData>
		ProtectedBinaryNodeInterface<StoredData>* 
			ProtectedBinaryTreeInterface<StoredData>::max(
			ProtectedBinaryNodeInterface<StoredData> &root)const
		{
			ProtectedBinaryNodeInterface<StoredData> *max = &root;

			if (nullptr == max) /* max of empty is nullptr */
				return max;

			while (max->right) /* max is the most right element of right subtree */
				max = max->right;

			return max;
		}

		template<class StoredData>
		std::size_t ProtectedBinaryTreeInterface<StoredData>::depth(
			ProtectedBinaryNodeInterface<StoredData> &root,
			std::size_t current)const
		{
			std::size_t left = current, right = current;

			/* recursive descent calculates all tree depths */
			if (nullptr != root.left)
				left = depth(*root.left, current + 1);

			if (nullptr != root.right)
				right = depth(*root.right, current + 1);

			/* max depth returns */
			return left > right ? left : right;
		}

		template<class StoredData>
		ProtectedBinaryNodeInterface<StoredData> * 
			ProtectedBinaryTreeInterface<StoredData>::buildTree(
			std::vector<StoredData> &objects, 
			int leftBound, 
			int rightBound)
		{
			/* quit out of recursion */
			if (rightBound < leftBound)
				return nullptr;

			/* middle is the root of current subtree */
			int middle = (rightBound - leftBound) / 2;

			ProtectedBinaryNodeInterface<StoredData> * 
				root = new ProtectedBinaryNodeInterface<StoredData>(objects[middle + leftBound], nullptr, nullptr, nullptr);

			/* building tree with elements that are left from the middle */
			root->left = buildTree(objects, leftBound, leftBound + middle - 1);
			if (root->left) /* if success - point it to parent */
				root->left->parent = root;

			/* building tree with elements that are right from the middle */
			root->right = buildTree(objects, leftBound + middle + 1, rightBound);
			if (root->right) /* if success - point it to parent */
				root->right->parent = root;

			return root; /* return tree */
		}

	}
	
}

#endif /*_COMMON_REALISATION_*/
