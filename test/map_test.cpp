#include "test.hpp"

void	pair ( void )
{
	std::cout << "PAIR" << std::endl;

	NAMESPACE::pair<test,int>	p ( 1, 2 );
	NAMESPACE::pair<test,int>	p2 ( p );

	std::cout << p.first << ", " << p.second << std::endl;

	NAMESPACE::pair<test,int>	p3 = NAMESPACE::make_pair<test,int>( 1, 2 );

	std::cout << p3.first << ", " << p3.second << std::endl;

	NAMESPACE::pair<int,test>	p4 ( 1, 2 );
	NAMESPACE::pair<int,test>	p5 ( p4 );

	std::cout << p5.first << ", " << p5.second << std::endl;

	NAMESPACE::pair<char,test>	p6;
	p6 = NAMESPACE::make_pair<char,test>( 'c', 2 );

	std::cout << p6.first << ", " << p6.second << std::endl;

	std::cout << "----------" << std::endl << std::endl;
}

void	map_canonicalform( void )
{
	std::cout << "CANONICAL FORM" << std::endl;

	{
		std::cout << "-> default and copy constructors" << std::endl;
		NAMESPACE::map<test,int>	map;
		std::cout << "----------" << std::endl;
		NAMESPACE::map<test,int>	map2( map );
		std::cout << "----------" << std::endl;
	}
	std::cout << "----------" << std::endl << std::endl;

	{
		std::cout << "-> copy constructor from filled map, and operator= "
			"overload" << std::endl;
		NAMESPACE::map<int,test>	map;
		map.insert( NAMESPACE::make_pair( 1, 'a' ) );
		map.insert( NAMESPACE::make_pair( 2, 'b' ) );
		map.insert( NAMESPACE::make_pair( 3, 'c' ) );
		std::cout << "----------" << std::endl;
		NAMESPACE::map<int,test>	map2( map );
		std::cout << "----------" << std::endl;
		NAMESPACE::map<int,test>	map3;
		map3 = map2;
		std::cout << "map size = " << map.size() << std::endl;
		std::cout << "map2 size = " << map2.size() << std::endl;
		std::cout << "map3 size = " << map3.size() << std::endl;
		std::cout << "----------" << std::endl;
	}

	std::cout << "----------" << std::endl << std::endl;

	{
		std::cout << "-> range constructor (with iterators as arguments)"
			<< std::endl;
		NAMESPACE::map<test,test>	map;
		map.insert( NAMESPACE::make_pair( 1, 'a' ) );
		map.insert( NAMESPACE::make_pair( 2, 'b' ) );
		map.insert( NAMESPACE::make_pair( 3, 'c' ) );
		NAMESPACE::map<test,test>::iterator	it = map.begin();
		NAMESPACE::map<test,test>::iterator	ite = map.end();
		NAMESPACE::map<test,test>	map2( it, ite );
		std::cout << "map size = " << map.size() << std::endl;
		std::cout << "map2 size = " << map2.size() << std::endl;
		std::cout << "----------" << std::endl;
	}

	std::cout << "--------------------" << std::endl << std::endl;
}

NAMESPACE::map<int,char>	sample_map ( void )
{
	NAMESPACE::map<int,char>	map;

	map.insert( NAMESPACE::make_pair( 1, 'a' ) );
	map.insert( NAMESPACE::make_pair( 2, 'b' ) );
	map.insert( NAMESPACE::make_pair( 3, 'c' ) );
	map.insert( NAMESPACE::make_pair( 4, 'd' ) );
	map.insert( NAMESPACE::make_pair( 5, 'e' ) );

	return ( map );
}

void	map_iterator ( void )
{
	std::cout << "ITERATOR" << std::endl;

	NAMESPACE::map<int,char>	map = sample_map();
	std::cout << "-> map = sample map with 5 elements (keys go from 1 to 5, "
		"and values from 'a' to 'e')" << std::endl;

	std::cout << "map:\t";
	NAMESPACE::map<int,char>::const_iterator cit = map.begin();
	NAMESPACE::map<int,char>::iterator ite = map.end();
	for ( ; cit != ite; cit++ )
		std::cout << '\t' << cit->first << ' ' << cit->second;
	std::cout << std::endl;

	std::cout << "map reversed:";
	NAMESPACE::map<int,char>::const_reverse_iterator crite = map.rend();
	for ( NAMESPACE::map<int,char>::reverse_iterator rit = map.rbegin();
			rit != crite; ++rit )
		std::cout << '\t' << rit->first << ' ' << rit->second;
	std::cout << std::endl;

	std::cout << "--------------------" << std::endl << std::endl;
}

