#pragma once

#include <memory>
#include "iterator_base.hpp"
#include "iterator_traits.hpp"
#include <iostream>

using namespace ft;
namespace ft
{
	template< class Iter >
	class reverse_iterator
	{
		public:
			typedef	Iter													iterator_type;
			typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iter>::value_type			value_type;
			typedef typename iterator_traits<Iter>::difference_type		difference_type;
			typedef typename iterator_traits<Iter>::pointer				pointer;
			typedef typename iterator_traits<Iter>::reference			reference;
		
		protected:
			iterator_type	current;

		public:
			/* ------------------------ Constructor / Destructor ------------------------ */
			reverse_iterator(void) {};
			reverse_iterator (iterator_type it) : current(it){};
			reverse_iterator(const reverse_iterator& obj) : current(obj.current){};

			template <class U>
			reverse_iterator(const reverse_iterator<U>& obj) : current(obj.base()){};
			
			reverse_iterator&	operator=(const reverse_iterator<Iter>& obj)
			{
				current = obj.base();
				return (*this);
			}

			~reverse_iterator(void){};

			/* --------------------------- getCurrentIt (base) -------------------------- */
			Iter base(void) const {return(current);};

			/* --------------------------------- Access --------------------------------- */


			reference	operator*( void ) const 		{ iterator_type tmp = current; return(*--tmp); }
			reference	operator*( void ) 				{ iterator_type tmp = current; return(*--tmp); }
			pointer 	operator->() const				{ return &(operator*()); }
			pointer 	operator->()					{ return &(operator*()); }
			reference	operator[](	difference_type n ) { return(base()[-n -1]); }

			/* ---------------------------- Increment reverse --------------------------- */
			reverse_iterator&	operator++() { current--; return (*this); };
			reverse_iterator	operator++(int)
			{
				reverse_iterator tmp(*this);
				--current;
				return (tmp);
			};
			reverse_iterator&	operator+=(difference_type n)
			{
				current -= n;
				return (*this);
			}
			reverse_iterator	operator+(difference_type n) const {return (current - n);};
			friend reverse_iterator operator+(difference_type n, const reverse_iterator rhs)
			{
				return (rhs + n);
			}
			
			/* ---------------------------- Derement reverse ---------------------------- */
			reverse_iterator&	operator--() {current++; return (*this);}
			reverse_iterator	operator--(int)
			{
				reverse_iterator tmp(*this);
				++current;
				return (tmp);
			}
			reverse_iterator&	operator-=(difference_type n)
			{
				current += n;
				return (*this);
			}
			reverse_iterator	operator-(difference_type n) const {return (current + n);};
	
	
	};
	/* -------------------------------------------------------------------------- */
	/*                             Non Member Function                            */
	/* -------------------------------------------------------------------------- */

		/* --------------------------------- Compare -------------------------------- */

		template<class Iter>
		bool operator==(const reverse_iterator<Iter>& lhs,
						const reverse_iterator<Iter>& rhs)
		{return (lhs.base() == rhs.base());}

		template<class Iterator1, class Iterator2>
		bool operator==(const ft::reverse_iterator<Iterator1>& lhs,
						const ft::reverse_iterator<Iterator2>& rhs)
		{return (lhs.base() == rhs.base());}
		
		template<class Iter>
		bool operator!=(const ft::reverse_iterator<Iter>& lhs,
						const ft::reverse_iterator<Iter>& rhs)
		{return (lhs.base() != rhs.base());}

		template<class Iterator1, class Iterator2>
		bool operator!=(const ft::reverse_iterator<Iterator1>& lhs,
						const ft::reverse_iterator<Iterator2>& rhs)
		{return (lhs.base() != rhs.base());}
		
		template<class Iter>
		bool operator<(const ft::reverse_iterator<Iter>& lhs,
						const ft::reverse_iterator<Iter>& rhs)
		{return (lhs.base() > rhs.base());}

		template<class Iterator1, class Iterator2>
		bool operator<(const ft::reverse_iterator<Iterator1>& lhs,
					   const ft::reverse_iterator<Iterator2>& rhs)
		{return (lhs.base() > rhs.base());}
		
		template<class Iter>
		bool operator<=(const ft::reverse_iterator<Iter>& lhs,
						const ft::reverse_iterator<Iter>& rhs)
		{return (lhs.base() >= rhs.base());}

		template<class Iterator1, class Iterator2>
		bool operator<=(const ft::reverse_iterator<Iterator1>& lhs,
						const ft::reverse_iterator<Iterator2>& rhs)
		{return (lhs.base() >= rhs.base());}
		
		template<class Iter>
		bool operator>(const ft::reverse_iterator<Iter>& lhs,
						const ft::reverse_iterator<Iter>& rhs)
		{return (lhs.base() < rhs.base());}

		template<class Iterator1, class Iterator2>
		bool operator>(const ft::reverse_iterator<Iterator1>& lhs,
					   const ft::reverse_iterator<Iterator2>& rhs)
		{return (lhs.base() < rhs.base());}
		
		template<class Iter>
		bool operator>=(const ft::reverse_iterator<Iter>& lhs,
						const ft::reverse_iterator<Iter>& rhs)
		{return (lhs.base() <= rhs.base());}

		template<class Iterator1, class Iterator2>
		bool operator>=(const ft::reverse_iterator<Iterator1>& lhs,
						const ft::reverse_iterator<Iterator2>& rhs)
		{return (lhs.base() <= rhs.base());}

		/* -------------------------------- Operation ------------------------------- */
		//template<class Iter>
		//typename ft::reverse_iterator<Iter>::difference_type
		//operator+(typename ft::reverse_iterator<Iter>::difference_type n,
		//		  const ft::reverse_iterator<Iter>& it)
		//{
		//	return (reverse_iterator<Iter>(it.base() - n));
		//}

		template< class Iterator1, class Iterator2 >
		typename ft::reverse_iterator<Iterator1>::difference_type 
		operator-(const ft::reverse_iterator<Iterator1>& lhs,
				  const ft::reverse_iterator<Iterator2>& rhs)
		{return (rhs.base() - lhs.base());}
		
	
	
};