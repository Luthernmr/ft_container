#pragma once

#include <memory>
#include <stdexcept>
#include <map>
#include "../includes/pair.hpp"
#include "../includes/node.hpp"
#include "../includes/lexicographical_compare.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "../iterator/bidirectional_iterator.hpp"

namespace ft
{
	template < class Key,  class T, class Compare = std::less<Key>, class Alloc = std::allocator<Node<ft::pair<const Key, T> > > >
	class map
	{
		public:
			typedef Key 																				key_type;
        	typedef T																					mapped_type;
        	typedef ft::pair<const key_type, mapped_type> 												value_type;
        	typedef Compare 																			key_compare;
        	typedef Alloc																				allocator_type; 

		private:
			typedef	ft::Node<value_type>																node_type;
			typedef	ft::Node<value_type>*																node_ptr;
			key_compare																					_keycomp;
			node_ptr																					_end_ptr;
			size_t																						_size;
			allocator_type																				_alloc;


		public:
        	typedef typename allocator_type::reference 													reference;
        	typedef typename allocator_type::const_reference 											const_reference;
        	typedef typename allocator_type::pointer 													pointer;
        	typedef typename allocator_type::const_pointer 												const_pointer;
        	typedef typename allocator_type::size_type 													size_type;
        	typedef typename allocator_type::difference_type 											difference_type;

        	typedef typename ft::bidirectional_iterator<value_type, node_type> 							iterator;
        	typedef typename ft::bidirectional_iterator<const value_type,const node_type> 				const_iterator;

        	typedef typename ft::reverse_iterator<iterator> 											reverse_iterator;
        	typedef typename ft::reverse_iterator<const_iterator> 										const_reverse_iterator;


			
	
		public:
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
					Compare	comp;
					value_compare(Compare c) : comp(c){};
				public:
					//~value_compare();

					bool operator() (const value_type& x, const value_type& y) const
		 			{
						return comp(x.first, y.first);
					}
					
			};
			value_compare																				_valuecomp;

		
		public:

		/* ------------------------- Constructor / Destrucor ------------------------ */

			//map();
			map(const Compare& comp = key_compare(), const Alloc& alloc = allocator_type()):  _keycomp(comp), _end_ptr(NULL), _size(0), _alloc(alloc), _valuecomp(comp)
			{
				value_type tmp;
				_end_ptr = _alloc.allocate(1);	
				_alloc.construct(_end_ptr, Node<value_type>(tmp));	
			}

			template< class InputIt >
			map(InputIt first, InputIt last,const Compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):  _keycomp(comp), _end_ptr(NULL), _size(0), _alloc(alloc), _valuecomp(comp) 
			{
				value_type tmp;
				_end_ptr = _alloc.allocate(1);	
				_alloc.construct(_end_ptr, Node<value_type>(tmp));	
				insert(first,last);
			}

			map(const map& obj) : _keycomp(obj._keycomp), _size(0), _alloc(obj._alloc), _valuecomp(obj._valuecomp) 
			{

				value_type tmp;
				_end_ptr = _alloc.allocate(1);	
				_alloc.construct(_end_ptr, Node<value_type>(tmp));	
				*this = obj;
			}

			~map() {clear();}

			map& operator=(const map& obj)
			{
				clear();
				insert(obj.begin(), obj.end());
				return (*this);
			}
		
			allocator_type get_allocator() const
			{
				return (_alloc);
			}
		/* ---------------------------------- Acces --------------------------------- */


			mapped_type&			at(const Key& key) 
			{
				node_ptr node = findKey(key);
				if (!node)
					throw (std::out_of_range("out_of_range"));
				return(node->_content.second);
			}
			const mapped_type&		at(const Key& key) const 
			{
				node_ptr node = findKey(key);
				if (!node)
					throw (std::out_of_range("out_of_range"));
				return(node->_content.second);
			}
			T&			operator[](const Key& key)
			{
				iterator	it = find(key);
				if (it != end())
					return ((*it).second);
				else
					return (insert(ft::make_pair(key, T())).first->second);
			}
		
		/* -------------------------------- Capacity -------------------------------- */

			bool					empty() const 		{return (_size == 0);}
			size_type				size() const 		{return (_size);}
			size_type				max_size() const 	{return ( _alloc.max_size());}

		/* -------------------------------- Iterators ------------------------------- */

