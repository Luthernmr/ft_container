#pragma once

#include "iterator_base.hpp"
#include "./node.hpp"
namespace ft
{
	template<class I, class Node>
	class bidirectional_iterator : public iterator<std::bidirectional_iterator_tag, I>
	{
		public:
			typedef typename bidirectional_iterator::difference_type		difference_type;
			typedef typename bidirectional_iterator::value_type				value_type;
			typedef typename bidirectional_iterator::pointer				pointer;
			typedef typename bidirectional_iterator::reference				reference;
			typedef typename bidirectional_iterator::iterator_category		iterator_category;

		private:
			//class Node;
			typedef	Node														node_type;
			typedef	iterator<std::bidirectional_iterator_tag, node_type>	node_it;
			typedef typename iterator_traits<node_it>::pointer 				node_pointer;
			node_pointer													_pointer;
			//value_type 	node;


		public:
		
		/* ------------------------- Constructor/ Destructor ------------------------ */
			bidirectional_iterator(node_pointer begin) : _pointer(begin) {}
			bidirectional_iterator() {_pointer = 0;}
			//bidirectional_iterator(const bidirectional_iterator &obj){_pointer = obj._pointer;}
			bidirectional_iterator(const iterator_traits<bidirectional_iterator<I, Node> >&obj) :_pointer(obj._pointer) {}
			bidirectional_iterator	&operator=(const bidirectional_iterator &obj)
			{
				if (this != &obj)
					this->_pointer = obj._pointer;
				return *this;
			}
			~bidirectional_iterator(){};
			operator bidirectional_iterator<const I, const Node>() const  { return (bidirectional_iterator<const I, const Node>(_pointer)); }
		/* -------------------------- Increment / Decrement ------------------------- */
			bidirectional_iterator& operator++( void ) { _pointer++; return(*this); }
			bidirectional_iterator& operator--( void ) { _pointer--; return(*this);	}
			bidirectional_iterator operator++( int )
			{
					bidirectional_iterator<I, Node> tmp(_pointer);
					_pointer++;
					return (tmp);
			}
			bidirectional_iterator operator--( int )
			{
				bidirectional_iterator<I, Node> tmp(_pointer);
				_pointer--;
				return (tmp);
			}
		
		/* ----------------------------- Dereferencement ---------------------------- */
			reference	operator*( void ) const 	{ return(_pointer->_content); }

			pointer	operator->() const				{ return(&(_pointer->_content)); }//FIXME - second et first

		/* --------------------------------- compare -------------------------------- */

		friend bool	operator==(const bidirectional_iterator<I, Node> &lhs, const bidirectional_iterator<I, Node> &rhs) 	{return (lhs._pointer == rhs._pointer);}
		friend bool	operator!=(const bidirectional_iterator<I, Node> &lhs, const bidirectional_iterator<I, Node> &rhs) 	{return (lhs._pointer != rhs._pointer);}
		friend bool	operator>(const bidirectional_iterator<I, Node> &lhs, const bidirectional_iterator<I, Node> &rhs) 	{return (lhs._pointer > rhs._pointer);}
		friend bool	operator<(const bidirectional_iterator<I, Node> &lhs, const bidirectional_iterator<I, Node> &rhs) 	{return (lhs._pointer < rhs._pointer);}
		friend bool	operator>=(const bidirectional_iterator<I, Node> &lhs, const bidirectional_iterator<I, Node> &rhs) 	{return (lhs._pointer >= rhs._pointer);}
		friend bool	operator<=(const bidirectional_iterator<I, Node> &lhs, const bidirectional_iterator<I, Node> &rhs) 	{return (lhs._pointer <= rhs._pointer);}
	};
}; // namespace ft
