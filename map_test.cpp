#include "common.hpp" 

void	Constructors(std::vector< KEY_TYPE > &rand_store);
void	Deletion(std::vector< KEY_TYPE > &rand_store);
void	Insert(std::vector< KEY_TYPE > &rand_store);
void	utility(std::vector< KEY_TYPE > &rand_store);
void	iterators(std::vector< KEY_TYPE > &rand_store);

void	test_insert(std::vector< KEY_TYPE > rands, std::ofstream &out);
void 	test_constructors(std::vector<KEY_TYPE> &rands, std::ofstream &out);
void 	iterators_tests(std::vector<KEY_TYPE> &rands, std::ofstream &out);
void 	utilities_tests(std::vector<KEY_TYPE> &rands, std::ofstream &out);
void 	erases(std::vector<KEY_TYPE> &rands, std::ofstream &out);
void	relate_op(void );

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp,std::ofstream &out, bool print_content = 1)
{
	out << "size: " << mp.size() << std::endl;
	out << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		out << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
		{
			out << "- " << printPair(it, false, out) << std::endl;
		}
	}
	out << "###############################################" << std::endl;
}

time_t getms(void)
{
	struct timeval time_now;
    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
	return( msecs_time );
}

void map_test()
{
	std::vector< KEY_TYPE >			rand_store;
	NAMESPACE::map<float, const char *> test;
	NAMESPACE::map<double, const char *> test2;
	NAMESPACE::map<std::string, const char *> test3;
	srand(RAND_SEED);
	for (int i = 0 ; i < LIMITE ; i++)
	{	rand_store.push_back(rand());	}
	Constructors(rand_store);
	Insert(rand_store);
	Deletion(rand_store); 
	iterators(rand_store);
	utility(rand_store);
	relate_op();
}

void	iterators(std::vector< KEY_TYPE > &rand_store)
{
	std::time_t				start;(void ) start;
	std::time_t 			ft_stamp;(void ) ft_stamp;

	MAP_TYPE m;

	start = getms();
	std::string logdir ( TRACE_DIR_MAP + std::string (NAME_NS) +"/iterators_log.txt") ;
	std::ofstream out(logdir.c_str());
	iterators_tests(rand_store, out);
	ft_stamp = getms();
	ft_stamp = ft_stamp - start;
	out << " Iterators : " << NAME_NS << " Runtime = " << ft_stamp << std::endl;
}

void	utility(std::vector< KEY_TYPE > &rand_store)
{
	std::time_t				start;(void ) start;
	std::time_t 			ft_stamp;(void ) ft_stamp;

	MAP_TYPE m;

	start = getms();
	std::string logdir ( TRACE_DIR_MAP + std::string (NAME_NS) +"/utilities_log.txt") ;
	std::ofstream out(logdir.c_str());
	utilities_tests(rand_store, out);
	ft_stamp = getms();
	ft_stamp = ft_stamp - start;
	out << " Utilities : " << NAME_NS << " Runtime = " << ft_stamp << std::endl;
}

void	Deletion(std::vector< KEY_TYPE > &rand_store)
{
	std::time_t				start;(void ) start;
	std::time_t 			ft_stamp;(void ) ft_stamp;

	start = getms();
	std::string logdir ( TRACE_DIR_MAP + std::string (NAME_NS) +"/delete_log.txt") ;
	std::ofstream out(logdir.c_str());
	erases(rand_store, out);
	ft_stamp = getms();
	ft_stamp = ft_stamp - start;
	out << " Deletion : " << NAME_NS << " Runtime = " << ft_stamp << std::endl;
}

void	Constructors(std::vector< KEY_TYPE > &rand_store)
{
	std::time_t				start;(void ) start;
	std::time_t 			ft_stamp;(void ) ft_stamp;

	start = getms();
	std::string logdir ( TRACE_DIR_MAP + std::string (NAME_NS) +"/construct_log.txt") ;
	std::ofstream out(logdir.c_str());
	test_constructors( rand_store, out );
	ft_stamp = getms();
	ft_stamp = ft_stamp - start;
	out << " Constructors : " << NAME_NS << " Runtime = " << ft_stamp << std::endl;
}

void	Insert(std::vector< KEY_TYPE > &rand_store)
{
	std::time_t				start;(void ) start;
	std::time_t 			ft_stamp;(void ) ft_stamp;

	start = getms();
	std::string logdir ( TRACE_DIR_MAP + std::string (NAME_NS) +"/insert_log.txt") ;
	std::ofstream out(logdir.c_str());
	test_insert(rand_store, out);
	ft_stamp = getms();
	ft_stamp = ft_stamp - start;
	out << " Insert : " << NAME_NS << " Runtime = " << ft_stamp << std::endl;
}

