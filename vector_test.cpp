#include <iostream>
#include "common.hpp" 

void	v_Constructors(const std::vector< KEY_TYPE > &rand_store);
void	v_Deletion(std::vector< KEY_TYPE > &rand_store);
void	v_Insert(std::vector< KEY_TYPE > &rand_store);
void	v_utility(std::vector< KEY_TYPE > &rand_store);
void	v_iterators(std::vector< KEY_TYPE > &rand_store);

void	v_test_insert(std::vector< KEY_TYPE > rands, std::ofstream &out);
void	v_test_constructors( const std::vector<KEY_TYPE> &rands, std::ofstream &out);
void 	v_iterators_tests(std::vector<KEY_TYPE> &rands, std::ofstream &out);
void 	v_utilities_tests(std::vector<KEY_TYPE> &rands, std::ofstream &out);
void 	v_erases(std::vector<KEY_TYPE> &rands, std::ofstream &out);
void	v_relate_op(void );

time_t v_getms(void)
{
	struct timeval time_now;
    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
	return( msecs_time );
}
void	v_printSize(const VECTOR_TYPE& vec, std::ofstream &out, bool write)
{
	out << "Size = " << vec.size() << std::endl;
	out << "Max size = " << vec.max_size() << std::endl;
	if (write)
	{
		int i = 0;
		VECTOR_CITER beg = vec.begin();
		while(beg != vec.end())
			out << "Vector[" << i++ << "] = " << *beg++ <<std::endl; 
		out << "#######################################################################" << std::endl;
	}
}

void vector_test ()
{
	std::vector< KEY_TYPE >			rand_store;
	srand(RAND_SEED);
	for (int i = 0 ; i < LIMITE ; i++)
	{	rand_store.push_back(rand());	}
	v_Constructors(rand_store);
	v_Insert(rand_store);
	v_Deletion(rand_store); 
	v_iterators(rand_store);
	v_utility(rand_store);
	v_relate_op();
}



void	v_iterators(std::vector< KEY_TYPE > &rand_store)
{
	std::time_t				start;(void ) start;
	std::time_t 			ft_stamp;(void ) ft_stamp;

	VECTOR_TYPE m;

	start = v_getms();
	std::string logdir ( TRACE_DIR_VEC + std::string (NAME_NS) +"/iterators_log.txt") ;
	std::ofstream out(logdir.c_str());
	v_iterators_tests(rand_store, out);
	ft_stamp = v_getms();
	ft_stamp = ft_stamp - start;
	out << " Iterators : " << NAME_NS << " Runtime = " << ft_stamp << std::endl;
}

void	v_utility(std::vector< KEY_TYPE > &rand_store)
{
	std::time_t				start;(void ) start;
	std::time_t 			ft_stamp;(void ) ft_stamp;

	VECTOR_TYPE m;

	start = v_getms();
	std::string logdir ( TRACE_DIR_VEC + std::string (NAME_NS) +"/utilities_log.txt") ;
	std::ofstream out(logdir.c_str());
	v_utilities_tests(rand_store, out);
	ft_stamp = v_getms();
	ft_stamp = ft_stamp - start;
	out << " Utilities : " << NAME_NS << " Runtime = " << ft_stamp << std::endl;
}

void	v_Deletion(std::vector< KEY_TYPE > &rand_store)
{
	std::time_t				start;(void ) start;
	std::time_t 			ft_stamp;(void ) ft_stamp;

	start = v_getms();
	std::string logdir ( TRACE_DIR_VEC + std::string (NAME_NS) +"/delete_log.txt") ;
	std::ofstream out(logdir.c_str());
	v_erases(rand_store, out);
	ft_stamp = v_getms();
	ft_stamp = ft_stamp - start;
	out << " Deletion : " << NAME_NS << " Runtime = " << ft_stamp << std::endl;
}

void	v_Constructors( const std::vector< KEY_TYPE > &rand_store)
{
	std::time_t				start;(void ) start;
	std::time_t 			ft_stamp;(void ) ft_stamp;

	start = v_getms();
	std::string logdir ( TRACE_DIR_VEC + std::string (NAME_NS) +"/construct_log.txt") ;
	std::ofstream out(logdir.c_str());
	v_test_constructors( rand_store, out );
	ft_stamp = v_getms();
	ft_stamp = ft_stamp - start;
	out << " Constructors : " << NAME_NS << " Runtime = " << ft_stamp << std::endl;
}