void	map_capacity ( void )
{
	std::cout << "CAPACITY" << std::endl;

	NAMESPACE::map<int,char>	map = sample_map();
	std::cout << "-> map = sample map with 5 elements (keys go from 1 to 5, "
		"and values from 'a' to 'e')" << std::endl;
	std::cout << "map.size() = " << map.size() << std::endl;
	std::cout << "map.max_size() = " << map.max_size() << std::endl;
	std::cout << "map.empty() = " << map.empty() << std::endl;
	std::cout << "----------" << std::endl;

	NAMESPACE::map<int,char>	map2;
	std::cout << "-> map2 default constructed" << std::endl;
	std::cout << "map2.empty() = " << map2.empty() << std::endl;

	std::cout << "--------------------" << std::endl << std::endl;
}

template < class Key, class T, class Compare, class Alloc >
	void	print_map ( NAMESPACE::map<Key,T,Compare,Alloc>& map )
	{
		std::cout << "[keys, values]:" << std::endl;
		typename NAMESPACE::map<Key,T,Compare,Alloc>::iterator it = map.begin();
		typename NAMESPACE::map<Key,T,Compare,Alloc>::iterator ite = map.end();
		for ( ; it != ite; it++ )
		{
			std::cout << '[' << it->first << ", " << it->second << ']'
				<< std::endl;
		}
		std::cout << "size = " << map.size() << std::endl;
		std::cout << "----------" << std::endl;
	}

void	map_elementaccess ( void )
{
	std::cout << "ELEMENT ACCESS" << std::endl;

	NAMESPACE::map<int,char>	map = sample_map();
	std::cout << "-> map = sample map with 5 elements (keys go from 1 to 5, "
		"and values from 'a' to 'e')" << std::endl;

	map[3] = 'p';
	std::cout << "-> map[3] = 'p'" << std::endl;
	map[-2] = 'i';
	std::cout << "-> map[-2] = 'i'" << std::endl;
	map[68] = 'f';
	std::cout << "-> map[68] = 'f'" << std::endl;
	map[7];
	std::cout << "-> map[7]" << std::endl;
	print_map( map );

	try
	{
		std::cout << "map.at( 4 ) = " << map.at(4) << std::endl;
		std::cout << "map.at( 8 ) = " << map.at( 8 ) << std::endl;
	}
	catch ( std::exception &e )
	{
		std::cerr << e.what() << std::endl;
	}
	std::cout << "----------" << std::endl;
}

