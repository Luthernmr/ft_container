#pragma once

#include <memory>
#include <stdexcept>
#include <map>
#include "pair.hpp"
#include "node.hpp"
#include "iterator/bidirectional_iterator.hpp"
#include "avl_tree.hpp"

namespace ft
{
	template < class Key,  class T, class Compare = std::less<Key>, class Alloc = std::allocator< std::pair<const Key, T> > > 
	class map
	{
		class Node;
		class Tree;
		public:
			typedef Key 																				key_type;
        	typedef T																					mapped_type;
        	typedef ft::pair<const Key, mapped_type> 													value_type;
        	typedef Compare 																			key_compare;
        	typedef Alloc																				allocator_type; 

		private:
			typedef	ft::Node<value_type>																node_type;
			typedef	ft::Node<value_type>*																node_ptr;
			typedef ft::Tree<node_type, key_compare , allocator_type>									tree_type;

		public:
        	typedef typename allocator_type::reference 													reference;
        	typedef typename allocator_type::const_reference 											const_reference;
        	typedef typename allocator_type::pointer 													pointer;
        	typedef typename allocator_type::const_pointer 												const_pointer;
        	typedef typename allocator_type::size_type 													size_type;
        	typedef typename allocator_type::difference_type 											difference_type;

        	typedef typename ft::bidirectional_iterator<node_type> 										iterator;
        	typedef typename ft::bidirectional_iterator<const node_type> 								const_iterator;

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

		private:
			tree_type*		_tree;
			allocator_type	_myAlloc;
		
		public:

		/* ------------------------- Constructor / Destrucor ------------------------ */
			map(): _tree(NULL) {}

			explicit map(const Compare& comp,
						const Alloc& alloc = Alloc()): _tree(NULL) {}

			template< class InputIt >
			map(InputIt first, InputIt last, const Compare& comp = Compare(),
				const Alloc& alloc = Alloc()): _tree(NULL) {}

			map(const map& obj): _tree(NULL)
			{
				*this = obj;
			}

			~map() {}

			map& operator=(const map& obj)
			{
				_tree = obj._tree;
				return *this;
			}
		
			allocator_type get_allocator() const
			{
				return (_myAlloc);
			}
		/* ---------------------------------- Acces --------------------------------- */

			mapped_type&			at(const Key& key) {}
			const mapped_type&		at(const Key& key) const {}
			mapped_type&			operator[](const Key& key) {}

		/* -------------------------------- Iterators ------------------------------- */

			iterator				begin()			 	{return iterator(_tree->minValue(_tree->_root));}
			const_iterator			begin() const		{return iterator(_tree->minValue(_tree->_root));}
			iterator				end() 				{return iterator(_tree->maxValue(_tree->_root));}
			const_iterator			end() const 		{return iterator(_tree->maxValue(_tree->_root));}
			reverse_iterator		rbegin() 			{return reverse_iterator(_tree->maxValue(_tree->_root));}
			const_reverse_iterator	rbegin() const 		{return const_reverse_iterator(_tree->maxValue(_tree->_root));}
			reverse_iterator		rend() 				{return reverse_iterator(_tree->minValue(_tree->_root));}
			const_reverse_iterator	rend() const 		{return const_reverse_iterator(_tree->minValue(_tree->_root));}

		/* -------------------------------- Capacity -------------------------------- */

			bool					empty() const 		{return (begin() == end());}
			size_type				size() const 		{return (_tree->size());}
			size_type				max_size() const 	{return (_myAlloc.max_size());}

		/* -------------------------------- Modifier -------------------------------- */

			void					clear() 
			{
				_tree->deleteAll(_tree->_root);
				_tree->_root = NULL;
			}

			ft::pair<iterator, bool>	insert(const value_type& value) // The pair::second element (bool) in the pair is set to true if a new element was inserted or false if an equivalent element already existed.
			{
				bool tmp = false;
				iterator it = _tree.search(value.first);
				if (!it)
					tmp = true;
				_tree->insert(value);
				return(ft::make_pair<iterator, bool>(iterator(_tree.search(value.first)), tmp));
			}

			iterator					insert(iterator pos, const value_type& value) 
			{
					(void)	pos;
					insert(value);
					return(_tree.search(value.first));
			}

			template<class InputIt>	
			void 						insert(InputIt first, InputIt last) 
			{
				while (first != last)
					{
						insert(*first);
						first++;
					}
			}

			iterator					erase(iterator pos) 
			{
				_tree.remove((*pos).first);
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
				if(_tree.search(key))
					{
						_tree.remove(key);
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