#ifndef TREE_H
# define TREE_H

# include <memory>
# include <iostream>
# include "iterator.hpp"
# include "tools.hpp"

namespace ft
{

/* ************************************************************************** */
/*                                                                            */
/*                        		node										  */
/*  																	      */
/* ************************************************************************** */

	template <class T>
	struct Node
	{
		T		val;
		Node *	parent;
		Node *	left;
		Node *	right;

		typedef T	value_type;

		Node(const T& val, Node *parent = 0, Node *left = 0, Node *right = 0)
			: val(val), parent(parent), left(left), right(right) 
		{}
		
		Node(const Node& rhs) : val(rhs.val), parent(rhs.parent),
								left(rhs.left), right(rhs.right)
		{}

		~Node(void) {}

		Node& operator=(const Node& rhs)
		{
			if (this != &rhs) {
				this->val = rhs.val;
				this->left = rhs.left;
				this->right = rhs.right;
				this->parent = rhs.parent;
			}
			return (*this);
		}

		Node *	inOrderSuccessor()
		{
			Node *nd = this;

			if (!nd)
				return 0;
			if (nd->right)
			{
				nd = nd->right;
				while (nd->left)
					nd = nd->left;
				return (nd);
			}

			Node * p = nd->parent;

			while (p && p->right == nd)
			{
				nd = p;
				p = p->parent;
			}
			return (p);
		}

		Node *	inOrderPredecessor()
		{
			Node *nd = this;

			if (!nd)
				return 0;
			if (nd->left)
			{
				nd = nd->left;
				while (nd->right)
					nd = nd->right;
				return (nd);
			}

			Node * p = nd->parent;

			while (p && p->left == nd)
			{
				nd = p;
				p = p->parent;
			}
			return (p);
		}
	};

/* ************************************************************************** */
/*                                                                            */
/*                        	binary tree										  */
/*  																	      */
/* ************************************************************************** */

//basic BTS, not balanced
	template <class T, class ValCompare, class NodeAlloc = std::allocator<Node<T> > >
	class Btree
	{
	public:
		typedef T										value_type;
		typedef size_t									size_type;
		typedef Node<T>									node;
		typedef Tree_iterator<node>						iterator;
		typedef Tree_iterator<const node>				const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	//canonical
		Btree() : _root(0), _size(0), _comp(ValCompare()), _nodeAlloc(NodeAlloc())
		{}

		Btree(const Btree& rhs) : _size(rhs._size),
								 _comp(rhs._comp),
								  _nodeAlloc(rhs._nodeAlloc)
		{
			this->_root = _copyNodeRecur(rhs._root);
		}

		~Btree()
		{
			this->clear();
		}

		Btree &	operator=(const Btree & rhs)
		{
			if (this != &rhs)
			{
				this->clear();
				this->_size = rhs._size;
				this->_nodeAlloc = rhs._nodeAlloc;
				this->_comp = rhs._comp;
				this->_root = _copyNodeRecur(rhs._root);
			}
			return (*this);
		}
	
	//iterators
		iterator 		begin()
		{
			return iterator(this->_leftmost());
		}

		const_iterator	begin() const
		{
			return const_iterator(this->_leftmost());
		}
	
		iterator		end()
		{
			if (_root)
				return iterator(this->_rightmost()->right);
			return (iterator(_root));
		}

		const_iterator	end() const
		{
			if (_root)
				return const_iterator(this->_rightmost()->right);
			return (_root);
		}

		reverse_iterator		rbegin() { return reverse_iterator(this->end()); }	
		const_reverse_iterator	rbegin() const { return reverse_iterator(this->end()); }
		reverse_iterator		rend() { return reverse_iterator(this->begin()); }
		const_reverse_iterator	rend() const { return reverse_iterator(this->begin()); }
	
	//capacity
		size_type size() const { return (this->_size); }
		size_type max_size() const { return (this->_nodeAlloc.max_size()); }
	
	//insertion
		ft::pair<iterator, bool> insert(const value_type& x)
		{
			node *		ret;
			size_type	tmp;

			tmp = _size;
			ret = _insert(_root, x);
			return (ft::make_pair(iterator(ret), _size != tmp));
		}

		iterator insert(iterator position, const value_type& x)
		{
			if (position && (!position->parent || _comp(x, position->parent->val)))
				return iterator(_insert(&*position, x));
			return iterator(_insert(_root, x));
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
				this->insert(*first++);
		}

	//deletion
		void erase(iterator position)
		{
			_erase(_root, *position);
		}

		size_type erase(const value_type& x)
		{
			size_type	tmp = _size;

			_erase(_root, x);
			return (tmp - _size);
		}

		void erase(iterator first, iterator last)
		{
			while (first != last)
			{
				this->erase(_root, first->val);
				first++;
			}
		}

	//other modifiers
		void swap(Btree& rhs)
		{
			if (this != &rhs)
			{
				std::swap(this->_root = rhs._root);
				std::swap(this->_size = rhs._size);
			}
		}