void iterators_tests(std::vector<KEY_TYPE> &rands, std::ofstream &out)
{
	std::vector<PAIR_TYPE> pr;
	for (std::vector<int >::iterator beg = rands.begin(); beg != rands.end(); beg++)
		pr.push_back(PAIR_TYPE(*beg, std::string("RANGE Constructor")));
	MAP_TYPE m;
	NAMESPACE::map<KEY_TYPE,std::string, std::greater<KEY_TYPE> > other_way;
	m[rands[LIMITE / 24 ]] = "This one isn't a match";
	for(std::vector<PAIR_TYPE>::iterator beg = pr.begin(); beg != pr.end(); beg++)
	{
		m.insert(*beg);
		other_way.insert(*beg);
	}
	MAP_ITER m_beg = m.begin();
	NAMESPACE::map<KEY_TYPE,std::string, std::greater<KEY_TYPE> >::reverse_iterator o_rbeg = other_way.rbegin();
	for (;m_beg != m.end() && o_rbeg != other_way.rend(); m_beg++)
	{
		if (*m_beg != *o_rbeg)	
			out << m_beg->first << " Pairs didn't match " << o_rbeg->first << std::endl;
		// else
		// 	out << m_beg->first << " Pairiter_tests " << o_rbeg->first << std::endl;
		o_rbeg++;
	}
	MAP_TYPE::const_reverse_iterator m_rbeg( m.rbegin() );
	NAMESPACE::map<KEY_TYPE,std::string, std::greater<KEY_TYPE> >::const_iterator o_beg( other_way.begin());
	for (; o_beg != other_way.end() && m_rbeg != m.rend() ;o_beg++)
	{
		if (*o_beg != *m_rbeg)	
			out << o_beg->first << " Pairs didn't match " << m_rbeg->first << std::endl;
		// else
		// 	out << o_beg->first << " Pairs matched " << m_rbeg->first << std::endl;
		m_rbeg++;
	}
}

void	defaults( std::ofstream &out)
{
	out << "Default Constructors" << std::endl;
	MAP_TYPE t1;
	const MAP_TYPE t2;
	printSize(t1, out, 1);
	out << "Empty test : " << t1.empty() <<std::endl;
	printSize(t2, out, 1);
	out << "Empty test : " << t2.empty() <<std::endl;
}

MAP_TYPE	iterators (std::vector<int > &rands, std::ofstream &out)
{
	out << "Range Constructor" << std::endl;
	std::vector<PAIR_TYPE> tmp;
	for (std::vector<int >::iterator beg = rands.begin(); beg != rands.end(); beg++)
		tmp.push_back(PAIR_TYPE(*beg, std::string("RANGE Constructor")));
	MAP_TYPE m (tmp.begin(), tmp.end());
	printSize(m, out , 1);
	return (m);
}
void	test_constructors( std::vector<int > &rands, std::ofstream &out)
{
	defaults(out);
	out << "###############################################################################"<< std::endl;
	MAP_TYPE tmp = iterators(rands, out );
	out << "###############################################################################"<< std::endl;
	out << "Copy Constructor" << std::endl;
	MAP_TYPE cpy(tmp);
	MAP_TYPE cpy2 = tmp;
	printSize(cpy, out , 1);
	out << "Empty test : " << cpy.empty() <<std::endl;
	printSize(cpy2, out , 1);
	out << "Empty test : " << cpy2.empty() <<std::endl;
	out << "###############################################################################"<< std::endl;
}



void erases(std::vector<int> &rands, std::ofstream &out)
{
	MAP_TYPE m;
	out << "Range Constructor" << std::endl;
	std::vector<PAIR_TYPE> tmp;
	for (std::vector<int >::iterator beg = rands.begin(); beg != rands.end(); beg++)
		tmp.push_back(PAIR_TYPE(*beg, std::string("RANGE Constructor")));
	m.insert(tmp.begin(), tmp.end());
	out << "BEFORE DELETION" << std::endl;
	printSize(m, out, 1);
	m.erase(++m.begin());
	m.erase(rands[LIMITE / 2]);
	for (int i = LIMITE / 4 ; i< LIMITE / 2 ; i++)
	{
		// if (i % 3)
			out << "Erasing[" << rands[i] << "] = " << m.erase(rands[i])<< std::endl;
	}
	MAP_ITER beg = m.begin();
	for(int i = 0; i < LIMITE / 6;i++ )
		beg++;
	m.erase(m.begin(), beg);
	out << "After every deletion" << std::endl;
	printSize(m, out, 1);
	m.clear();
	out << "After Clear" << std::endl;
	printSize(m, out, 1);

}

