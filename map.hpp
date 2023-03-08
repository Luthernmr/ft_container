#pragma once

#include <memory>
#include <stdexcept>
#include <map>
#include "pair.hpp"
#include "node.hpp"
#include "iterator/bidirectional_iterator.hpp"

using namespace ft;
namespace ft
{
	template < class Key,  class T, class Compare = std::less<Key>, class Alloc = std::allocator<Node<ft::pair<const Key, T> > > >
	class map
	{
		public:
			typedef Key 																				key_type;
        	typedef T																					mapped_type;
        	typedef ft::pair<const Key, mapped_type> 													value_type;
        	typedef Compare 																			key_compare;
        	typedef Alloc																				allocator_type; 
		//private:
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

        	typedef typename ft::bidirectional_iterator<value_type> 									iterator;
        	typedef typename ft::bidirectional_iterator<const value_type> 								const_iterator;

        	typedef typename ft::reverse_iterator<iterator> 											reverse_iterator;
        	typedef typename ft::reverse_iterator<const_iterator> 										const_reverse_iterator;
			
	
		public:
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				protected:
					key_compare	comp;
					value_compare(key_compare c) : comp(c){};
				public:
					//~value_compare();

					bool operator() (const value_type& x, const value_type& y) const
		 			{
						return comp(x.first, y.first);
					}
					
			};

		
		public:

		/* ------------------------- Constructor / Destrucor ------------------------ */

			map();
			map(const Compare& comp = std::less<Key>(), const Alloc& alloc = allocator_type()):  _keycomp(comp), _root(NULL), _size(0), _alloc(alloc){}

			template< class InputIt >
			map(InputIt first, InputIt last,const Compare& comp = std::less<Key>(), const Alloc& alloc = allocator_type()):  _keycomp(comp), _root(NULL), _size(0), _alloc(alloc){}

			map(const map& obj)
			{
				*this = obj;
			}

			~map() 
			{
				clearTree(_root);
			}

			map& operator=(const map& obj)
			{
				_keycomp = obj._keycomp;
				_root = obj._root;
				_size = obj._size;
				_alloc = obj._alloc;
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
			const mapped_type&		at(const Key& key) const {}
			mapped_type&			operator[](const Key& key) {}

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
				ft::pair<iterator, bool> pair = ft::make_pair<iterator, bool>(iterator(findKey(value.first)), tmp);
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
				//_tree.remove((*pos).first);
			}

			iterator					erase(iterator first, iterator last) 
			{
				while(first != last)
				{
					if (first->first)
						erase((first++)->first);
				}
			}

			size_type					erase(const Key& key) 
			{
				if(findKey(key))
					{
						//_tree.remove(key);
						return (1);
					}
					return(0);
			}
			void						swap(map& other) {}

		/* --------------------------------- Lookup --------------------------------- */

			size_type									count(const Key& key) const {}
			iterator									find(const Key& key) {}
			const_iterator								find(const Key& key) const {}
			ft::pair<iterator,iterator>					equal_range(const Key& key) {}
			ft::pair<const_iterator, const_iterator>	equal_range(const Key& key) const {}
			iterator									lower_bound(const Key& key) {}
			const_iterator								lower_bound(const Key& key) const {}
			iterator									upper_bound(const Key& key) {}
			const_iterator								upper_bound(const Key& key) const {}

		/* -------------------------------- Observer -------------------------------- */
			key_compare									key_comp() const {}
			value_compare								value_comp() const {}

			/* -------------------------------------------------------------------------- */
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

		/* -------------------------------- Modifier -------------------------------- */
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
				_root = insert_node(_root, &(ft::make_pair(key, val)));
				//_root->setParent(NULL);	
			}

			void	insert_help(const value_type pair)
			{
				_root = insert_node(_root, pair);
				//_root->setParent(NULL);
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
				else if (_keycomp((Key)node->getFirst()) , (Key)pair.first)
				{
					node->setrChild(insert_node(node->getrChild(), pair));
					//if (node->getrChild())
					//	node->getrChild()->setParent(node);
				}
				else if (_keycomp(pair.first, node->getFirst()))
				{
					node->setlChild(insert_node(node->getlChild(), pair));
					//if (node->getlChild())
					//	node->getlChild()->setParent(node);
				}
				updateH(node);

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

			node_ptr findKey(const Key &key)
			{
				if (!key)
					return (NULL);
				return(findKey(key, _root));
				
			}

			node_ptr findKey(const Key &key, node_ptr node)
			{
				if (!node)
					return (NULL);
				if (_keycomp(key, node->getFirst()))
					findKey(key, node->getlChild());
				else if (_keycomp(node->getFirst(), key))
					findKey(key, node->getrChild());
				return (node);
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