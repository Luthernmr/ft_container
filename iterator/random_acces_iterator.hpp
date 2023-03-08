#pragma once

#include "iterator_base.hpp"

using namespace ft;
namespace ft
{

	template<class I>
	class random_access_iterator : public iterator<std::random_access_iterator_tag, I>
	{
		public: 
			typedef typename ft::iterator<std::random_access_iterator_tag, I>::difference_type		difference_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, I>::value_type			value_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, I>::pointer				pointer;
			typedef typename ft::iterator<std::random_access_iterator_tag, I>::reference			reference;
			typedef typename ft::iterator<std::random_access_iterator_tag, I>::iterator_category	iterator_category;
		
		private:
			pointer	_pointer;
		public:
		/* -------------------------------------------------------------------------- */
		/*                           Constructor/Destructor                           */
		/* -------------------------------------------------------------------------- */
			random_access_iterator(pointer begin) : _pointer(begin) {}
			random_access_iterator() {_pointer = 0;}
			random_access_iterator(const random_access_iterator &obj){_pointer = obj._pointer;}
			random_access_iterator(const iterator_traits<random_access_iterator<value_type> > &obj){_pointer = obj._pointer;}
			random_access_iterator	&operator=(const random_access_iterator &obj)
			{
				if (this != &obj)
					this->_pointer = obj._pointer;
				return *this;
			}
			~random_access_iterator(){};

			operator random_access_iterator<const I> () const  { return (random_access_iterator<const I>(this->_pointer)); }
		
		/* -------------------------- Increment/ Decrement -------------------------- */
			random_access_iterator& operator++( void ) { _pointer++; return(*this); }
			random_access_iterator& operator--( void ) { _pointer--; return(*this);	}
			random_access_iterator operator++( int )
			{
					random_access_iterator<value_type> tmp(_pointer);
					_pointer++;
					return (tmp);
			}
			random_access_iterator operator--( int )
			{
				random_access_iterator<value_type> tmp(_pointer);
				_pointer--;
				return (tmp);
			}

		/* --------------------------------- Compare -------------------------------- */
		friend bool	operator==(const random_access_iterator<I> &lhs, const random_access_iterator<I> &rhs) 	{return (lhs._pointer == rhs._pointer);}
		friend bool	operator!=(const random_access_iterator<I> &lhs, const random_access_iterator<I> &rhs) 	{return (lhs._pointer != rhs._pointer);}
		friend bool	operator>(const random_access_iterator<I> &lhs, const random_access_iterator<I> &rhs) 	{return (lhs._pointer > rhs._pointer);}
		friend bool	operator<(const random_access_iterator<I> &lhs, const random_access_iterator<I> &rhs) 	{return (lhs._pointer < rhs._pointer);}
		friend bool	operator>=(const random_access_iterator<I> &lhs, const random_access_iterator<I> &rhs) 	{return (lhs._pointer >= rhs._pointer);}
		friend bool	operator<=(const random_access_iterator<I> &lhs, const random_access_iterator<I> &rhs) 	{return (lhs._pointer <= rhs._pointer);}

		/* -------------------------------- Operation ------------------------------- */
		random_access_iterator& operator+=(	difference_type n ) { _pointer += n;	return(*this); }
		random_access_iterator& operator-=(	difference_type n ) { _pointer -= n;	return(*this); }

		random_access_iterator	operator+( difference_type n ) const
		{
			random_access_iterator tmp = *this;
			tmp += n;
			return(tmp);
		}

		random_access_iterator	operator-( difference_type n ) const 
		{	
			random_access_iterator tmp = *this;
			tmp -= n;
			return(tmp);
		}

		friend random_access_iterator	operator-( difference_type n ,random_access_iterator &rhs)
		{ random_access_iterator tmp = rhs; tmp -= n; return tmp;	}

		friend random_access_iterator	operator-( random_access_iterator &rhs, difference_type n )
		{ random_access_iterator tmp = rhs; tmp -= n; return tmp;	}

		friend random_access_iterator	operator+( difference_type n , random_access_iterator &rhs)
		{ random_access_iterator tmp =rhs; tmp += n; return tmp; }

		friend random_access_iterator	operator+( random_access_iterator &rhs, difference_type n)
		{ random_access_iterator tmp =rhs; tmp += n; return tmp; }
		
		friend difference_type	operator-(const random_access_iterator<I> &lhs, const random_access_iterator<I> &rhs) { return (lhs._pointer - rhs._pointer); }
		friend difference_type	operator+(const random_access_iterator<I> &lhs, const random_access_iterator<I> &rhs) { return (lhs._pointer + rhs._pointer); }

		/* ---------------------------------- Acces --------------------------------- */
		reference	operator[](	difference_type n ) { return(*(_pointer + n)); }
		reference	operator*( void ) { return(*_pointer); }
		pointer		operator->( void ) { return(_pointer); }

	};
	
};