			iterator				end() 			
			{
					return (iterator(_end_ptr));
			}
			const_iterator			end() const 		
			{
					return (const_iterator(_end_ptr));
			}
			
			iterator				begin()			 	
			{
				if (!_root())
					return (iterator(_end_ptr));
				return iterator(minValue(_root()));
			}
			const_iterator			begin() const		
			{
				if (!_root())
					return (const_iterator(_end_ptr));
				return const_iterator(minValue(_root()));
			}
			reverse_iterator		rbegin() 			{return reverse_iterator(end());}
			const_reverse_iterator	rbegin() const 		{return const_reverse_iterator(end());}
			reverse_iterator		rend() 				{return reverse_iterator(begin());}
			const_reverse_iterator	rend() const 		{return const_reverse_iterator(begin());}


		/* -------------------------------- Modifier -------------------------------- */

			void					clear() 
			{
				clearTree(_root());
				_root() = NULL;
			}

			ft::pair<iterator, bool>	insert(const value_type& value) // The pair::second element (bool) in the pair is set to true if a new element was inserted or false if an equivalent element already existed.
			{
				bool tmp = false;
				node_ptr it = findKey(value.first);
				if (it == _end_ptr)
					tmp = true;
				insert_help(value);
				ft::pair<iterator, bool> pair = ft::make_pair(iterator(findKey(value.first)), tmp);
				return(pair);
			}

			iterator					insert(iterator pos, const value_type& value) 
			{
					(void)	pos;
					insert(value);
					return(findKey(value.first));
			}

			template<class InputIt>	
			void 						insert(InputIt first, InputIt last) 
			{
				while (first != last)
				{
					insert(*first);
					first++;
				}
			}

			iterator					erase(iterator pos) 
			{
				deleteNode(pos.getPtr());
				return (pos);
			}

			iterator					erase(iterator first, iterator last) 
			{
				iterator tmp = first;
				while(first != last)
				{
					++tmp;
					deleteNode(first.getPtr());
					first = tmp;
				}
				return (tmp);
			}

			size_type					erase(const Key &key) 
			{
				iterator it = findKey(key); 
				if(it != end())
				{
					deleteNode(it.getPtr());
					return (1);
				}
				return(0);
			}


			void						swap(map& other)
			{

				size_type tmp_size = _size;
				node_ptr end_l = _root();
				
				_root() = other._root();
				_size = other._size;
		
				other._root() = end_l;
				other._size = tmp_size;
				
				if (_root())
					_root()->_parent = _end_ptr;
			
				if (other._root())
					other._root()->_parent = other._end_ptr;
		
			}

		/* --------------------------------- Lookup --------------------------------- */

			size_type									count(const Key& key) const
			{
				return(find(key) != end());
			}
			iterator									find(const Key& key) 			{return (iterator(findKey(key)));}
			const_iterator								find(const Key& key) const 	
			{	
				node_ptr tmp = findKey(key);
				return (const_iterator(tmp));
			}
			ft::pair<iterator,iterator>					equal_range(const Key& key) 
			{
				return(ft::make_pair<iterator, iterator>(lower_bound(key),upper_bound(key)));
			}
			ft::pair<const_iterator, const_iterator>	equal_range(const Key& key) const
			{
				return(ft::make_pair<const_iterator, const_iterator>(lower_bound(key),upper_bound(key)));			
			}
			iterator									lower_bound(const Key& key)
			{
				iterator it = begin();
				while (it != end())
				{
					if (_keycomp(it->first, key))
						it++;
					else
						return(it);
				}
				return( it );
			}
			const_iterator								lower_bound(const Key& key) const
			{
				const_iterator it = begin();
				while (it != end())
				{
					if (_keycomp(it->first, key))
						it++;
					else
						return(it);
				}
				return( it );
			}
			iterator									upper_bound(const Key& key) 
			{
				iterator it = begin();
				while (it != end())
				{
					if (_keycomp(it->first, key) || key == it->first)
						it++;
					else
						return(it);
				}
				return( it );
			}
			const_iterator								upper_bound(const Key& key) const 
			{
				const_iterator it = begin();
				while (it != end())
				{
					if (_keycomp(it->first, key) || key == it->first)
						it++;
					else
						return(it);
				}
				return( it );
			}

		/* -------------------------------- Observer -------------------------------- */
			key_compare									key_comp() const {return (key_compare());}
			value_compare 								value_comp() const {return value_compare(key_compare());}

