#pragma once


#include "./pair.hpp"
#include "./node.hpp"

class Node;
namespace ft
{

	template<class Key,class T, class Compare = std::less<Key>>
	class Tree
	{
		public :
			int												height;
			int 											diff;
			typedef typename ft::Node<class Key, class T>	nodeType;

			nodeType _root;
			size_t	_height;
			size_t	_size;

			nodeType *r_rotate(nodeType *node)
			{

				nodeType *newRoot = node->getlChild();
				node->setlChild(newRoot->getrChild());
				newRoot->setrChild(node);
				
				updateH(node);
				updateH(newRoot);
				return (newRoot);
			}

			nodeType *l_rotate(nodeType *node)
			{

				nodeType *newRoot = node->getrChild();
				node->setrChild(newRoot->getlChild());
				newRoot->setlChild(node);
				
				updateH(node);
				updateH(newRoot);
				return (newRoot);
			}
			
			void	updateH(nodeType *node)
			{
				if (!node)
					return;
				node->setHeight(0);
				if (node->getlChild())
					node->setHeight(node->getlChild()->getHeight() + 1);
				if (node->getrChild())
					if (node->getrChild()->getHeight() >= node->getHeight())
						node->setHeight(node->getrChild()->getHeight() + 1);
			}

	};
}