NAMESPACE::map<int,char>	map_insert ( void )
{
	std::cout << "MODIFIERS" << std::endl;

	NAMESPACE::map<int,char>	map;
	NAMESPACE::pair<NAMESPACE::map<int,char>::iterator,bool>	res;

	std::cout << std::boolalpha;
	res = map.insert( NAMESPACE::make_pair( 0, 'a' ) );
	std::cout << "-> map.insert( make_pair( 0, 'a' ) )" << std::endl
		<< "returned iterator points to: " << res.first->first << ", "
		<< res.first->second << std::endl
		<< "insertion success: " << res.second << std::endl;
	res = map.insert( NAMESPACE::make_pair( 7, 'b' ) );
	std::cout << "-> map.insert( make_pair( 7, 'b' ) )" << std::endl
		<< "returned iterator points to: " << res.first->first << ", "
		<< res.first->second << std::endl
		<< "insertion success: " << res.second << std::endl;
	res = map.insert( NAMESPACE::make_pair( -2, 'c' ) );
	std::cout << "-> map.insert( make_pair( -2, 'c' ) )" << std::endl
		<< "returned iterator points to: " << res.first->first << ", "
		<< res.first->second << std::endl
		<< "insertion success: " << res.second << std::endl;
	res = map.insert( NAMESPACE::make_pair( 7, 'd' ) );
	std::cout << "-> map.insert( make_pair( 7, 'd' ) )" << std::endl
		<< "returned iterator points to: " << res.first->first << ", "
		<< res.first->second << std::endl
		<< "insertion success: " << res.second << std::endl;
	res = map.insert( NAMESPACE::make_pair( 10, 'e' ) );
	std::cout << "-> map.insert( make_pair( 10, 'e' ) )" << std::endl
		<< "returned iterator points to: " << res.first->first << ", "
		<< res.first->second << std::endl
		<< "insertion success: " << res.second << std::endl;

	print_map( map );

	NAMESPACE::map<int,char>::iterator	it = map.begin();
	std::cout << "-> it = map.begin()" << std::endl;
	NAMESPACE::map<int,char>::iterator	it_res;

	it_res = map.insert( it, NAMESPACE::make_pair( -1, 'f' ) );
	std::cout << "-> map.insert( it, make_pair( -1, 'f' ) )" << std::endl
		<< "returned iterator points to: " << it_res->first << ", "
		<< it_res->second << std::endl;
	++it;
	std::cout << "-> it++" << std::endl;
	++it;
	std::cout << "-> it++" << std::endl;
	it_res = map.insert( it, NAMESPACE::make_pair( 6, 'g' ) );
	std::cout << "-> map.insert( it, make_pair( 6, 'g' ) )" << std::endl
		<< "returned iterator points to: " << it_res->first << ", "
		<< it_res->second << std::endl;
	++it;
	std::cout << "-> it++" << std::endl;
	++it;
	std::cout << "-> it++" << std::endl;
	it_res = map.insert( it, NAMESPACE::make_pair( 8, 'h' ) );
	std::cout << "-> map.insert( it, make_pair( 8, 'h' ) )" << std::endl
		<< "returned iterator points to: " << it_res->first << ", "
		<< it_res->second << std::endl;
	++it;
	std::cout << "-> it++" << std::endl;
	it_res = map.insert( it, NAMESPACE::make_pair( 9, 'i' ) );
	std::cout << "-> map.insert( it, make_pair( 9, 'i' ) )" << std::endl
		<< "returned iterator points to: " << it_res->first << ", "
		<< it_res->second << std::endl;
	++it;
	std::cout << "-> it++" << std::endl;
	++it;
	std::cout << "-> it++" << std::endl;
	it_res = map.insert( it, NAMESPACE::make_pair( 11, 'j' ) );
	std::cout << "-> map.insert( it, make_pair( 11, 'j' ) )" << std::endl
		<< "returned iterator points to: " << it_res->first << ", "
		<< it_res->second << std::endl;

	print_map( map );

	NAMESPACE::map<int,char>	map_input = sample_map();
	std::cout << "-> map_input = sample map() i.e. with 5 elements (keys go "
		"from 1 to 5, and values from 'a' to 'e')" << std::endl;
	map.insert( map_input.begin(), map_input.end() );

	print_map( map );

	std::cout << "--------------------" << std::endl << std::endl;

	return ( map );
}

void	map_erase ( NAMESPACE::map<int,char> map )
{
	NAMESPACE::map<int,char>::iterator	it = map.begin();
	std::cout << "-> it = map.begin()" << std::endl;

	map.erase( it );
	std::cout << "map.erase( it )" << std::endl;
	print_map( map );

	it = map.begin();
	std::cout << "-> it = map.begin()" << std::endl;

	NAMESPACE::map<int,char>::size_type	res = map.erase( 5 );
	std::cout << "map.erase( 5 )" << std::endl;
	std::cout << res << " element removed" << std::endl;
	print_map( map );

	res = map.erase( 13 );
	std::cout << "map.erase( 13 )" << std::endl;
	std::cout << res << " element removed" << std::endl;
	print_map( map );

	++it;
	std::cout << "++it" << std::endl;
	++it;
	std::cout << "++it" << std::endl;
	++it;
	std::cout << "++it" << std::endl;
	++it;
	std::cout << "++it" << std::endl;
	++it;
	std::cout << "++it" << std::endl;
	++it;
	std::cout << "++it" << std::endl;
	++it;
	std::cout << "++it" << std::endl;
	++it;
	std::cout << "++it" << std::endl;
	map.erase( it, map.end() );
	std::cout << "map.erase( it, map.end() )" << std::endl;
	print_map( map );

	std::cout << "--------------------" << std::endl << std::endl;
}

