#include "vector.hpp"
#include "iostream"
#include "iterator/random_acces_iterator.hpp"
#include "iterator/reverse_iterator.hpp"
#include "iterator/bidirectional_iterator.hpp"

int main()
{
	std::vector<int> test;
	std::vector<int>::iterator it = test.begin();
	std::cout << "here\n";
	std::cout << *it;
}