#include "test.hpp"

void	stack_tests ( void )
{
	std::cout << "STACK TESTS" << std::endl << std::endl;

	NAMESPACE::stack< int, NAMESPACE::vector<int> >	stack;

	std::cout << "-> stack" << std::endl;
	std::cout << "stack size = " << stack.size() << std::endl;
	std::cout << "stack empty = " << stack.empty() << std::endl;
	std::cout << "stack.push(1)" << std::endl;
	stack.push(1);
	std::cout << "stack.push(2)" << std::endl;
	stack.push(2);
	std::cout << "stack top = " << stack.top() << std::endl;
	std::cout << "stack.pop()" << std::endl;
	stack.pop();

	NAMESPACE::stack< int, NAMESPACE::vector<int> >	stack2(stack);
	std::cout << "-> stack2" << std::endl;
	std::cout << "stack2 = stack" << std::endl;
	stack2 = stack;
	std::cout << std::boolalpha;
	std::cout << "stack == stack2: " << (stack == stack2) << std::endl;
	std::cout << "stack < stack2: " << (stack < stack2) << std::endl;
	std::cout << "stack2.push(3)" << std::endl;
	stack2.push(3);
	std::cout << "stack2 == stack2: " << (stack == stack2) << std::endl;
	std::cout << "stack2 < stack2: " << (stack < stack2) << std::endl;
	std::cout << "stack size = " << stack.size() << std::endl;
	std::cout << "stack empty = " << stack.empty() << std::endl;
	std::cout << "stack top = " << stack.top() << std::endl;
	std::cout << "stack2 size = " << stack2.size() << std::endl;
	std::cout << "stack2 top = " << stack2.top() << std::endl;
}
