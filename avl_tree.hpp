#pragma once


#include "./pair.hpp"
#include "./node.hpp"

namespace ft
{
	template<class Node, class Compare, class Alloc>
	class Tree
	{
		class Pair;

		public :
			typedef Node										node_type;
			typedef Node*										node_ptr;
			typedef Compare										key_compare;
			typedef Alloc										node_allocator;
			typedef typename node_allocator::size_type			size_type;
			typedef typename node_allocator::difference_type	difference_type;

			key_compare											_comp;
			node_ptr 											_root;
			size_t												_size;
			node_allocator										_alloc;

		public:
		/* ------------------------ Constructor / Destructor ------------------------ */
			Tree(const key_compare &comp = key_compare(), const node_allocator &alloc = node_allocator()) : _comp(comp), _root(NULL), _size(0), _alloc(alloc){}
			~Tree()
			{
				deleteall(_root);
			}

			Tree &operator=(const Tree &obj)
			{
				_comp = obj._comp;
				_root = obj._root;
				_size = obj._size;
				_alloc = obj._alloc;

				return (*this);
			}

			
		/* ----------------------------- Simple Rotation ---------------------------- */
			node_ptr r_rotate(node_ptr node)
			{
				node_ptr newRoot = node->getlChild();
				node->setlChild(newRoot->getrChild());
				newRoot->setrChild(node);
				
				updateH(node);
				updateH(newRoot);
				return (newRoot);
			}

			node_ptr l_rotate(node_ptr node)
			{

				node_ptr newRoot = node->getrChild();
				node->setrChild(newRoot->getlChild());
				newRoot->setlChild(node);
				
				updateH(node);
				updateH(newRoot);
				return (newRoot);
			}

		/* --------------------------- Update node Height --------------------------- */
			void	updateH(node_ptr node)
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

		/* -------------------------------- Balancer -------------------------------- */
			int diffH (node_ptr node)
			{
				return (node->getlChild()->getHeight() - node->getrChild()->getHeight());
			}

			node_ptr balance(node_ptr node)
			{
				if (!node)
					return(NULL);
				else if (diffH(node) > 1)
				{
					if (diffH(node->getlChild()) < 0)
						node->setlChild(l_rotate(node->getlChild()));
					return (r_rotate(node));
				}
				else if (diffH(node) < -1)
				{
					if (diffH(node->getrChild()) > 0)
						node->setrChild(r_rotate());
					return (l_rotate(node));
				}
				return (node);
			}
		/* -------------------------------- Capacity -------------------------------- */
			size_type size() const { return (_size); }

			size_type max_size() const {  return _alloc.max_size(); }

		/* -------------------------------- Modifier -------------------------------- */
			void deleteall(node_ptr root)
			{
				_size = 0;
 		  		if( root != NULL )
  		 		{
		 			deleteall(root->getrChild());
		 			deleteall(root->getlChild());
					_alloc.destroy(root);
					_alloc.deallocate(root, 1);
   				}
			}

			void insert(const node_type *node)
			{
				if (!node)
				{
					_size++;
					node = _alloc.construct(node)
				} 

				root = balance(*node);
			}
	
	};
};


