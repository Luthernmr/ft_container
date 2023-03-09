#pragma once

#include <memory>
#include <stdexcept>
#include <map>
#include "pair.hpp"
#include "node.hpp"
#include "iterator/reverse_iterator.hpp"
#include "iterator/bidirectional_iterator.hpp"
#include "iterator/lexicographical_compare.hpp"

using namespace ft;
namespace ft
{
	template < class Key,  class T, class Compare = std::less<Key>, class Alloc = std::allocator<Node<ft::pair<const Key, T> > > >
	class map
	{
		public:
			typedef Key 																				key_type;
        	typedef T																					mapped_type;
        	typedef ft::pair<const key_type, mapped_type> 												value_type;
        	typedef Compare 																			key_compare;
        	typedef Alloc																				allocator_type; 
		private:
			typedef	ft::Node<value_type>																node_type;
			typedef	ft::Node<value_type>*																node_ptr;
			key_compare																					_keycomp;
			node_ptr 																					_root;
			size_t																						_size;
			allocator_type																				_alloc;


		public:
        	typedef typename allocator_type::reference 													reference;
        	typedef typename allocator_type::const_reference 											const_reference;
        	typedef typename allocator_type::pointer 													pointer;
        	typedef typename allocator_type::const_pointer 												const_pointer;
        	typedef typename allocator_type::size_type 													size_type;
        	typedef typename allocator_type::difference_type 											difference_type;

        	typedef typename ft::bidirectional_iterator<value_type, node_type> 							iterator;
        	typedef typename ft::bidirectional_iterator<const value_type,const node_type> 				const_iterator;

        	typedef typename ft::reverse_iterator<iterator> 											reverse_iterator;
        	typedef typename ft::reverse_iterator<const_iterator> 										const_reverse_iterator;
			
	
		public:
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
					Compare	comp;
					value_compare(Compare c) : comp(c){};
				public:
					//~value_compare();

					bool operator() (const value_type& x, const value_type& y) const
		 			{
						return comp(x.first, y.first);
					}
					
			};
			value_compare																				_valuecomp;

		
		public:

		/* ------------------------- Constructor / Destrucor ------------------------ */

			//map();
			map(const Compare& comp = key_compare(), const Alloc& alloc = allocator_type()):  _keycomp(comp), _root(NULL), _size(0), _alloc(alloc), _valuecomp(comp){}

			template< class InputIt >
			map(InputIt first, InputIt last,const Compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):  _keycomp(comp), _root(NULL), _size(0), _alloc(alloc), _valuecomp(comp) {insert(first,last);}

			map(const map& obj) : _keycomp(obj._keycomp), _root(obj._root), _size(obj._size), _alloc(obj._alloc), _valuecomp(obj._valuecomp) 
			{
				const_iterator it = obj.begin();
				while (it != obj.end())
					insert(*it++);
			}

			~map() {clearTree(_root);}

			map& operator=(const map& obj)
			{
				_keycomp = obj._keycomp;
				_root = obj._root;
				_size = obj._size;
				_alloc = obj._alloc;
				_valuecomp = obj._valuecomp;
				return *this;
			}
		
			allocator_type get_allocator() const
			{
				return (_alloc);
			}
		/* ---------------------------------- Acces --------------------------------- */

			mapped_type&			at(const Key& key) 
			{
				node_ptr node = findKey(key);
				if (!node)
					throw (std::out_of_range("out_of_range"));
				return(node->getSecond());
			}
			const mapped_type&		at(const Key& key) const 
			{
				node_ptr node = findKey(key);
				if (!node)
					throw (std::out_of_range("out_of_range"));
				return(node->_content.second);
			}
			T&			operator[](const Key& key)
			{
				node_ptr node = findKey(key);
				if (!node)
				{
					insert(value_type(key, mapped_type()));
					node = findKey(key);
				}
				return (node->_content.second);
			}

		

		/* -------------------------------- Iterators ------------------------------- */

			iterator				begin()			 	{return iterator(minValue(_root));}
			const_iterator			begin() const		{return iterator(minValue(_root));}
			iterator				end() 				{return iterator(maxValue(_root));}
			const_iterator			end() const 		{return iterator(maxValue(_root));}
			reverse_iterator		rbegin() 			{return reverse_iterator(maxValue(_root));}
			const_reverse_iterator	rbegin() const 		{return const_reverse_iterator(maxValue(_root));}
			reverse_iterator		rend() 				{return reverse_iterator(minValue(_root));}
			const_reverse_iterator	rend() const 		{return const_reverse_iterator(minValue(_root));}

		/* -------------------------------- Capacity -------------------------------- */