		void clear()
		{
			_clearNodeRecur(_root);
			_root = 0;
		}

	//operations
		iterator		find(const value_type& x)
		{
			node * ret = _find(_root, x);

			if (!ret)
				return (this->end());
			return (iterator(ret));
		}

		const_iterator	find(const value_type& x) const
		{
			node * ret = _find(_root, x);
	
			if (!ret)
				return (this->end());
			return (const_iterator(ret));
		}

	//relational operations
		friend bool operator==(const Btree<T, ValCompare, NodeAlloc>& x,
						const Btree<T, ValCompare, NodeAlloc>& y)
		{
			if (x._size == y._size)
			{
				return (ft::equal(x.begin(), x.end(), y.begin()));
			}
			return false;
		}

		friend bool operator!=(const Btree<T, ValCompare, NodeAlloc>& x,
						const Btree<T, ValCompare, NodeAlloc>& y)
		{
			return !(x == y);
		}

		friend bool operator<(const Btree<T, ValCompare, NodeAlloc>& x,
						const Btree<T, ValCompare, NodeAlloc>& y)
		{
			return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
		}

		friend bool operator>(const Btree<T, ValCompare, NodeAlloc>& x,
						const Btree<T, ValCompare, NodeAlloc>& y)
		{
			return (y < x);
		}

		friend bool operator>=(const Btree<T, ValCompare, NodeAlloc>& x,
						const Btree<T, ValCompare, NodeAlloc>& y)
		{
			return !(x < y);
		}

		friend bool operator<=(const Btree<T, ValCompare, NodeAlloc>& x,
						const Btree<T, ValCompare, NodeAlloc>& y)
		{
			return !(y < x);
		}

	private:
		node *		_root;
		size_t		_size;
		ValCompare	_comp;
		NodeAlloc	_nodeAlloc;

		node*	_insert(node * root, const value_type& val, node * parent = 0)
		{
			if (!root)
			{
				_size++;
				root = _createNode(val, parent);
				if (parent && _comp(val, parent->val))
					parent->left = root;
				else if (parent)
					parent->right = root;
				if (!_root)
					_root = root;
			}
			else if (_comp(val, root->val))
				return (_insert(root->left, val, root));
			else if (_comp(root->val, val))
				return (_insert(root->right, val, root));
			return (root);
		}

		node*	_erase(node * root, const value_type& val)
		{
			node * tmp;

			if (!root)
				return (0);
			if (_comp(root->val, val))
				_erase(root->right, val);
			else if (_comp(val, root->val))
				_erase(root->left, val);
			else if (root->left && root->right)
			{
				tmp = root->right;
				while (tmp->left)
					tmp = tmp->left;

				node * replace = _createNode(tmp->val, root->parent, root->left,
												_erase(root->right, tmp->val));
				root->left->parent = replace;
				root->right->parent = replace;
				if (root->parent && _comp(root->parent->val, root->val))
					root->parent->right = replace;
				else if (root->parent)
					root->parent->left = replace;
				else
					_root = replace;
				_clearNode(root);
			}
			else
			{
				tmp = root;
				if (root->left)
					root = root->left;
				else
					root = root->right;
				if (root)
					root->parent = tmp->parent;

				if (tmp->parent && _comp(tmp->parent->val, tmp->val))
					tmp->parent->right = root;
				else if (tmp->parent)
					tmp->parent->left = root;
				else
					_root = root;

				_clearNode(tmp);
			}
			return root;
		}

		node *	_find(node * root, const value_type& val) const
		{
			if (!root)
				return 0;
			if (_comp(val, root->val))
				return (_find(root->left, val));
			else if (_comp(root->val, val))
				return (_find(root->right, val));
			else
				return root;
		}

		node *	_leftmost() const
		{
			node * ret = _root;

			if (ret)
			{
				while (ret->left)
					ret = ret->left;
			}
			return (ret);
		}

		node *	_rightmost() const
		{
			node * ret = _root;

			if (ret)
			{
				while (ret->right)
					ret = ret->right;
			}
			return (ret);
		}

		node *	_createNode(const value_type& val, node * parent,
									node *left = 0, node *right = 0)
		{
			node *	ret;

			ret = _nodeAlloc.allocate(1);
			_nodeAlloc.construct(ret, node(val, parent, left, right));
			return (ret);
		}

		node *	_copyNodeRecur(node *root, node * parent = 0)
		{
			node * cp = 0;

			if (root)
			{
				cp = _createNode(root->val, parent,
								_copyNodeRecur(root->left, cp),
								_copyNodeRecur(root->right, cp));
			}
			return cp;
		}

		void	_clearNode(node * nd)
		{
			_nodeAlloc.destroy(nd);
			_nodeAlloc.deallocate(nd, 1);
			_size--;
		}

		void	_clearNodeRecur(node * root)
		{
			if (root)
			{
				if (root->left)
					_clearNodeRecur(root->left);
				if (root->right)
					_clearNodeRecur(root->right);
				_clearNode(root);
			}
		}
	}; //classe Btree

} //namespace ft
#endif