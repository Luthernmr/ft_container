#pragma once
#include "vector.hpp"
#include <vector>

#include "map.hpp"
#include <map>

#include "stack.hpp"
#include <stack>

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sys/time.h>


#define LIMITE 120000
#define RAND_SEED	446
#define KEY_TYPE	int
#ifndef NAMESPACE
# define NAMESPACE std
# define NAME_NS	"std" 
#endif

#ifndef NAME_NS
# define NAME_NS "ft"
#endif

#define KEY_TYPE int
#define VECTOR_TYPE NAMESPACE::vector<KEY_TYPE>
#define VECTOR_ITER VECTOR_TYPE::iterator
#define VECTOR_CITER VECTOR_TYPE::const_iterator
#define TRACE_DIR_VEC	"trace/vector/"

#define	MAP_TYPE	NAMESPACE::map<KEY_TYPE,std::string >
#define	MAP_ITER	MAP_TYPE::iterator
#define	MAP_CITER	MAP_TYPE::const_iterator
#define PAIR_TYPE	NAMESPACE::pair<const KEY_TYPE, std::string >
#define TRACE_DIR_MAP	"trace/map/"

#define STACK_TYPE	NAMESPACE::stack<KEY_TYPE>
#define TRACE_DIR_STK	"trace/stack/"

void vector_test ();
void map_test ();
void stack_test ();
