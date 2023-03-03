#pragma once

#include "./pair.hpp"

#include <memory>

namespace ft
{
	template <class Pair>
	class Node
	{
		private:
			Pair 					_content;
			size_t 					_height;
			Node 					*_parent;
			Node 					*_lChild;
			Node 					*_rChild;

		public:
			Node(Pair &content) : 
					_content(content), _parent(NULL), _height(1), _lChild(NULL), _rChild(NULL) {}
			Node(Pair &content, Node *parent) : 
					_content(content), _parent(parent), _height(1), _lChild(NULL), _rChild(NULL) {}

		/* --------------------------------- Getter --------------------------------- */
			Pair 						getContent() 								{return _content;};
			const Pair&					getContent() const 							{return (_content);}
        	void						setContent(const Pair& pair)				{_content = pair;}
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