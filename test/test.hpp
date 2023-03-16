#pragma once

#include "../containers/vector.hpp"
#include "../containers/stack.hpp"
#include "../containers/map.hpp"
#include <vector>
#include <stack>
#include <map>
#define NAMESPACE ft
#include <cstdlib> // EXIT_SUCCESS
#include <iostream>

class test
{
	public:

		int		id;

		test ( void )
		{
			static int i = 1000;
			id = i;
			i++;
			std::cout << "[" << id << "] default constructor" << std::endl;
		}
		test ( int arg )
		{
			(void)arg;
			static int i = 0;
			id = i;
			i++;
			std::cout << "[" << id << "] parameterized constructor"
				<< std::endl;
		}
		test ( const test& src )
		{
			id = src.id + 10;
			std::cout << "[" << id << "] copy constructor from " << src.id
				<< std::endl;
			*this = src;
		}
		~test ( void )
		{
			std::cout << "[" << id << "] destructor" << std::endl;
		}
		test&	operator= ( const test& rhs )
		{
			std::cout << "[" << id << "-->" << rhs.id + 100
				<< "] operator= (test &) from " << rhs.id << std::endl;
			id = rhs.id + 100;
			return ( *this );
		}
		test&	operator= ( int arg )
		{
			std::cout << "[" << id << "-->" << arg + 100
				<< "] operator= (int) from " << arg << " (int arg) "
				<< std::endl;
			id = arg + 100;
			return ( *this );
		}
		friend std::ostream&	operator<<( std::ostream& o, const test& rhs )
		{
			o << rhs.id;
			return ( o );
		}
		bool	operator== ( const test& rhs ) const
		{
			return ( id == rhs.id );
		}
		bool	operator< ( const test& rhs ) const
		{
			return ( id < rhs.id );
		}
};

struct	test_struct
{
	int n;
};

void	vector_canonicalform ( void );
void	vector_iterator ( void );
template < class T, class Alloc >
	void	print_vector ( NAMESPACE::vector<T,Alloc>& vec );
void	vector_capacity ( void );
void	vector_elementaccess ( void );
void	vector_modifiers ( void );
void	vector_allocator ( void );
void	vector_non_member_functions ( void );
void	reverse_iterator_vector ( void );

void	stack_tests ( void );

void	pair ( void );
void	map_canonicalform( void );
void	map_iterator ( void );
void	map_capacity ( void );
void	map_elementaccess ( void );
void	map_modifiers ( void );
void	map_observers ( void );
void	map_operations ( void );
void	map_allocator( void );
void	map_non_member_functions( void );
void	map_more( void );
void	map_same( void );
