#pragma once

#include <memory>

namespace ft
{
	template < class Key,  class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T>>> 
	class map
	{
		
		public:
			typedef Key 																				key_type;
        	typedef T																					mapped_type;
        	typedef ft::pair<const key_type, mapped_type> 												value_type;
        	typedef Compare 																			key_compare;
        	typedef Alloc 																				allocator_type; 
        	typedef typename allocator_type::reference 													reference;
        	typedef typename allocator_type::const_reference 											const_reference;
        	typedef typename allocator_type::pointer 													pointer;
        	typedef typename allocator_type::const_pointer 												const_pointer;
        	typedef typename allocator_type::size_type 													size_type;
        	typedef typename allocator_type::difference_type 											difference_type;
        	//typedef typename ft::tree<value_type, allocator_type, key_compare>::iterator 				iterator;
        	//typedef typename ft::tree<value_type, allocator_type, key_compare>::reverse_iterator 		reverse_iterator;
        	//typedef typename ft::tree<value_type, allocator_type, key_compare>::const_iterator 			const_iterator;
	    	//typedef typename ft::tree<value_type, allocator_type, key_compare>::const_reverse_iterator 	const_reverse_iterator;
			
	
		public:
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend
				protected:
					key_compare	comp;
					value_compare(key_compare c) : comp(c){};
				public:
					~value_compare();

					bool operator() (const value_type& x, const value_type& y) const
		 			{
						return comp(x.first, y.first);
					}
					
			};

		private:
			value_type*		_tree;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_myAlloc;
		
		public:

		/* ------------------------- Constructor / Destrucor ------------------------ */
			map(): _tree(NULL) {}

			explicit map(const Compare& comp,
						const Allocator& alloc = Allocator()): _tree(NULL) {}

			template< class InputIt >
			map(InputIt first, InputIt last, const Compare& comp = Compare(),
				const Allocator& alloc = Allocator()): _tree(NULL) {}

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

			iterator				begin() {return iterator(_tree.begin());}
			const_iterator			begin() const {return iterator(_tree.begin());}
			iterator				end() {return iterator(_tree.end());}
			const_iterator			end() const {return iterator(_tree.end());}
			reverse_iterator		rbegin() {return reverse_iterator(_tree.rbegin());}
			const_reverse_iterator	rbegin() const {return const_reverse_iterator(_tree.rbegin());}
			reverse_iterator		rend() {return reverse_iterator(_tree.rend());}
			const_reverse_iterator	rend() const {return const_reverse_iterator(_tree.rend());}

		/* -------------------------------- Capacity -------------------------------- */

			bool					empty() const {return (begin() == end());}
			size_type				size() const {return (_size);}
			size_type				max_size() const {return (_capacity);}

		/* -------------------------------- Modifier -------------------------------- */

			void					clear() {}
			pair<iterator, bool>	insert(const value_type& value) {}
			iterator				insert(iterator pos, const value_type& value) {}
			template<class InputIt>
			void 					insert(InputIt first, InputIt last) {}
			iterator				erase(iterator pos) {}
			iterator				erase(iterator first, iterator last) {}
			size_type				erase(const Key& key) {}
			void					swap(map& other) {}

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
			ft::map::value_compare						value_comp() const {}
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