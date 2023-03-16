#include "test.hpp"

void	vector_canonicalform( void )
{
	std::cout << "CANONICAL FORM" << std::endl;

	{
		std::cout << "-> default and copy constructors" << std::endl;
		NAMESPACE::vector<test>	vec;
		std::cout << "----------" << std::endl;
		NAMESPACE::vector<test>	vec2( vec );
		std::cout << "----------" << std::endl;
	}
	std::cout << "----------" << std::endl << std::endl;

	{
		std::cout << "-> fill constructor (with number of elements as "
			"argument), copy constructor, and operator= overload" << std::endl;
		NAMESPACE::vector<test>	vec( 2 );
		std::cout << "----------" << std::endl;
		NAMESPACE::vector<test>	vec2( vec );
		std::cout << "----------" << std::endl;
		NAMESPACE::vector<test> vec3;
		vec3 = vec2;
		std::cout << "----------" << std::endl;
	}
	std::cout << "----------" << std::endl << std::endl;

	{
		std::cout << "-> range constructor (with iterators as arguments)"
			<< std::endl;
		NAMESPACE::vector<test>	vec( 2 );
		NAMESPACE::vector<test>::iterator	it = vec.begin();
		NAMESPACE::vector<test>::iterator	ite = vec.end();
		NAMESPACE::vector<test>	vec2( it, ite );
		std::cout << "----------" << std::endl;
	}

	std::cout << "--------------------" << std::endl << std::endl;
}

void	vector_iterator( void )
{
	std::cout << "ITERATOR" << std::endl;

	NAMESPACE::vector<int>	vec( 5 );
	int		i = 0;
	NAMESPACE::vector<int>::const_reverse_iterator crite = vec.rend();
	for ( NAMESPACE::vector<int>::reverse_iterator rit = vec.rbegin();
			rit != crite; ++rit )
		*rit = ++i;
	std::cout << "vec (backwards):";
	NAMESPACE::vector<int>::const_iterator cit = vec.begin();
	for ( NAMESPACE::vector<int>::iterator ite = vec.end() - 1;
			ite >= cit; --ite )
		std::cout << ' ' << *ite;
	std::cout << std::endl;

	i = 0;
	NAMESPACE::vector<test_struct>	vec2( 10 );
	NAMESPACE::vector<test_struct>::const_iterator cite2 = vec2.end();
	for ( NAMESPACE::vector<test_struct>::iterator it = vec2.begin() + 1;
			it <= cite2; it++ )
		(it - 1)->n = i++;
	std::cout << "vec2 len: " << vec2.end() - vec2.begin() << std::endl;
	std::cout << "vec2 (odd values):";
	for ( NAMESPACE::vector<test_struct>::iterator it = vec2.begin();
			cite2 > it; it += 2 )
		std::cout << ' ' << it[1].n;
	std::cout << std::endl;

	const NAMESPACE::vector<int>	vec3( vec.begin(), 3 + vec.begin() );
	std::cout << "vec3 (const):";
	NAMESPACE::vector<int>::const_iterator cite = vec3.end();
	for ( NAMESPACE::vector<int>::const_iterator cit = vec3.begin();
			cit != cite; ++cit )
		std::cout << ' ' << *cit;
	std::cout << std::endl;
	std::cout << "vec3 reversed (const):";
	for ( NAMESPACE::vector<int>::const_reverse_iterator crit = vec3.rbegin();
			crit != vec3.rend(); ++crit )
		std::cout << ' ' << *crit;
	std::cout << std::endl;

	NAMESPACE::vector<int>::iterator		it = vec.begin();
	NAMESPACE::vector<int>::const_iterator	cit2( it );
	cit2 = it;

	NAMESPACE::vector<int>::reverse_iterator		rit = vec.rbegin();
	NAMESPACE::vector<int>::const_reverse_iterator	crit( rit );
	crit = rit;

	std::cout << "--------------------" << std::endl << std::endl;
}