void utilities_tests(std::vector<KEY_TYPE> &rands, std::ofstream &out)
{

	std::vector<PAIR_TYPE> pr;
	for (std::vector<int >::iterator beg = rands.begin(); beg != (rands.begin() + 10); beg++)
		pr.push_back(PAIR_TYPE(*beg, std::string("Random inserts")));
	MAP_TYPE m;
	MAP_TYPE mp;
	NAMESPACE::map<KEY_TYPE,std::string, std::greater<KEY_TYPE> > other_way;
	out << "comp less :" << m.key_comp()(1,2) << " comp greater: "<< other_way.key_comp()(1,2) << std::endl;
	
	out << " Value comp less :" << m.value_comp()(*pr.begin(),*(++pr.begin())) << " Value comp greater: "<< other_way.value_comp()(*pr.begin(),*(++pr.begin())) << std::endl;
	out << "SWAP" << std::endl;
	for(std::vector<PAIR_TYPE>::iterator beg = pr.begin(); beg != pr.end(); beg++)
		m.insert(*beg);
	MAP_CITER m_beg = m.begin();
	for(int i = 0; i< 10; i++)
		mp[i] = "Ordered creation";
	MAP_CITER mp_beg = mp.begin();
	out << "BEFORE SWAP" << std::endl << "m : " << std::endl;

	printSize(m,out,1);
	out << "mp : " << std::endl;
	printSize(mp,out,1);

	m.swap(mp);

	out << "AFTER SWAP" << std::endl << "m : " << std::endl;

	printSize(m,out,1);
	out << "mp : " << std::endl;
	printSize(mp,out,1);
	out << "ITER validity" << std::endl;
	out << (m_beg == mp.begin()) << std::endl;
	out << (mp_beg == m.begin()) << std::endl;

	MAP_ITER find = m.find(7);
	if (find != m.end())
		out << "Find(7) has found - " << printPair(find, false, out) << std::endl;
	else
		out << "DIDN't find(7)" << std::endl;
	find = m.find(rands[ LIMITE / 18]);
	if (find != m.end())
		out << "Find(" << rands[LIMITE / 18] << ") has found - " << printPair(find, false, out) << std::endl;
	else
		out << "DIDN't find("<< rands[LIMITE / 18] << ") in m" << std::endl;
	
	MAP_CITER low = m.lower_bound(2);
	MAP_CITER up = m.upper_bound(8);
	out << "lower :  "<< printPair(low, false, out) << std::endl << "upper : " << printPair(up, false, out) << std::endl;
	out << "Count " << mp.count(17) << ' ' << mp.count(mp.begin()->first) << std::endl; 

}
void	test_insert(std::vector< KEY_TYPE > rands, std::ofstream &out)
{
	MAP_TYPE _m;
	std::vector<PAIR_TYPE> tmp;
	for (int i = 0; i < 5 ;i++)
		tmp.push_back(PAIR_TYPE(i, std::string("RANGE INSERT")));
	std::vector< KEY_TYPE >::iterator beg = rands.begin();
	while (beg != rands.end())
	{
		if (*beg % 3 )
			_m[*beg] = "Bracket insert";
		else
			_m.insert(PAIR_TYPE(*beg, "PAIR INSERT"));
		beg++;
	}
	_m.insert(tmp.begin(),tmp.end());
	MAP_ITER hint(_m.begin());
	hint = _m.begin();
	for( int i = 0; i < LIMITE / 4 && hint != _m.end(); i++)
		hint++;
	_m.insert(hint, PAIR_TYPE((hint->first ) + LIMITE/4, "HINT INSERT"));
	printSize( _m, out, 1);
}

template <class MAP>
void	cmp(const MAP &lhs, const MAP &rhs, std::ofstream &out)
{
	static int i = 0;

	out << "############### [" << i++ << "] ###############"  << std::endl;
	out << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	out << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	out << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

void		relate_op(void )
{
	MAP_TYPE mp1;
	MAP_TYPE mp2;
	std::time_t				start;(void ) start;
	std::time_t 			ft_stamp;(void ) ft_stamp;

	start = getms();
	std::string logdir ( TRACE_DIR_MAP + std::string (NAME_NS) +"/relation_log.txt") ;
	std::ofstream out(logdir.c_str());
	mp1['a'] = 2; mp1['b'] = 3; mp1['c'] = 4; mp1['d'] = 5;
	mp2['a'] = 2; mp2['b'] = 3; mp2['c'] = 4; mp2['d'] = 5;

	cmp(mp1, mp1, out); // 0
	cmp(mp1, mp2, out); // 1

	mp2['e'] = 6; mp2['f'] = 7; mp2['h'] = 8; mp2['h'] = 9;

	cmp(mp1, mp2, out); // 2
	cmp(mp2, mp1, out); // 3

	(++(++mp1.begin()))->second = 42;

	cmp(mp1, mp2, out); // 4
	cmp(mp2, mp1, out); // 5

	swap(mp1, mp2);
	cmp(mp1, mp2, out); // 6
	cmp(mp2, mp1, out); // 7

	ft_stamp = getms();
	ft_stamp = ft_stamp - start;
	out << " Relations : " << NAME_NS << " Runtime = " << ft_stamp << std::endl;
}
