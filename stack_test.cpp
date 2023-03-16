#include <iostream>
#include "common.hpp" 

void	s_tests( std::vector< KEY_TYPE > &rand_store);

time_t s_getms(void)
{
	struct timeval time_now;
    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
	return( msecs_time );
}

void stack_test ()
{
	std::vector< KEY_TYPE >			rand_store;
	srand(RAND_SEED);
	for (int i = 0 ; i < LIMITE ; i++)
	{	rand_store.push_back(rand());	}
	s_tests(rand_store);
}

void	s_utilities_tests( std::vector<KEY_TYPE> &rands, std::ofstream &out)
{
	STACK_TYPE st;
	out << "EMPTY"  << st.empty() << " size " << st.size() << std::endl;
	for(std::vector< KEY_TYPE>::iterator beg = rands.begin(); beg != rands.end(); beg++)
	{
		st.push(*beg);
		out << "top : " << st.top() << "size = " << st.size() << std::endl;
	}
	out << "EMPTY" << st.empty();
	STACK_TYPE st2 = st;
	out << (st == st2) << std::endl;
	st.push( KEY_TYPE() );
	out << (st > st2) << (st2 > st) << (st != st2) << (st2 != st) << (st >= st2) << (st <= st2) << std::endl;
	st.pop();
	st.pop();
	st.pop();
	out << (st > st2) << (st2 > st) << (st != st2) << (st2 != st) << (st >= st2) << (st <= st2) << std::endl;
	for(STACK_TYPE::size_type i = st.size(); i > 0; i--)
	{
		out << "poping : " << st.top() << std::endl;
		st.pop();
	}
	out << "st.size /empty : " << st.size() << " / " << st.empty() << std::endl;
	out << "st2.size /empty : " << st2.size() << " / " << st2.empty() << std::endl;
	out <<  "st2.top " << st2.top() << std::endl;
}

void	s_tests(std::vector< KEY_TYPE > &rand_store)
{
	std::time_t				start;(void ) start;
	std::time_t 			ft_stamp;(void ) ft_stamp;

	VECTOR_TYPE m;

	start = s_getms();
	std::string logdir ( TRACE_DIR_STK + std::string (NAME_NS) +"/stack_log.txt") ;
	std::ofstream out(logdir.c_str());
	s_utilities_tests(rand_store, out);
	ft_stamp = s_getms();
	ft_stamp = ft_stamp - start;
	out << " Utilities : " << NAME_NS << " Runtime = " << ft_stamp << std::endl;
}
