#include "test/test.hpp"

int		main ( void )
{
	std::cout << "VECTOR TESTS" << std::endl << std::endl;
	vector_canonicalform();
	vector_iterator();
	vector_capacity();
	vector_elementaccess();
	vector_modifiers();
	vector_allocator();
	vector_non_member_functions();
	reverse_iterator_vector();

	stack_tests();

	std::cout << "MAP TESTS" << std::endl << std::endl;
	//pair();
	map_canonicalform();
	map_iterator();
	map_capacity();
	map_elementaccess();
	map_modifiers();
	map_observers();
	map_operations();
	map_allocator();
	map_non_member_functions();
	map_more();
	map_same();

	return ( EXIT_SUCCESS );
}
