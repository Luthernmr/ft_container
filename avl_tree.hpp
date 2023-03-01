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
			typedef typename ft::Node<class Key, class T>*	nodePtr;
			typedef typename ft::Node<class Key, class T>	nodeType;

			nodePtr root;
			size_t	height;
			size_t	size;
	};
}


