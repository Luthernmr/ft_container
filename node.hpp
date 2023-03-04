#pragma once

#include "./pair.hpp"

#include <memory>

namespace ft
{
	template <class T>
	class Node
	{
		public:
			typedef	T									pair_type;
			typedef typename pair_type::first_type		first_type;
			typedef typename pair_type::second_type		second_type;

		private:
			pair_type									_content;
			size_t 										_height;
			Node 										*_parent;
			Node 										*_lChild;
			Node 										*_rChild;

		public:
			Node(pair_type &content) : 
					_content(content), _parent(NULL), _height(1), _lChild(NULL), _rChild(NULL) {}
			Node(pair_type &content, Node *parent) : 
					_content(content), _parent(parent), _height(1), _lChild(NULL), _rChild(NULL) {}

		/* --------------------------------- Getter --------------------------------- */
			pair_type 					getContent() 								{return _content;};
			const pair_type&			getContent() const 							{return (_content);}
			first_type 					getFirst() const							{return (_content.first);}
			second_type					getSecond() const							{return (_content.second);}
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
			Node&               operator++()
        	{
        	    if (_rChild)
        	    {
        	        Node* current = _rChild;
        	        while (current->_lChild)
        	            current = current->_lChild;
        	        return (*current);
        	    }
        	    Node* current = this;
        	    Node* parent = _parent;
        	    while (parent != NULL && current == parent->_rChild)
        	    {
        	        current = parent;
        	        parent = parent->_parent;
        	    }
        	    return (*parent);
        	}
        	Node&               operator--()
        	{
        	    if (_lChild)
        	    {
        	        Node* current = _lChild;
        	        while (current->_rChild)
        	            current = current->_rChild;
        	        return (*current);
        	    }
        	    Node* current = this;
        	    Node* parent = _parent;
        	    while (parent != NULL && current == parent->_lChild)
        	    {
        	        current = parent;
        	        parent = parent->_parent;
        	    }
        	    return (*parent);
			}
	};
};