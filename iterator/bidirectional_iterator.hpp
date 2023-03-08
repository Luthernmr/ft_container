#pragma once

#include "iterator_base.hpp"
#include "./node.hpp"
namespace ft
{
using namespace ft;
	template<class I>
	class bidirectional_iterator : public ft::iterator<std::bidirectional_iterator_tag, I>
	{
		public:
			typedef typename ft::iterator<std::bidirectional_iterator_tag, I>::difference_type		difference_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, I>::value_type			value_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, I>::pointer				pointer;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, I>::reference			reference;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, I>::iterator_category	iterator_category;

		private:
			//class Node;
			typedef	ft::Node<value_type>*	node_ptr;
			typedef	ft::Node<value_type>	node_type;
			node_ptr						_pointer;
			//value_type 	node;


		public:
		
		/* ------------------------- Constructor/ Destructor ------------------------ */
			//bidirectional_iterator() : _pointer(NULL) {}
			bidirectional_iterator(node_ptr begin) : _pointer(begin) {}
			bidirectional_iterator() {_pointer = 0;}
			bidirectional_iterator(const bidirectional_iterator &obj){_pointer = obj._pointer;}
			bidirectional_iterator(const ft::iterator_traits<bidirectional_iterator<value_type> > &obj){_pointer = obj._pointer;}
			bidirectional_iterator	&operator=(const bidirectional_iterator &obj)
			{
				if (this != &obj)
					this->_pointer = obj._pointer;
				return *this;
			}
			//~bidirectional_iterator(){};
		/* -------------------------- Increment / Decrement ------------------------- */
			bidirectional_iterator& operator++( void ) { _pointer++; return(*this); }
			bidirectional_iterator& operator--( void ) { _pointer--; return(*this);	}
			bidirectional_iterator operator++( int )
			{
					bidirectional_iterator<value_type> tmp(_pointer);
					_pointer++;
					return (tmp);
			}
			bidirectional_iterator operator--( int )
			{
				bidirectional_iterator<value_type> tmp(_pointer);
				_pointer--;
				return (tmp);
			}
		
		/* ----------------------------- Dereferencement ---------------------------- */
			reference	operator*( void ) 	{ return(_pointer->_content); }
			pointer		operator->( void ) 	
			{ 
				//if (!_pointer)
				//	return (&_end);
				return(&(_pointer->_content));
			}//FIXME - second et first

		/* --------------------------------- compare -------------------------------- */

		friend bool	operator==(const bidirectional_iterator<value_type> &lhs, const bidirectional_iterator<value_type> &rhs) 	{return (lhs._pointer == rhs._pointer);}
		friend bool	operator!=(const bidirectional_iterator<value_type> &lhs, const bidirectional_iterator<value_type> &rhs) 	{return (lhs._pointer != rhs._pointer);}
		friend bool	operator>(const bidirectional_iterator<value_type> &lhs, const bidirectional_iterator<value_type> &rhs) 	{return (lhs._pointer > rhs._pointer);}
		friend bool	operator<(const bidirectional_iterator<value_type> &lhs, const bidirectional_iterator<value_type> &rhs) 	{return (lhs._pointer < rhs._pointer);}
		friend bool	operator>=(const bidirectional_iterator<value_type> &lhs, const bidirectional_iterator<value_type> &rhs) 	{return (lhs._pointer >= rhs._pointer);}
		friend bool	operator<=(const bidirectional_iterator<value_type> &lhs, const bidirectional_iterator<value_type> &rhs) 	{return (lhs._pointer <= rhs._pointer);}
	};
}; // namespace ft
