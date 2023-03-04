#pragma once


#include "./pair.hpp"
#include "./node.hpp"
#include "./map.hpp"

namespace ft
{
	template<class Key,class Value, class Compare = std::less<Key> >
	class Tree
	{
		class Pair;

		public :
			typedef ft::pair<const Key, Value>					pair_type;
			typedef ft::Node<pair_type>							node_type;
			typedef ft::Node<pair_type>*						node_ptr;
			typedef Compare										key_compare;
			typedef std::allocator<node_type>					node_allocator;
			typedef typename node_allocator::size_type			size_type;
			typedef typename node_allocator::difference_type	difference_type;

			key_compare											_keycomp;
			node_ptr 											_root;
			size_t												_size;
			node_allocator										_alloc;

		public:
		/* ------------------------ Constructor / Destructor ------------------------ */
			Tree(const key_compare &comp = key_compare(), const node_allocator &alloc = std::allocator<node_type>()) : _keycomp(comp), _root(NULL), _size(0), _alloc(alloc){}
			~Tree()
			{
				deleteAll(_root);
			}

			Tree &operator=(const Tree &obj)
			{
				_keycomp = obj._keycomp;
				_root = obj._root;
				_size = obj._size;
				_alloc = obj._alloc;

				return (*this);
			}
		/* ------------------------------ Start and End ----------------------------- */
			node_ptr	minValue(node_ptr node) const
			{
				node_ptr tmp = node;
				if (!tmp)
					return(NULL);
				while (tmp->getlChild())
					tmp = tmp->getlChild();
				return (tmp);
			}
			
			node_ptr	maxValue(node_ptr node) const
			{
				node_ptr tmp = node;
				if (!tmp)
					return(NULL);
				while (tmp->getrChild())
					tmp = tmp->getrChild();
				return (tmp);
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
						node->setrChild(r_rotate(node->getrChild()));
					return (l_rotate(node));
				}
				return (node);
			}
		/* -------------------------------- Capacity -------------------------------- */
			size_type size() const { return (_size); }

			size_type max_size() const {  return _alloc.max_size(); }

		/* -------------------------------- Modifier -------------------------------- */
			void deleteAll(node_ptr root)
			{
				_size = 0;
 		  		if(root != NULL)
  		 		{
		 			deleteAll(root->getrChild());
		 			deleteAll(root->getlChild());
					_alloc.destroy(root);
					_alloc.deallocate(root, 1);
   				}
			}

			void	insert(const Key& key, const Value& val)
			{	
				_root = insert_Node(_root, key, val);
				_root->setParent(NULL);	
			}

			void	insert(const pair_type &pair)
			{
				_root = insert_node(_root, pair.first, pair.second);
				_root->setParent(NULL);
			}
			
			node_ptr insert_node(node_ptr node, const Key &key, const Value &value)
			{
				if (!node)
				{
					node = _alloc.allocate(1);
					try
					{
						_alloc.construct(node, make_pair(key, value)); 
					}
					catch(...)
					{
						_alloc.deallocate(node, 1);
						throw;
					}
					_size++;
					return (node);
				}
				else if (_keycomp(node->getFirst()) , key)
				{
					node->setrChild(insert_node(node->getrChild(), key, value));
					if (node->getrChild())
						node->getrChild()->setParent(node);
				}
				else if (_keycomp(key, node->getFirst()))
				{
					node->setlChild(insert_node(node->getlChild(), key, value));
					if (node->getlChild())
						node->getlChild()->setParent(node);
				}
				return (balance(node));
			}

			node_ptr	remove(node_ptr node, const Key &key)
			{
				if (!node)
					return (NULL);
				//if (comp(node->getFirst(), key))
				//{
				//	node->setrChild()
				//}
			}
	};
};


