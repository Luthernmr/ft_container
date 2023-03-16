#pragma once

#include "vector.hpp"

namespace ft
{
	template	<typename T, typename Container = ft::vector<T> >
    class		stack
	{
    public:
        typedef Container							container_type;
        typedef typename Container::value_type		value_type;
        typedef typename Container::size_type		size_type;
        typedef typename Container::reference		reference;
        typedef typename Container::const_reference	const_reference;

    protected:
        container_type _array;

    public:
	/* ------------------ Constructor/Destructor/Assign content ----------------- */
        explicit stack(const container_type& cont = container_type())
		: _array(cont) {}

		~stack() {}

		stack&				operator=(const stack& other)
		{
			_array = other._array;
			return (*this);
		}

	/* ----------------------------- Element Access ----------------------------- */
        value_type&			top() {return (_array.back());}
        const value_type&	top() const {return (_array.back());}

	/* -------------------------------- Capacity -------------------------------- */
        bool				empty() const {return (_array.empty());}
        size_type			size() const {return (_array.size());}

	/* -------------------------------- Modifiers ------------------------------- */
        void				push(const value_type& value) {_array.push_back(value);}
        void				pop() {_array.pop_back();}

	/* -------------------------------- Operators ------------------------------- */
		friend bool			operator==(const stack<value_type, container_type>& lhs,
										const stack<value_type, container_type>& rhs)
		{ return (lhs._array == rhs._array); }

		friend bool			operator!=(const stack<value_type, container_type>& lhs,
										const stack<value_type, container_type>& rhs)
		{ return (!(lhs._array == rhs._array)); }

		friend bool			operator<(const stack<value_type, container_type>& lhs,
										const stack<value_type, container_type>& rhs)
		{ return (lhs._array < rhs._array); }
		friend bool			operator<=(const stack<value_type, container_type>& lhs,
										const stack<value_type, container_type>& rhs)
		{ return (lhs._array <= rhs._array); }
		friend bool			operator>(const stack<value_type, container_type>& lhs,
										const stack<value_type, container_type>& rhs)
		{ return (lhs._array > rhs._array); }
		friend bool			operator>=(const stack<value_type, container_type>& lhs,
										const stack<value_type, container_type>& rhs)
		{ return (lhs._array >= rhs._array); }
    };

}