void	map_swap_clear ( NAMESPACE::map<int,char> map )
{
	NAMESPACE::map<int,char>	map2 = sample_map();
	std::cout << "-> map2 = sample map with 5 elements (keys go from 1 to 5, "
		"and values from 'a' to 'e')" << std::endl;

	map.swap( map2 );
	std::cout << "-> map.swap( map2 )" << std::endl;
	std::cout << "=== print map ===" << std::endl;
	print_map( map );
	std::cout << "=== print map2 ===" << std::endl;
	print_map( map2 );

	map.clear();
	std::cout << "-> map.clear()" << std::endl;
	print_map( map );

	std::cout << "--------------------" << std::endl << std::endl;
}

void	map_modifiers ( void )
{
	std::cout << "MODIFIERS" << std::endl;

	NAMESPACE::map<int,char>	map;

	map = map_insert();
	map_erase( map );
	map_swap_clear( map );
}

void	map_observers ( void )
{
	std::cout << "OBSERVERS" << std::endl;

	// key_comp()
	// from https://cplusplus.com/reference/map/map/key_comp/
	NAMESPACE::map<char,int>	map;
	NAMESPACE::map<char,int>::key_compare	comp = map.key_comp();

	map['a'] = 100;
	map['b'] = 200;
	map['c'] = 300;

	char	highest = map.rbegin()->first;
	NAMESPACE::map<char,int>::iterator	it = map.begin();
	std::cout << "map contains:" << std::endl;
	do
	{
		std::cout << it->first << " => " << it->second << std::endl;
	} while ( comp( (*it++).first, highest ) );
	std::cout << std::endl;


	// value_comp()
	// from https://cplusplus.com/reference/map/map/value_comp/
	NAMESPACE::map<char,int>	map2;

	map2['x'] = 1001;
	map2['y'] = 2002;
	map2['z'] = 3003;

	NAMESPACE::pair<char,int>	highest2 = *map2.rbegin();
	NAMESPACE::map<char,int>::iterator	it2 = map2.begin();
	std::cout << "map2 contains:" << std::endl;
	do
	{
		std::cout << it2->first << " => " << it2->second << std::endl;
	} while ( map2.value_comp()( *it2++, highest2 ) );

	std::cout << "--------------------" << std::endl << std::endl;
}

void	map_operations ( void )
{
	std::cout << "OPERATIONS" << std::endl;

	NAMESPACE::map<int,char>	map = sample_map();
	std::cout << "-> map = sample map with 5 elements (keys go from 1 to 5, "
		"and values from 'a' to 'e')" << std::endl;

	NAMESPACE::map<int,char>::iterator	it = map.find( 4 );
	std::cout << "-> it = map.find( 4 )" << std::endl;
	std::cout << "it->first = " << it->first << ", it->second = " << it->second
		<< std::endl;

	it = map.find( 9 );
	std::cout << "-> it = map.find( 9 )" << std::endl;
	std::cout << std::boolalpha << "it == map.end(): " << ( it == map.end() )
		<< std::endl;
	std::cout << "----------" << std::endl;

	std::cout << "map.count( 2 ) = " << map.count( 2 ) << std::endl;
	std::cout << "map.count( 8 ) = " << map.count( 8 ) << std::endl;
	std::cout << "----------" << std::endl;

	it = map.lower_bound( 2 );
	std::cout << "-> it = map.lower_bound( 2 )" << std::endl;
	std::cout << "it->first = " << it->first << ", it->second = " << it->second
		<< std::endl;
	std::cout << "----------" << std::endl;

	it = map.upper_bound( 2 );
	std::cout << "-> it = map.upper_bound( 2 )" << std::endl;
	std::cout << "it->first = " << it->first << ", it->second = " << it->second
		<< std::endl;
	std::cout << "----------" << std::endl;

	NAMESPACE::pair<NAMESPACE::map<int,char>::iterator,
		NAMESPACE::map<int,char>::iterator> range;
	range = map.equal_range( 4 );
	std::cout << "-> range = map.equal_range( 4 )" << std::endl;

	std::cout << "range.first->first = " << range.first->first
		<< ", range.first->second = " << range.first->second << std::endl;
	std::cout << "range.second->first = " << range.second->first
		<< ", range.second->second = " << range.second->second << std::endl;
	std::cout << "----------" << std::endl;

	std::cout << "--------------------" << std::endl << std::endl;
}