template < class T, class Alloc >
	void	print_vector( NAMESPACE::vector<T,Alloc>& vec )
	{
		std::cout << "values:";
		for ( typename NAMESPACE::vector<T,Alloc>::size_type i = 0;
				i < vec.size(); i++ )
		{
			std::cout << ' ' << vec[i];
		}
		std::cout << std::endl;
		std::cout << "capacity = " << vec.capacity() << std::endl;
		std::cout << "size = " << vec.size() << std::endl;
		std::cout << "----------" << std::endl;
	}

void	vector_capacity( void )
{
	std::cout << "CAPACITY" << std::endl;

	NAMESPACE::vector<int>	vec( 3, 2 );
	std::cout << "-> vec( 3, 2 )" << std::endl;
	print_vector( vec );

	vec.resize( 4 );
	std::cout << "-> resize( 4 )" << std::endl;
	print_vector( vec );

	vec.reserve( 5 );
	std::cout << "-> reserve( 5 )" << std::endl;
	print_vector( vec );

	vec.resize( 5, 3 );
	std::cout << "-> resize( 5, 3 )" << std::endl;
	print_vector( vec );

	vec.reserve( 2 );
	std::cout << "-> reserve( 2 )" << std::endl;
	print_vector( vec );

	vec.resize( 1, 1 );
	std::cout << "-> resize( 1, 1 )" << std::endl;
	print_vector( vec );

	std::cout << "max_size = " << vec.max_size() << std::endl;
	std::cout << "empty = " << vec.empty() << std::endl;

	NAMESPACE::vector<test>	vec2;
	std::cout << "-> vec2 ()" << std::endl;
	std::cout << "vec2.empty = " << vec2.empty() << std::endl;

	std::cout << "--------------------" << std::endl << std::endl;
}

void	vector_elementaccess( void )
{
	std::cout << "ELEMENT ACCESS" << std::endl;

	NAMESPACE::vector<int>	vec( 3, 1 );
	vec[1] = 2;
	vec[2] = 3;
	std::cout << "front = " << vec.front() << std::endl;
	std::cout << "at 1 = " << vec.at( 1 ) << std::endl;
	std::cout << "back = " << vec.back() << std::endl;
	try
	{
		std::cout << "vec.at( 4 ) = " << vec.at( 4 ) << std::endl;
	}
	catch ( std::exception &e )
	{
		std::cerr << e.what() << std::endl;
	}
	std::cout << "----------" << std::endl;

	std::cout << "for loop with brackets operator ([]):";
	for ( NAMESPACE::vector<int>::size_type i = 0; i < vec.size(); i++ )
	{
		std::cout << " " << vec[i];
	}
	std::cout << "----------" << std::endl;
	std::cout << std::endl;

	const NAMESPACE::vector<int>	vec2( vec );
	std::cout << "-> vec2( vec ) (const)" << std::endl;
	std::cout << "vec2.front = " << vec2.front() << std::endl;
	std::cout << "vec2.at( 1 ) = " << vec2.at( 1 ) << std::endl;
	std::cout << "vec2.back = " << vec2.back() << std::endl;

	std::cout << "--------------------" << std::endl << std::endl;
}