			/* -----------------------------------tree----------------------------------- */
			/*                                    tree                                    */
			/* -------------------------------------------------------------------------- */

			
		private :
			node_ptr	minValue(node_ptr node) const
			{
				node_ptr tmp = node;
				if (!tmp)
					return(NULL);
				while (tmp->_lChild != NULL)
					tmp = tmp->_lChild;
				return (tmp);
			}
			
			node_ptr	maxValue(node_ptr node) const
			{
				node_ptr tmp = node;
				if (!tmp)
					return(NULL);
				while (tmp->_rChild != NULL)
					tmp = tmp->_rChild;
				return (tmp);
			}
		//public: //NOTE - temp public
			void printTree(node_ptr root, std::string indent, bool last)
			{
			  if (root) {
			    std::cout << indent;
			    if (last) {
			      std::cout << "R----";
			      indent += "   ";
			    } else {
			      std::cout << "L----";
			      indent += "|  ";
			    }
			    std::cout << root->_content.first << std::endl;
			    printTree(root->_lChild, indent, false);
			    printTree(root->_rChild, indent, true);
			  }
			}

			node_ptr&	_root()
			{
				return (_end_ptr->_lChild);
			}

			node_ptr	_root() const
			{
				return (_end_ptr->_lChild);
			}
			node_ptr&	_end()
			{
				return (_end_ptr);
			}

			node_ptr	_end() const
			{
				return (_end_ptr);
			}

		/* ----------------------------- Simple Rotation ---------------------------- */
			node_ptr r_rotate(node_ptr node)
			{
				if (!node)
					return (node);
				node_ptr newRoot = node->getlChild();
				node_ptr subRnewRoot = newRoot->getrChild();
				
				if (node == _root())
					_root() = newRoot;
				
				newRoot->setrChild(node);
				newRoot->setParent(node->getParent());

				node->setlChild(subRnewRoot);
				node->setParent(newRoot);
			
				if (subRnewRoot)
					subRnewRoot->_parent = node;

				updateH(node);
				updateH(newRoot);

				return (newRoot);
			}

			node_ptr l_rotate(node_ptr node)
			{

				if (!node)
					return (node);
				node_ptr newRoot = node->getrChild();
				node_ptr subRnewRoot = newRoot->getlChild();

				if (node == _root())
					_root() = newRoot;
				
				newRoot->setlChild(node);
				newRoot->setParent(node->getParent());

				node->setrChild(subRnewRoot);
				node->setParent(newRoot);
			
				if (subRnewRoot)
					subRnewRoot->_parent = node;
				
				updateH(node);
				updateH(newRoot);
				return (newRoot);
			}

		/* --------------------------- Update node Height --------------------------- */
			void	updateH(node_ptr node)
			{
				if (!node)
					return;
				
				node->_height = 1;
				if (node->_lChild)
					node->_height = node->_lChild->_height + 1;
				if (node->_rChild)
					if (node->_rChild->_height >= node->_height)
						node->_height = node->_rChild->_height + 1;
			}

		/* -------------------------------- Balancer -------------------------------- */
			int diffH (node_ptr node)
			{
				int lh;
				int rh;
				if (!node->_lChild)
					lh = 0;
				else
					lh = node->_lChild->_height;
				if (!node->_rChild)
					rh = 0;
				else
					rh = node->_rChild->_height;
				return (lh - rh);
			}

			node_ptr balance(node_ptr node)
			{

				if (!node)
					return(NULL);
				else if (diffH(node) > 1)
				{

					if (diffH(node->_lChild) < 0)
						node->_lChild = l_rotate(node->_lChild);
					return (r_rotate(node));
				}
				else if (diffH(node) < -1)
				{
					if (diffH(node->_rChild) > 0)
						node->_rChild = r_rotate(node->_rChild);
					return (l_rotate(node));
				}

				return (node);
			}

			void clearTree(node_ptr &root)
			{
				_size = 0;
				if (!root)
					return;
 		  		if(root->_lChild)
		 			clearTree(root->_lChild);
  		 		if (root->_rChild)
		 			clearTree(root->_rChild);
				_alloc.destroy(root);
				_alloc.deallocate(root, 1);
				root = NULL;
			}

			void	insert_help(const Key& key, const mapped_type& val)
			{	
				_root() = insert_node(_root(), _end_ptr, (ft::make_pair(key, val)));
			}

			void	insert_help(const value_type pair)
			{
				_root() = insert_node(_root(), _end_ptr, pair);
			}