void	map_allocator( void )
{
	NAMESPACE::map<int,char>	map;
	map.get_allocator();
}

void	map_non_member_functions( void )
{
	std::cout << "NON MEMBER FUNCTIONS" << std::endl;

	NAMESPACE::map<int,char>	map1 = sample_map();
	std::cout << "=== print map1 ===" << std::endl;
	print_map( map1 );
	NAMESPACE::map<int,char>	map2 = sample_map();
	map2.erase( 3 );
	map2.insert( NAMESPACE::make_pair( 9, 'i' ) );
	std::cout << "=== print map2 ===" << std::endl;
	print_map( map2 );
	NAMESPACE::map<int,char>	map3 = sample_map();
	std::cout << "=== print map3 ===" << std::endl;
	print_map( map3 );

	std::cout << std::boolalpha;
	std::cout << "map1 == map2: " << (map1 == map2) << std::endl;
	std::cout << "map1 == map3: " << (map1 == map3) << std::endl;
	std::cout << "----------" << std::endl;
	std::cout << "map1 != map2: " << (map1 != map2) << std::endl;
	std::cout << "map1 != map3: " << (map1 != map3) << std::endl;
	std::cout << "----------" << std::endl;
	std::cout << "map1 < map2: " << (map1 < map2) << std::endl;
	std::cout << "map1 < map3: " << (map1 < map3) << std::endl;
	std::cout << "----------" << std::endl;
	std::cout << "map1 <= map2: " << (map1 <= map2) << std::endl;
	std::cout << "map1 <= map3: " << (map1 <= map3) << std::endl;
	std::cout << "----------" << std::endl;
	std::cout << "map1 > map2: " << (map1 > map2) << std::endl;
	std::cout << "map1 > map3: " << (map1 > map3) << std::endl;
	std::cout << "----------" << std::endl;
	std::cout << "map1 >= map2: " << (map1 >= map2) << std::endl;
	std::cout << "map1 >= map3: " << (map1 >= map3) << std::endl;
	std::cout << "----------" << std::endl;

	std::cout << "-> swap( map1, map2 )" << std::endl;
	swap( map1, map2 );
	std::cout << "=== print map1 ===" << std::endl;
	print_map( map1 );
	std::cout << "=== print map2 ===" << std::endl;
	print_map( map2 );
}

template < class T >
struct	more
{
	bool	operator() ( const T& a, const T& b ) const { return ( a > b ); }
};

void	map_more( void )
{
	NAMESPACE::map<int,char, more<int> >	map;
	map.insert( NAMESPACE::make_pair( 1, 'a' ) );
	map.insert( NAMESPACE::make_pair( 2, 'b' ) );
	map.insert( NAMESPACE::make_pair( 3, 'c' ) );
	map.insert( NAMESPACE::make_pair( 4, 'd' ) );
	map.insert( NAMESPACE::make_pair( 5, 'e' ) );
	std::cout << "-> map = sample map with 5 elements (keys go from 1 to 5, "
		"and values from 'a' to 'e')" << std::endl
		<< "key_compare function passed to map is more<int>" << std::endl;

	std::cout << "=== print map ===" << std::endl;
	print_map( map );
}

template < class T >
struct	same
{
	bool	operator() ( const T& a, const T& b ) const { return ( a == b ); }
};

void	map_same( void )
{
	NAMESPACE::map<int,char, same<int> >	map;
	map.insert( NAMESPACE::make_pair( 1, 'a' ) );
	map.insert( NAMESPACE::make_pair( 2, 'b' ) );
	map.insert( NAMESPACE::make_pair( 3, 'c' ) );
	map.insert( NAMESPACE::make_pair( 4, 'd' ) );
	map.insert( NAMESPACE::make_pair( 5, 'e' ) );
	std::cout << "-> map = sample map with 5 elements (keys go from 1 to 5, "
		"and values from 'a' to 'e')" << std::endl
		<< "key_compare function passed to map is same<int>" << std::endl;

	std::cout << "=== print map ===" << std::endl;
	print_map( map );
}