void	vector_modifiers( void )
{
	std::cout << "MODIFIERS" << std::endl;

	NAMESPACE::vector<int> vec( 2, 4 );
	std::cout << "-> vec( 2, 4 )" << std::endl;
	print_vector( vec );

	NAMESPACE::vector<int> vec_input;
	std::cout << "-> vec_input default constructed" << std::endl;
	vec_input.assign( 1, 3 );
	std::cout << "-> vec_input.assign( 1, 3 )" << std::endl;
	std::cout << "=== print vec_input ===" << std::endl;
	print_vector( vec_input );
	NAMESPACE::vector<int>::iterator	it = vec_input.begin();
	std::cout << "-> it = vec_input.begin()" << std::endl;
	NAMESPACE::vector<int>::iterator	ite = vec_input.end();
	std::cout << "-> ite = vec_input.end()" << std::endl;
	vec.assign( it, ite );
	std::cout << "-> vec.assign( it, ite )" << std::endl;
	std::cout << "=== print vec ===" << std::endl;
	print_vector( vec );

	vec_input.assign( 4, 6 );
	std::cout << "-> vec_input.assign( 4, 6 )" << std::endl;
	std::cout << "=== print vec_input ===" << std::endl;
	print_vector( vec_input );
	it = vec_input.begin();
	std::cout << "-> it = vec_input.begin()" << std::endl;
	ite = vec_input.end();
	std::cout << "-> ite = vec_input.end()" << std::endl;
	vec.assign( it, ite );
	std::cout << "-> vec.assign( it, ite )" << std::endl;
	std::cout << "=== print vec ===" << std::endl;
	print_vector( vec );

	vec.pop_back();
	std::cout << "-> pop_back()" << std::endl;
	print_vector( vec );

	vec.pop_back();
	std::cout << "-> pop_back()" << std::endl;
	print_vector( vec );

	vec_input.assign( 3, 5 );
	std::cout << "-> vec_input.assign( 3, 5 )" << std::endl;
	std::cout << "=== print vec_input ===" << std::endl;
	print_vector( vec_input );
	it = vec_input.begin();
	std::cout << "-> it = vec_input.begin()" << std::endl;
	ite = vec_input.end();
	std::cout << "-> ite = vec_input.end()" << std::endl;
	vec.assign( it, ite );
	std::cout << "-> vec.assign( it, ite )" << std::endl;
	std::cout << "=== print vec ===" << std::endl;
	print_vector( vec );

	vec.push_back( 8 );
	std::cout << "-> push_back( 8 )" << std::endl;
	print_vector( vec );

	vec.push_back( 7 );
	std::cout << "-> push_back( 7 )" << std::endl;
	print_vector( vec );

	std::cout << "-> insert( 1, 3 )" << std::endl;
	std::cout << "value inserted: " << *vec.insert( vec.begin() + 1, 3 )
		<< std::endl;
	print_vector( vec );

	vec.insert( vec.begin() + 5, 2, 9 );
	std::cout << "-> insert( 5, 2, 9 )" << std::endl;
	print_vector( vec );

	vec_input.assign( 2, 1 );
	std::cout << "-> vec_input.assign( 2, 1 )" << std::endl;
	std::cout << "=== print vec_input ===" << std::endl;
	print_vector( vec_input );
	it = vec_input.begin();
	std::cout << "-> it = vec_input.begin()" << std::endl;
	ite = vec_input.end();
	std::cout << "-> ite = vec_input.end()" << std::endl;
	vec.insert( vec.begin(), it, ite );
	std::cout << "-> vec.insert( 0, it, ite )" << std::endl;
	std::cout << "=== print vec ===" << std::endl;
	print_vector( vec );

	std::cout << "-> erase( 2 )" << std::endl;
	std::cout << "value following erased one: " << *vec.erase( vec.begin() + 2 )
		<< std::endl;
	print_vector( vec );

	std::cout << "-> erase( 1, 3 )" << std::endl;
	std::cout << "value following erased ones: "
		<< *vec.erase( vec.begin() + 1, vec.begin() + 3 ) << std::endl;
	print_vector( vec );

	NAMESPACE::vector<int> vec2( 2, 9 );
	std::cout << "-> vec2( 2, 9 )" << std::endl;
	print_vector( vec2 );

	std::cout << "-> it_vec = vec.begin()" << std::endl;
	NAMESPACE::vector<int>::iterator	it_vec = vec.begin();
	std::cout << "-> ite_vec = vec.end()" << std::endl;
	NAMESPACE::vector<int>::iterator	ite_vec = vec.end();
	vec.swap( vec2 );
	std::cout << "-> vec.swap( vec2 )" << std::endl;
	std::cout << "=== print vec ===" << std::endl;
	print_vector( vec );
	std::cout << "=== print vec2 ===" << std::endl;
	print_vector( vec2 );
	std::cout << "contents from it_vec until ite_vec:";
	for ( ; it_vec != ite_vec; it_vec++ )
		std::cout << " " << *it_vec;
	std::cout << std::endl;
	std::cout << "----------" << std::endl << std::endl;

	vec.clear();
	std::cout << "-> vec.clear()" << std::endl;
	print_vector( vec );

	std::cout << "--------------------" << std::endl << std::endl;
}