			node_ptr insert_node(node_ptr node,node_ptr parent, value_type pair)//
			{
				if (!node)
				{	
					node = _alloc.allocate(1);
					try{ _alloc.construct(node, Node<value_type>(pair, parent)); }
					catch(...)
					{
						_alloc.deallocate(node, 1);
						throw;
					}
					_size++;
					return (node);
				}
				if (_keycomp(node->_content.first, pair.first))
					node->_rChild = insert_node(node->_rChild,node, pair);
				else if (_keycomp(pair.first, node->_content.first))
					node->_lChild = insert_node(node->_lChild, node, pair);
				else 
					return (node);

				updateH(node);

				return (balance(node));
			}

			node_ptr findKey(const Key &key) const
			{
				return(findKey(key, _root()));
				
			}

			node_ptr findKey(const Key &key, node_ptr node) const
			{
				if (!node)
					return (_end_ptr);
				if (_keycomp(key, node->_content.first))
					return(findKey(key, node->_lChild));
				else if (_keycomp(node->_content.first, key))
					return (findKey(key, node->_rChild));
				return (node);
			}
			void	del_node(node_ptr node)
			{
				_alloc.destroy(node);
				_alloc.deallocate(node,1);
				_size--;
			}

			void	reattach(node_ptr node, node_ptr new_node)
			{
				if (node == _root())
					_root() = new_node;
				else if (node == node->_parent->_lChild)
					node->_parent->_lChild = new_node;
				else if (node == node->_parent->_rChild)
					node->_parent->_rChild = new_node;
				if (new_node != NULL)
					new_node->_parent = node->_parent;
			}

			void	balance_all(node_ptr node)
			{
				if (node == NULL)
					return ;
				//while (node != _end_ptr)//FIXME - infinit loop in tricky erase
				//{
				//	updateH(node);
				//	balance(node);
				//	node = node->_parent;
				//	std::cout << "her\n";
				//}
			}

			void deleteNode(node_ptr root)
			{
   				node_ptr temp;
				if(root == NULL)
					return;
   				if (!root->_lChild)
				{
					temp = root;
					reattach(root, root->_rChild);
					balance_all(temp);
				}
				else if (!root->_rChild)
				{
					temp = root;
					reattach(root, root->_lChild);
					balance_all(temp);
				}
   				else	
   				{
					iterator it = begin();
					while (it.getPtr() != root)
						it++;
					it++;
   				   	node_ptr newRoot = it.getPtr();
					temp = newRoot;
					if (newRoot->_parent != root)
					{
						temp = newRoot->_parent;
						reattach(newRoot, newRoot->_rChild);
						newRoot->_rChild = root->_rChild;
						newRoot->_rChild->_parent = newRoot;
					}
					reattach(root, newRoot);
					newRoot->_lChild = root->_lChild;
					newRoot->_lChild->_parent = newRoot;
					balance_all(temp);
   				}
				del_node(root);
			}
	};
	/* -------------------------------- Operator -------------------------------- */
		template<class Key, class T, class Compare, class Alloc>
		bool operator==(const map<Key, T, Compare, Alloc>& lhs,
						const map<Key, T, Compare, Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			return (equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

		template<class Key, class T, class Compare, class Alloc>
		bool operator!=(const map<Key, T, Compare, Alloc>& lhs,
						const map<Key, T, Compare, Alloc>& rhs)
		{
			return (!(lhs == rhs));
		}

		template<class Key, class T, class Compare, class Alloc>
		bool operator<(const map<Key, T, Compare, Alloc>& lhs,
						const map<Key, T, Compare, Alloc>& rhs)
		{
			return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

		template<class Key, class T, class Compare, class Alloc>
		bool operator<=(const map<Key, T, Compare, Alloc>& lhs,
						const map<Key, T, Compare, Alloc>& rhs)
		{
			return (!(rhs < lhs));
		}

		template<class Key, class T, class Compare, class Alloc>
		bool operator>(const map<Key, T, Compare, Alloc>& lhs,
						const map<Key, T, Compare, Alloc>& rhs)
		{
			return (rhs < lhs);
		}
		template<class Key, class T, class Compare, class Alloc>
		bool operator>=(const map<Key, T, Compare, Alloc>& lhs,
						const map<Key, T, Compare, Alloc>& rhs)
		{
			return (!(lhs < rhs));
		}
};