			bool					empty() const 		{return (begin() == end());}
			size_type				size() const 		{return (_size);}
			size_type				max_size() const 	{return ( _alloc.max_size());}

		/* -------------------------------- Modifier -------------------------------- */

			void					clear() 
			{
				clearTree(_root);
			}

			ft::pair<iterator, bool>	insert(const value_type& value) // The pair::second element (bool) in the pair is set to true if a new element was inserted or false if an equivalent element already existed.
			{
				bool tmp = false;
				iterator it = findKey(value.first);
				if (it == NULL)
					tmp = true;
				insert_help(value);
				ft::pair<iterator, bool> pair = ft::make_pair(iterator(findKey(value.first)), tmp);
				return(pair);
			}

			iterator					insert(iterator pos, const value_type& value) 
			{
					(void)	pos;
					insert_help(value);
					return(findKey(value.first));
			}

			template<class InputIt>	
			void 						insert(InputIt first, InputIt last) 
			{
				while (first != last)
					{
						insert_help(*first);
						first++;
					}
			}

			iterator					erase(iterator pos) 
			{
				iterator tmp = pos;
				deleteNode(_root,(*pos).first);
				return (pos);
			}

			iterator					erase(iterator first, iterator last) 
			{
				while(first != last)
				{
					if (first->first)
					{
						iterator tmp = first;
						erase((first++)->first);
						return (tmp);
					}
				}
				return (NULL);
			}

			size_type					erase(const Key &key) 
			{
				if(findKey(key))
					{
						deleteNode(_root, key);
						return (1);
					}
					return(0);
			}


			void						swap(map& other)
			{
					node_ptr 		root = other._root;
					size_type 		size = other._size;
					key_compare		keycomp = other._keycomp;
					allocator_type	alloc = other._alloc;
					value_compare	valuecomp = other._valuecomp;
					other._size = size;
					other._root = root;
					other._keycomp = keycomp;
					other._alloc = alloc;
					other._valuecomp = valuecomp;

					_size = size;
					_root = root;
					_keycomp = keycomp;
					_alloc = alloc;
					_valuecomp = valuecomp;
			}

		/* --------------------------------- Lookup --------------------------------- */

			size_type									count(const Key& key) const
			{
				node_ptr tmp = findKey(key);
				if (tmp)
						return((size_type) 1);
				return((size_type) 0);
			}
			iterator									find(const Key& key) 			{return (iterator(findKey(key)));}
			const_iterator								find(const Key& key) const 	
			{	
				node_ptr tmp = findKey(key);
				return (const_iterator(tmp));
			}
			ft::pair<iterator,iterator>					equal_range(const Key& key) 
			{
				return(ft::make_pair<iterator, iterator>(lower_bound(key),upper_bound(key)));
			}
			ft::pair<const_iterator, const_iterator>	equal_range(const Key& key) const
			{
				return(ft::make_pair<const_iterator, const_iterator>(lower_bound(key),upper_bound(key)));			
			}
			iterator									lower_bound(const Key& key)
			{
				iterator it = begin();
				while (it != end())
				{
					if (_keycomp(it->first, key))
						it++;
					else
						return(it);
				}
				return( it );
			}
			const_iterator								lower_bound(const Key& key) const
			{
				const_iterator it = begin();
				while (it != end())
				{
					if (_keycomp(it->first, key))
						it++;
					else
						return(it);
				}
				return( it );
			}
			iterator									upper_bound(const Key& key) 
			{
				iterator it = begin();
				while (it != end())
				{
					if (_keycomp(it->first, key) || key == it->first)
						it++;
					else
						return(it);
				}
				return( it );
			}
			const_iterator								upper_bound(const Key& key) const 
			{
				const_iterator it = begin();
				while (it != end())
				{
					if (_keycomp(it->first, key) || key == it->first)
						it++;
					else
						return(it);
				}
				return( it );
			}

		/* -------------------------------- Observer -------------------------------- */
			key_compare									key_comp() const {return (key_compare());}
			value_compare 								value_comp() const {return value_compare(key_compare());}

			/* -----------------------------------tree----------------------------------- */
			/*                                    tree                                    */
			/* -------------------------------------------------------------------------- */

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
				int lh;
				int rh;
				if (!node->_lChild)
					lh = 0;
				else
					lh = node->_lChild->_height;
				if (!node->_rChild)
					rh = 0;
				else
					rh = node->_rChild->_height;
				return (lh - rh);
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

			void clearTree(const node_ptr &root)
			{
				_size = 0;
 		  		if(root != NULL)
  		 		{
		 			clearTree(root->getrChild());
		 			clearTree(root->getlChild());
					_alloc.destroy(root);
					_alloc.deallocate(root, 1);
   				}
			}