void	vector_allocator( void )
{
	NAMESPACE::vector<int>	vec;
	vec.get_allocator();
}

void	vector_non_member_functions( void )
{
	std::cout << "NON MEMBER FUNCTIONS" << std::endl;

	NAMESPACE::vector<int>	vec1( 8, 1 );
	std::cout << "=== print vec1 ===" << std::endl;
	print_vector( vec1 );
	NAMESPACE::vector<int>	vec2( 5, 3 );
	std::cout << "=== print vec2 ===" << std::endl;
	print_vector( vec2 );
	NAMESPACE::vector<int>	vec3( 8, 1 );
	std::cout << "=== print vec3 ===" << std::endl;
	print_vector( vec3 );

	std::cout << std::boolalpha;
	std::cout << "vec1 == vec2: " << (vec1 == vec2) << std::endl;
	std::cout << "vec1 == vec3: " << (vec1 == vec3) << std::endl;
	std::cout << "----------" << std::endl;
	std::cout << "vec1 != vec2: " << (vec1 != vec2) << std::endl;
	std::cout << "vec1 != vec3: " << (vec1 != vec3) << std::endl;
	std::cout << "----------" << std::endl;
	std::cout << "vec1 < vec2: " << (vec1 < vec2) << std::endl;
	std::cout << "vec1 < vec3: " << (vec1 < vec3) << std::endl;
	std::cout << "----------" << std::endl;
	std::cout << "vec1 <= vec2: " << (vec1 <= vec2) << std::endl;
	std::cout << "vec1 <= vec3: " << (vec1 <= vec3) << std::endl;
	std::cout << "----------" << std::endl;
	std::cout << "vec1 > vec2: " << (vec1 > vec2) << std::endl;
	std::cout << "vec1 > vec3: " << (vec1 > vec3) << std::endl;
	std::cout << "----------" << std::endl;
	std::cout << "vec1 >= vec2: " << (vec1 >= vec2) << std::endl;
	std::cout << "vec1 >= vec3: " << (vec1 >= vec3) << std::endl;
	std::cout << "----------" << std::endl;

	std::cout << "-> swap( vec1, vec2 )" << std::endl;
	swap( vec1, vec2 );
	std::cout << "=== print vec1 ===" << std::endl;
	print_vector( vec1 );
	std::cout << "=== print vec2 ===" << std::endl;
	print_vector( vec2 );
}

void	reverse_iterator_vector( void )
{
	std::cout << "REVERSE ITERATOR" << std::endl;

	std::vector<int>	vec;

	for ( std::vector<int>::size_type i = 0; i < 10; i++ )
		vec.push_back( i );

	typedef	std::vector<int>::iterator	iter_type;
	iter_type		from( vec.begin() );
	iter_type		until( vec.end() );

	NAMESPACE::reverse_iterator<iter_type>	rev_until( from );
	NAMESPACE::reverse_iterator<iter_type>	rev_from( until );

	std::cout << "vec rev:";
	while ( rev_from < rev_until )
		std::cout << ' ' << *rev_from++;
	std::cout << std::endl;

	rev_from -= 10;
	std::cout << "vec (using underlying iterator):";
	for ( iter_type it = rev_until.base(); it != rev_from.base(); it++ )
		std::cout << ' ' << *it;
	std::cout << std::endl;

	std::cout << "vec span = " << rev_from - rev_until << std::endl;

	std::cout << "vec rev:";
	for ( std::vector<int>::size_type i = 0; i < 10; i++ )
		std::cout << ' ' << rev_from[i];
	std::cout << std::endl;

	std::cout << "--------------------" << std::endl << std::endl;
}