void	v_Insert(std::vector< KEY_TYPE > &rand_store)
{
	std::time_t				start;(void ) start;
	std::time_t 			ft_stamp;(void ) ft_stamp;

	start = v_getms();
	std::string logdir ( TRACE_DIR_VEC + std::string (NAME_NS) +"/insert_log.txt") ;
	std::ofstream out(logdir.c_str());
	v_test_insert(rand_store, out);
	ft_stamp = v_getms();
	ft_stamp = ft_stamp - start;
	out << " Insert : " << NAME_NS << " Runtime = " << ft_stamp << std::endl;
}

void v_iterators_tests(std::vector<KEY_TYPE> &rands, std::ofstream &out)
{
	VECTOR_TYPE ns_rand;
	for (std::vector<KEY_TYPE >::iterator beg = rands.begin(); beg != rands.end(); beg++)
		ns_rand.push_back(*beg);
	VECTOR_TYPE m;
	m.insert(m.begin(), ns_rand.begin(), ns_rand.end());
	VECTOR_ITER m_beg = m.begin();
	VECTOR_TYPE other_way(m);
	NAMESPACE::vector<KEY_TYPE>::reverse_iterator o_rbeg = other_way.rbegin();
	for (;m_beg != m.end() && o_rbeg != other_way.rend(); m_beg++)
	{
		if (*m_beg != *o_rbeg)	
			out << *m_beg << " values aren't equal " << *o_rbeg << std::endl;
		o_rbeg++;
	}
	VECTOR_TYPE::const_reverse_iterator m_rbeg( m.rbegin() );
	NAMESPACE::vector<KEY_TYPE>::const_iterator o_beg( other_way.begin());
	for (; o_beg != other_way.end() && m_rbeg != m.rend() ;o_beg++)
	{
		if (*o_beg != *m_rbeg)	
			out << *o_beg << " values didn't match " << *m_rbeg << std::endl;
		m_rbeg++;
	}
}

void	v_defaults( std::ofstream &out)
{
	out << "Default Constructors" << std::endl;
	VECTOR_TYPE t1;
	const VECTOR_TYPE t2;
	v_printSize(t1, out, 1);
	out << "Empty test : " << t1.empty() <<std::endl;
	t1.push_back( 42 );
	out << "Empty test : " << t1.empty() <<std::endl;
	v_printSize(t2, out, 1);
}

VECTOR_TYPE	v_iterators (const std::vector<KEY_TYPE > &rands, std::ofstream &out)
{
	out << "Range Constructor" << std::endl;
	const VECTOR_TYPE m (rands.begin(), rands.end());
	v_printSize(m, out , 1);
	return (m);
}
void	v_test_constructors( const std::vector<KEY_TYPE> &rands, std::ofstream &out)
{
	v_defaults(out);
	out << "###############################################################################"<< std::endl;
	VECTOR_TYPE tmp = v_iterators(rands, out );
	out << "###############################################################################"<< std::endl;
	out << "Copy Constructor" << std::endl;
	VECTOR_TYPE cpy(tmp);
	VECTOR_TYPE cpy2 = tmp;
	v_printSize(cpy, out , 1);
	out << "Empty test : " << cpy.empty() <<std::endl;
	v_printSize(cpy2, out , 1);
	out << "Empty test : " << cpy2.empty() <<std::endl;
	out << "###############################################################################"<< std::endl;
}

void v_erases(std::vector<KEY_TYPE > &rands, std::ofstream &out)
{
	VECTOR_TYPE m;
	out << "Range Constructor" << std::endl;
	VECTOR_TYPE tmp;
	for (std::vector<KEY_TYPE >::iterator beg = rands.begin(); beg != rands.end(); beg++)
		tmp.push_back(*beg);
	m.insert(m.begin(),tmp.begin(), tmp.end());
	out << "BEFORE DELETION" << std::endl;
	v_printSize(m, out, 1);
	m.erase(++m.begin());
	VECTOR_ITER beg = m.begin();
	for(VECTOR_TYPE::size_type i = 0; i < m.size() / 2; i++)
		beg++;
	m.erase(m.begin(), beg);
	out << "After every deletion" << std::endl;
	v_printSize(m, out, 1);
	m.clear();
	out << "Empty? : " << m.empty() << std::endl;
	out << "After Clear" << std::endl;
	v_printSize(m, out, 1);
	out << "Capacity = "<< m.capacity() << std::endl;
}