			void	insert_help(const Key& key, const mapped_type& val)
			{	
				_root = insert_node(_root, (ft::make_pair(key, val)));
				_root->setParent(NULL);	
			}

			void	insert_help(const value_type pair)
			{
				_root = insert_node(_root, pair);
				_root->setParent(NULL);
			}

			node_ptr insert_node(node_ptr node, value_type pair)
			{
				if (!node)
				{	
					node = _alloc.allocate(1);
					try
					{
						_alloc.construct(node, Node<value_type>(pair)); 
					}
					catch(...)
					{
						_alloc.deallocate(node, 1);
						throw;
					}
					_size++;
					return (node);
				}
				else if (_keycomp(node->getFirst(), pair.first))
				{
					node->setrChild(insert_node(node->getrChild(), pair));
					if (node->getrChild())
						node->getrChild()->setParent(node);
				}
				else if (_keycomp(pair.first, node->getFirst()))
				{
					node->setlChild(insert_node(node->getlChild(), pair));
					if (node->getlChild())
						node->getlChild()->setParent(node);
				}
				updateH(node);

				return (balance(node));
			}

			node_ptr findKey(const Key &key) const
			{
				return(findKey(key, _root));
				
			}

			node_ptr findKey(const Key &key, node_ptr node) const
			{
				if (!node)
					return (NULL);
				if (_keycomp(key, node->getFirst()))
					return(findKey(key, node->getlChild()));
				else if (_keycomp(node->getFirst(), key))
					return (findKey(key, node->getrChild()));
				return (node);
			}

			node_ptr deleteNode(node_ptr root, const Key &key)
			{
				if (!root)
					return (root);
				if (_keycomp(key, root->getFirst()))
					root->setlChild(deleteNode(root->getlChild(), key));
				else if (_keycomp(root->getFirst(), key))
					root->setrChild(deleteNode(root->getrChild(), key));

				else
   				{
   				    // node with only one child or no child
   				    if ( (root->getlChild() == NULL) || (root->getrChild() == NULL) )
   				    {
   				        node_ptr temp = root->getlChild() ? root->getlChild() : root->getrChild(); // condition ? value_if_condition_true : value_if_condition_false 
			
   				        // No child case
   				        if (temp == NULL)
   				        {
   				            temp = root;
   				            root = NULL;
   				        }
   				        else // One child case
   				       	root = temp; // Copy the contents of
   				                       // the non-empty child
   						_alloc.destroy(temp);
						_alloc.deallocate(temp,1);
						_size--;
   				    }
   				    else
   				    {
   				        // node with two children: Get the inorder
   				        // successor (smallest in the right subtree)
   				       node_ptr temp = minValue(root->getrChild());
			
   				        // Copy the inorder successor's
   				        // data to this node
						temp->setrChild(root->getrChild());
						temp->setlChild(root->getlChild());
   				        //root->_content = ft::make_pair<const Key, mapped_type>((Key)temp->_content.first, root->_content.second);
			
   				        // Delete the inorder successor
   				        root->setrChild(deleteNode(root->getrChild(), temp->getFirst()));
   				    }
   				}
   				if (root == NULL)
   					return root;
			
				updateH(root);
   				return (balance(root));
			}
	};
	/* -------------------------------- Operator -------------------------------- */
		template<class Key, class T, class Compare, class Alloc>
		bool operator==(const map<Key, T, Compare, Alloc>& lhs,
						const map<Key, T, Compare, Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			return (equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

		template<class Key, class T, class Compare, class Alloc>
		bool operator!=(const map<Key, T, Compare, Alloc>& lhs,
						const map<Key, T, Compare, Alloc>& rhs)
		{
			return (!(lhs == rhs));
		}

		template<class Key, class T, class Compare, class Alloc>
		bool operator<(const map<Key, T, Compare, Alloc>& lhs,
						const map<Key, T, Compare, Alloc>& rhs)
		{
			return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

		template<class Key, class T, class Compare, class Alloc>
		bool operator<=(const map<Key, T, Compare, Alloc>& lhs,
						const map<Key, T, Compare, Alloc>& rhs)
		{
			return (!(rhs < lhs));
		}

		template<class Key, class T, class Compare, class Alloc>
		bool operator>(const map<Key, T, Compare, Alloc>& lhs,
						const map<Key, T, Compare, Alloc>& rhs)
		{
			return (rhs < lhs);
		}
		template<class Key, class T, class Compare, class Alloc>
		bool operator>=(const map<Key, T, Compare, Alloc>& lhs,
						const map<Key, T, Compare, Alloc>& rhs)
		{
			return (!(lhs < rhs));
		}
};