#include "common.hpp"

int main()
{
	std::cout << "LAUNCHING TEST OF " << NAME_NS << std::endl;
	std::cout << "MAP: testing" << std::endl;
	map_test();
	std::cout << "VECTOR: testing" << std::endl;
	vector_test();
	std::cout << "STACK: testing" << std::endl;
	stack_test();
	return(0);
}