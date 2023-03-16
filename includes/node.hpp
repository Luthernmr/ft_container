#pragma once

#include "utils.hpp"
#include <cstddef>

namespace ft
{
	template <class T> 
	struct Node
	{
			typedef T									pair_type;
			typedef ft::pair<long int, int> 			value_type;
			typedef typename pair_type::first_type		first_type;
			typedef typename pair_type::second_type		second_type;
			typedef	ft::pair<long int, int> 			end_type;

			pair_type									_content;
			size_t 										_height;
			Node 										*_parent;
			Node 										*_lChild;
			Node 										*_rChild;


		public:
			Node(pair_type &content) : 
					_content(ft::make_pair(content.first, content.second)), _height(1), _parent(NULL), _lChild(NULL), _rChild(NULL){}
			Node(pair_type &content, Node *parent) : 
					_content(ft::make_pair(content.first, content.second)), _height(1), _parent(parent), _lChild(NULL), _rChild(NULL) {
					}


		/* --------------------------------- Getter --------------------------------- */
			pair_type					getContent() 								{return _content;};
			const pair_type&			getContent() const 							{return (_content);}
			first_type 					getFirst() const							{return (_content.first);}
			const second_type&			getSecond() const							{return ((_content.second));}
        	void						setContent(const pair_type& pair)			{_content = pair;}
        	Node*						getParent() const 							{return (_parent);}
        	void						setParent(Node* parent)						{_parent = parent;}
        	Node*						getlChild() const							{return (_lChild);}
        	void						setlChild(Node* lChild)						{_lChild = lChild;}
        	Node*						getrChild() const							{return (_rChild);}
        	void						setrChild(Node* rChild)						{_rChild = rChild;}
        	int							getHeight() const							{return (_height);}
        	void						setHeight(int height)						{_height = height;}
		
		/* -------------------------------- Surcharge ------------------------------- */
		
	};
};