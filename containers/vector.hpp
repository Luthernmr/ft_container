#pragma once

#include "../includes/utils.hpp"

/* -------------------------------------------------------------------------- */
/*                                   vector                                   */
/* -------------------------------------------------------------------------- */
namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T														value_type;
			typedef Alloc 													allocator_type;
			typedef typename allocator_type::reference 						reference;
			typedef typename allocator_type::const_reference 				const_reference;
			typedef typename allocator_type::pointer 						pointer;
			typedef typename allocator_type::const_pointer 					const_pointer;
			typedef typename allocator_type::difference_type				difference_type;
			typedef typename allocator_type::size_type						size_type;
			
			typedef typename ft::random_access_iterator<value_type> 		iterator;
			typedef typename ft::random_access_iterator<const value_type> 	const_iterator;
			typedef typename ft::reverse_iterator<iterator> 				reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator> 			const_reverse_iterator;

		private:
			pointer			_array;
			allocator_type 	_myAlloc;
			size_type 		_size;
			size_type 		_capacity;

		//template<bool Cond, class T = void> struct enable_if {};  si ca prout do this;
		//template<class T> struct enable_if<true, T> { typedef T type; };

		public:

			/* ------------------------- Constructor/Destructor ------------------------- */
			explicit vector(const allocator_type &myAlloc = allocator_type()):_array(NULL), _myAlloc(myAlloc), _size(0), _capacity(0)
			{}

			explicit vector(size_type n, const T& value = T(), const allocator_type &myAlloc = allocator_type()) : _array(NULL), _myAlloc(myAlloc), _size(0), _capacity(0)
			{
				assign(n, value);
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type &myAlloc = allocator_type()) : _array(NULL) ,_myAlloc(myAlloc), _size(0), _capacity(0) 
			{
				assign(first, last);
			}

			vector(const vector &obj) : _array(NULL), _myAlloc(obj._myAlloc), _size(0), _capacity(0)
			{
				*this = obj; 
			};

			~vector(void) {}

			vector &operator=(const vector &obj)
			{
				if (obj.capacity() > 0)
				{
					reserve(obj.capacity());
					assign(obj.begin(), obj.end());
				}
				return (*this);
			}
			/* -------------------------------- Iterator -------------------------------- */
			iterator				begin() 		{ return (iterator(_array));  }
			const_iterator			begin() const 	{ return const_iterator((_array)); }
			iterator				end()			{ return iterator(_array + _size); }
			const_iterator			end() const 	{ return const_iterator(_array + _size); }
			reverse_iterator		rbegin() 		{ return reverse_iterator(_array + _size); }
			const_reverse_iterator	rbegin() const 	{ return const_reverse_iterator(_array + _size); }
			reverse_iterator		rend() 			{ return reverse_iterator(_array); }
			const_reverse_iterator	rend() const 	{ return const_reverse_iterator(_array); }	

			/* --------------------------------- Assign --------------------------------- */
			void assign( size_type count, const_reference value )
			{
				if (count <= 0)
					return;
				if (count > _capacity)
					reserve(count);
				clear();
				for (size_type i = 0; i < count; i++)
				{
					_myAlloc.construct(_array + _size++, value);
				}
			}

			template <class InputIterator>
			void assign(typename ft::enable_if
			<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			 InputIterator last)
			{
				clear();
				for (; first != last; ++first)
				{
					push_back(*first);
				}
			}


			/* -------------------------------- Capacity -------------------------------- */
			size_type 	capacity() 	const 		{ return(_capacity); }
			size_type 	max_size() 	const 		{ return (_myAlloc.max_size()); }
			size_type	size()		const		{ return(_size); }

			void		resize(size_type count, T value = T())
			{
				if (count > _capacity)
					reserve(count);
				if (count > size())
					for (size_t i = size(); i < count; i++)
						push_back(value);
				else
					for (size_t i = size(); i > count; i--)
						pop_back();
			}

			bool 		empty()const
			{
				return (begin() == end());	
			};

			void 		reserve(size_type new_cap)
			{
				if (new_cap <= _capacity)
					return;
				pointer tmp_array = _myAlloc.allocate(new_cap);
				for (size_type i = 0; i < _size; i++)
				{
					_myAlloc.construct(tmp_array + i,  _array[i]);
					_myAlloc.destroy(_array + i);
				}
				if (_array)
					_myAlloc.deallocate(_array, _capacity);
				_array = tmp_array;
				_capacity = new_cap;
			}

			iterator	insert(iterator position, const_reference val)
			{
				if (position == end())
				{
					push_back(val);
					return (end() - 1);
				}
				size_t index = position - begin();
				if (_size == _capacity)
					reserve(_capacity ? _capacity * 2 : 1);

				_myAlloc.construct(_array + _size++, back());
				
				for (size_t i = _size - 1; i > index; i--)
					_array[i] = _array[i - 1];
				
				_myAlloc.destroy(_array + index);
				_myAlloc.construct(_array + index, val);
				
				return iterator(_array + index);
			}

			void	insert(iterator position, size_type n, const_reference val)
			{
				size_type	index = std::distance(begin(), position);
				if (_size + n > _capacity)
					reserve(_size + n);
				size_type	nb_to_move = _size - index;
				for (size_type end = _size + n - 1; nb_to_move > 0; --end)
				{
					_myAlloc.construct(&_array[end], _array[end - n]);
					nb_to_move--;
				}
				for (size_type i = 0; i < n; ++i)
				{
					_array[index] = val;
					index++;
				}
				_size += n;
			}

			template <class InputIterator>
			void		insert(iterator position, typename ft::enable_if<
			!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			InputIterator last)
			{
				size_t n = 0;
				InputIterator temp = first;
				while (temp++ != last)
					n++;
				size_t index = position - begin();
				if (_size + n > _capacity)
					reserve(_size + n);
				for (size_t i = _size + n - 1; i >= index + n; i--)
					_array[i] = _array[i - n];
				for (size_t i = index; i < index + n; i++)
				{
					_myAlloc.destroy(_array + i);
					_myAlloc.construct(_array + i, *first++);
				}
				_size += n;
			}

			/* ------------------------------ Element Acces ----------------------------- */	
			reference at(size_type pos)
			{
				if (pos >= _size)
					throw (std::out_of_range("vector"));
				return (_array[pos]);
			}
			const_reference at(size_type pos) const
			{
				if (pos >= _size)
					throw (std::out_of_range("vector"));
				return (_array[pos]);
			}
			reference 		operator[](size_type pos) 		{ return (_array[pos]); }
			const_reference	operator[](size_type pos) const { return (_array[pos]); }
			reference		front(void) 					{ return (_array[0]); }
			const_reference	front(void) const 				{ return (_array[0]); }
			reference 		back(void) 						{ return (_array[_size - 1]); }
			const_reference	back(void) const 				{ return (_array[_size - 1]); }
			T 				*data(void) 					{ return (_array); }
			const T 		*data(void) const				{ return (_array); }

			/* -------------------------------- Modifier -------------------------------- */
			void					clear()
			{
				for (size_type i = 0; i < _size; i++)
					_myAlloc.destroy(_array + i);
				_size = 0;
			}
			void					push_back(const_reference value)
			{
				if (_size == _capacity)
				{
					if (_capacity)
						reserve(_capacity * 2);
					else
						reserve(1);
				}
				_myAlloc.construct((_array + _size++), value);
			}
			void					pop_back()
			{
				if (_size != 0)
					_myAlloc.destroy((_array + _size--) - 1);
			}

			iterator				erase(iterator position)
			{
				for (iterator it = position; it != _array + _size - 1; it++)
				{
					_myAlloc.destroy(&(*it));
					_myAlloc.construct(&(*it), *(it + 1));
				}
				_size--;
				return (position);
			}
			iterator				erase(iterator first, iterator last)
			{
				size_type range = last - first;
				for (iterator it = first; it != _array + _size - range; it++)
				{
					_myAlloc.destroy(&(*it));
					_myAlloc.construct(&(*it), *(it + (int)range));
				}
				for (iterator it = _array + _size - range; it != _array + _size; it++)
					_myAlloc.destroy(&(*it));
				_size -= range;
				return (first);
			}

			void					swap(vector& x)
			{
				value_type*		tmpData = x._array;
				size_type		tmpCapacity = x._capacity;
				size_type		tmpSize = x._size;
				allocator_type	tmpAlloc = x._myAlloc;

				x._array = _array;
				x._capacity = _capacity;
				x._size = _size;
				x._myAlloc = _myAlloc;

				_array = tmpData;
				_capacity = tmpCapacity;
				_size = tmpSize;
				_myAlloc = tmpAlloc;
			}
			/* -------------------------------- Allocator ------------------------------- */
	};
		/* ---------------------- Non-member function overloads --------------------- */
		template< class T, class Alloc >
		bool operator==(const ft::vector<T, Alloc>& lhs,
						const ft::vector<T, Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			for (typename ft::vector<T, Alloc>::size_type i = 0; i < lhs.size(); i++)
			{
				if (lhs[i] != rhs[i])
					return (false);
			}
			return (true);
		}

		template< class T, class Alloc >
		bool operator!=(const ft::vector<T, Alloc>& lhs,
						const ft::vector<T, Alloc>& rhs)
		{ return (!(lhs == rhs)); }

		template< class T, class Alloc >
		bool operator<(const ft::vector<T, Alloc>& lhs,
						const ft::vector<T, Alloc>& rhs )
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
			rhs.begin(), rhs.end()));
		}
		
		template< class T, class Alloc >
		bool operator<=(const ft::vector<T, Alloc>& lhs,
						const ft::vector<T, Alloc>& rhs )
		{ return (!(rhs < lhs)); }

		template< class T, class Alloc >
		bool operator>(const ft::vector<T, Alloc>& lhs,
						const ft::vector<T, Alloc>& rhs )
		{ return (rhs < lhs); }

		template< class T, class Alloc >
		bool operator>=(const ft::vector<T, Alloc>& lhs,
						const ft::vector<T, Alloc>& rhs )
		{ return (!(lhs < rhs)); }
}