void v_utilities_tests(std::vector<KEY_TYPE> &rands, std::ofstream &out)
{
	VECTOR_TYPE m;
	VECTOR_TYPE mp;
	VECTOR_TYPE ns_rands;
	for(std::vector<KEY_TYPE>::iterator beg = rands.begin(); beg != rands.end(); beg++)
		ns_rands.push_back(*beg);
	out << "SWAP" << std::endl;
	m.insert(m.begin(), ns_rands.begin(), ns_rands.end());
	for(int i = 0; i < 10 ;i++)
		mp.push_back(i);
	VECTOR_CITER m_beg = m.begin();
	VECTOR_CITER mp_beg = mp.begin();
	out << "BEFORE SWAP" << std::endl << "m : " << std::endl;

	v_printSize(m,out,1);
	for(VECTOR_TYPE::size_type i = 0; i < m.size();i++)
		out << "m[" << i << "] = " << m[i] <<" = " << m.at(i) << std::endl;
	out << "mp : " << std::endl;
	v_printSize(mp,out,1);

	m.swap(mp);

	out << "AFTER SWAP" << std::endl << "m : " << std::endl;

	v_printSize(m,out,1);
	out << "mp : " << std::endl;
	v_printSize(mp,out,1);
	out << "ITER validity" << std::endl;
	out << (m_beg == mp.begin()) << std::endl;
	out << *(++m_beg) << std::endl;
	out << (mp_beg == m.begin()) << std::endl;
	out << *(++mp_beg) << std::endl;
	mp.resize( 10 );
	m.resize(12);
	out << "NON-MEMBER SWAP :" << std::endl;
	swap(m, mp);
	v_printSize(m,out,1);
	out << "mp : " << std::endl;
	v_printSize(mp,out,1);
	out << "ITER validity" << std::endl;
	out << (m_beg == mp.begin()) << std::endl;
	out << *(++m_beg) << std::endl;
	out << (mp_beg == m.begin()) << std::endl;
	out << *(++mp_beg) << std::endl;
	NAMESPACE::vector< char > tmp;
	for(char c = 'a'; c < 'z'; c++)
		tmp.push_back(c);
	out << "Capacity: " << tmp.capacity() << " data = " << tmp.data() << std::endl;
}

void	v_test_insert(std::vector< KEY_TYPE > rands, std::ofstream &out)
{
	VECTOR_TYPE ns_rands;
	for(std::vector<KEY_TYPE>::iterator beg = rands.begin(); beg != rands.end(); beg++)
		ns_rands.push_back(*beg);
	VECTOR_TYPE vec;
	vec.assign(7, ns_rands[LIMITE / 2]);
	v_printSize(vec,out,1);
	vec.pop_back();
	v_printSize(vec,out,1);
	vec.assign(rands.begin(),rands.end());
	v_printSize(vec,out,1);
	out << "ACCESS: " << vec.front() << " = " << vec.at(0) <<  " - " << vec.back() << std::endl;
	VECTOR_ITER beg = vec.begin();
	vec.insert(beg,KEY_TYPE());
	vec.insert(vec.end(), 8, 12);
	vec.insert(vec.end(), rands.begin(), rands.begin()++);
}
template <class VECTOR>
void	v_cmp(const VECTOR &lhs, const VECTOR &rhs, std::ofstream &out)
{
	static int i = 0;

	out << "############### [" << i++ << "] ###############"  << std::endl;
	out << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	out << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	out << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

void		v_relate_op(void )
{
	VECTOR_TYPE mp1;
	VECTOR_TYPE mp2;
	std::time_t				start;(void ) start;
	std::time_t 			ft_stamp;(void ) ft_stamp;

	start = v_getms();
	std::string logdir ( TRACE_DIR_VEC + std::string (NAME_NS) +"/relation_log.txt") ;
	std::ofstream out(logdir.c_str());
	for(KEY_TYPE i = 0; i < 10; i++)
	{
		mp1.push_back(i);
		mp2.push_back(i);
	}

	v_cmp(mp1, mp1, out); // 0
	v_cmp(mp1, mp2, out); // 1

	for(KEY_TYPE i = 10; i < 15; i++)
	{	mp2.push_back(i);}

	v_cmp(mp1, mp2, out); // 2
	v_cmp(mp2, mp1, out); // 3

	swap(mp1, mp2);
	v_cmp(mp1, mp2, out); // 6
	v_cmp(mp2, mp1, out); // 7

	ft_stamp = v_getms();
	ft_stamp = ft_stamp - start;
	out << " Relations : " << NAME_NS << " Runtime = " << ft_stamp << std::endl;
}