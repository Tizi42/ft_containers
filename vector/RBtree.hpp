#ifndef FT_RBTREE_H
# define FT_RBTREE_H

# include <memory>
# include <iostream>
# include <algorithm>
# include "iterator.hpp"
# include "tools.hpp"

namespace ft
{
/* ************************************************************************** */
/*                                                                            */
/*                        	binary tree										  */
/*  																	      */
/* ************************************************************************** */

//basic BTS, not balanced
	template <class T, class ValCompare, class Alloc = std::allocator<T> >
	class RBtree
	{
	public:
/* ************************************************************************** */
/*                                                                            */
/*                        		node										  */
/*  																	      */
/* ************************************************************************** */

	enum Color { Black, Red };

	struct Node
	{
		T		val;
		Node *	parent;
		Node *	left;
		Node *	right;
		Color	color;

		Node(const T& val, Node *parent = 0, Node *left = 0, Node *right = 0,
				Color color = Red)
			: val(val), parent(parent), left(left), right(right), color(color)
		{}
		
		Node(const Node& rhs) : val(rhs.val), parent(rhs.parent),
								left(rhs.left), right(rhs.right), color(rhs.color)
		{}

		~Node(void)
		{}

		Node& operator=(const Node& rhs)
		{
			if (this != &rhs) {
				this->val = rhs.val;
				this->left = rhs.left;
				this->right = rhs.right;
				this->parent = rhs.parent;
				this->color = rhs.color;
			}
			return (*this);
		}

		T *		valptr()
		{
			return (&val);
		}

		Node *	inOrderSuccessor()
		{
			Node * nd = this;

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

		const Node *	inOrderSuccessor() const
		{
			const Node * nd = this;

			if (!nd)
				return 0;
			if (nd->right)
			{
				nd = nd->right;
				while (nd->left)
					nd = nd->left;
				return (nd);
			}

			const Node * p = nd->parent;

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

		const Node *	inOrderPredecessor() const
		{
			const Node *nd = this;

			if (!nd)
				return 0;
			if (nd->left)
			{
				nd = nd->left;
				while (nd->right)
					nd = nd->right;
				return (nd);
			}

			const Node * p = nd->parent;

			while (p && p->left == nd)
			{
				nd = p;
				p = p->parent;
			}
			return (p);
		}
	}; //struct Node

/* ************************************************************************** */
/*                                                                            */
/*                         Tree_iterator			  		 				  */
/*  																	      */
/* ************************************************************************** */

	template <typename Ty, bool ConstType = false>
	class Tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{

	public:
		typedef	Ty															value_type;
		typedef ft::iterator<ft::bidirectional_iterator_tag, value_type>	Iterator;
		typedef typename iterator_traits<Iterator>::difference_type			difference_type;
		typedef typename iterator_traits<Iterator>::pointer					pointer;
		typedef typename iterator_traits<Iterator>::reference				reference;
		typedef typename iterator_traits<Iterator>::iterator_category		iterator_category;

	//canonical
		Tree_iterator(void) : _base() {}

		Tree_iterator(Node * it) : _base(it) {}

		Tree_iterator(const Tree_iterator& rhs) : _base(rhs._base) {}

		Tree_iterator &operator=(const Tree_iterator& rhs)
		{
			if (this != &rhs)
				this->_base = rhs._base;
			return (*this);
		}

		~Tree_iterator() {}

	//member funcs
		reference operator*(void)
		{
			return (_base->val);
		}

		const reference operator*(void) const
		{
			return (_base->val);
		}

		pointer operator->(void)
		{
			return &(this->operator*());
		}

		const pointer operator->(void) const
		{
			return &(this->operator*());
		}

		Tree_iterator& operator++(void)
		{
			_base = _base->inOrderSuccessor();
			return (*this);
		}

		Tree_iterator operator++(int)
		{
			Tree_iterator it(*this);
			operator++();
			return (it);
		}

		Tree_iterator& operator--(void)
		{
			_base = _base->inOrderPredecessor();
			return (*this);
		}

		Tree_iterator operator--(int)
		{
			Tree_iterator it(*this);
			operator--();
			return (it);
		}

		operator Tree_iterator<const Ty, true> ()
		{
			return (Tree_iterator<const Ty, true>(this->_base));
		}

		Node *	base() const 
		{
			return (this->_base);
		}

		template<typename T1, typename T2, bool B1, bool B2>
		friend bool	operator==(const Tree_iterator<T1, B1> lhs,
					const Tree_iterator<T2, B2> rhs)
		{
			return (lhs.base() == rhs.base());
		}

		template<typename T1, typename T2, bool B1, bool B2>
		friend bool	operator!=(const Tree_iterator<T1, B1> lhs,
					const Tree_iterator<T2, B2> rhs)
		{
			return (lhs.base() != rhs.base());
		}

		private:
			Node * _base;
	}; //class Tree_iterator

/* ************************************************************************** */
/*                                                                            */
/*                        	tree part 										  */
/*  																	      */
/* ************************************************************************** */
	public:
		typedef T										value_type;
		typedef size_t									size_type;
		typedef Node									node;
		typedef Tree_iterator<T, false>					iterator;
		typedef Tree_iterator<const T, true>			const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		typedef typename Alloc::template rebind<Node >::other NodeAlloc;

	//canonical
		RBtree() : _root(0), _size(0),
					_comp(ValCompare()),
					_nodeAlloc(NodeAlloc())
		{
			_end = _createNode(value_type(), 0, 0, 0);
		}

		RBtree(const RBtree& rhs) : _size(rhs._size),
								 _comp(rhs._comp),
								  _nodeAlloc(rhs._nodeAlloc)
		{
			this->_end = _copyNodeRecur(rhs._end);
			this->_root = this->_end->left;
		}

		~RBtree()
		{
			this->clear();
			_nodeAlloc.destroy(_end);
			_nodeAlloc.deallocate(_end, 1);
		}

		RBtree &	operator=(const RBtree & rhs)
		{
			if (this != &rhs)
			{
				this->clear();
				this->_size = rhs._size;
				this->_nodeAlloc = rhs._nodeAlloc;
				this->_comp = rhs._comp;
				this->_end = _copyNodeRecur(rhs._end);
				this->_root = this->_end->left;
			}
			return (*this);
		}
	
	//iterators
		iterator 		begin()
		{
			if (this->_size == 0)
				return (_end);
			return iterator(this->_leftmost());
		}

		const_iterator	begin() const
		{
			if (this->_size == 0)
				return (_end);
			return const_iterator(this->_leftmost());
		}
	
		iterator		end()
		{
			return iterator(_end);
		}

		const_iterator	end() const
		{
			return const_iterator(_end);
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
			(void)position;
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
			if (position != this->end())
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
				this->erase(*first++);
			}
		}

	//other modifiers
		void swap(RBtree& rhs)
		{
			if (this != &rhs)
			{
				ft::swap(this->_root, rhs._root);
				ft::swap(this->_end, rhs._end);
				ft::swap(this->_size, rhs._size);
				ft::swap(this->_nodeAlloc, rhs._nodeAlloc);
			}
		}

		void clear()
		{
			_clearNodeRecur(_root);
			_end->left = 0;
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
		friend bool operator==(const RBtree<T, ValCompare, Alloc>& x,
						const RBtree<T, ValCompare, Alloc>& y)
		{
			if (x._size == y._size)
			{
				return (ft::equal(x.begin(), x.end(), y.begin()));
			}
			return false;
		}

		friend bool operator!=(const RBtree<T, ValCompare, Alloc>& x,
						const RBtree<T, ValCompare, Alloc>& y)
		{
			return !(x == y);
		}

		friend bool operator<(const RBtree<T, ValCompare, Alloc>& x,
						const RBtree<T, ValCompare, Alloc>& y)
		{
			return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
		}

		friend bool operator>(const RBtree<T, ValCompare, Alloc>& x,
						const RBtree<T, ValCompare, Alloc>& y)
		{
			return (y < x);
		}

		friend bool operator>=(const RBtree<T, ValCompare, Alloc>& x,
						const RBtree<T, ValCompare, Alloc>& y)
		{
			return !(x < y);
		}

		friend bool operator<=(const RBtree<T, ValCompare, Alloc>& x,
						const RBtree<T, ValCompare, Alloc>& y)
		{
			return !(y < x);
		}

	private:
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
				{
					_root = root;
					_end->left = _root;
					_root->parent = _end;
				}
				_insertFix(root);
			}
			else if (_comp(val, root->val))
				return (_insert(root->left, val, root));
			else if (_comp(root->val, val))
				return (_insert(root->right, val, root));
			return (root);
		}

		void	_insertFix(node * x)
		{
			while (x != _root && x->parent->color == Red)
			{
				node * gdparent = x->parent->parent;
				if (x->parent == gdparent->left) //parent if the left child of grand-parent
				{
					node * uncle = gdparent->right;
					if (uncle && uncle->color == Red) //uncle is red
					{
						uncle->color = Black;
						x->parent->color = Black;
						gdparent->color = Red;
						x = gdparent;
					}
					else //no uncle or uncle is black
					{
						if (x == x->parent->right) //x is the right child of parent
						{
							x = x->parent;
							_leftRotate(x);
						}
						x->parent->color = Black;
						gdparent->color = Red;
						_rightRotate(gdparent);
					}
				}
				else //parent is right child of grand-parent, mirror actions
				{
					node * uncle = gdparent->left;
					if (uncle && uncle->color == Red) //uncle is red
					{
						uncle->color = Black;
						x->parent->color = Black;
						gdparent->color = Red;
						x = gdparent;
					}
					else //no uncle or uncle is black
					{
						if (x == x->parent->left) //x is the right left of parent
						{
							x = x->parent;
							_rightRotate(x);
						}
						x->parent->color = Black;
						gdparent->color = Red;
						_leftRotate(gdparent);
					}
				}
			}
			_root->color = Black;
		}

		node*	_erase(node * root, const value_type& val, int clean = 1)
		{
			node * tmp;

			if (!root)
				return (0);
			if (_comp(root->val, val))
				_erase(root->right, val, clean);
			else if (_comp(val, root->val))
				_erase(root->left, val, clean);
			else if (root->left && root->right)
			{
				tmp = root->right;
				while (tmp->left)
					tmp = tmp->left;

				root->right = _erase(root->right, tmp->val, 0);

				root->left->parent = tmp;
				if (root->right)
					root->right->parent = tmp;
				_parentUpdateChild(root, tmp);
	
				tmp->left = root->left;
				tmp->right = root->right;
				tmp->parent = root->parent;
				tmp->color = root->color;

				// node * replace = _createNode(tmp->val, root->parent,
				// 							root->left, root->right, root->color);
				// _size++;
				// root->left->parent = replace;
				// root->right->parent = replace;
				// _parentUpdateChild(root, replace);
				// replace->right = _erase(root->right, tmp->val);
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
				_parentUpdateChild(tmp, root);
				if (tmp->color == Black)
					_eraseFix(root, tmp->parent);
				if (clean)
					_clearNode(tmp);
			}
			return root;
		}

		// void _printNodeRecu(node * n)
		// {
		// 	if (!n)
		// 		return ;
		// 	std::cout << "///////////"  << std::endl;
		// 	std::cout << "n->val:" << n->val.first << std::endl;	
		// 	std::cout << "n->color:" << n->color << std::endl;	
		// 	if (n->left)
		// 	{
		// 		std::cout << "n-left->val:" << n->left->val.first << std::endl;	
		// 		std::cout << "n-left->color:" << n->left->color << std::endl;
		// 	}	
		// 	if (n->right)
		// 	{
		// 		std::cout << "n-right->val:" << n->right->val.first << std::endl;	
		// 		std::cout << "n-right->color:" << n->right->color << std::endl;	
		// 	}
		// 	_printNodeRecu(n->left);
		// 	_printNodeRecu(n->right);
		// }

		/*	
		**	Let y the erased node
		**	x is the node that replaced y
		**	If x != null, x is y's only child, x's color is definitely Red
		**	Since y needs to be Black to launch this function, y must had a sibling
		**	The (x->color == Black) condition is usefull only starting from the 2nd round of while loop
		*/
		void	_eraseFix(node *x, node * parent)
		{	
			while (x != _root && (x == 0 || x->color == Black))
			{
				if (x == parent->left)
				{
					node * sibling = parent->right;

					if (sibling->color == Red)
					{
						sibling->color = Black;
						parent->color = Red;
						_leftRotate(parent);	
						sibling = parent->right;
					}	
					if ((!sibling->left || sibling->left->color == Black)
						&& (!sibling->right || sibling->right->color == Black))
					{
						sibling->color = Red;
						x = parent;
						parent = x->parent;
					}
					else
					{
						if (!sibling->right || sibling->right->color == Black)
						{
							if (sibling->left)
								sibling->left->color = Black;
							sibling->color = Red;
							_rightRotate(sibling);
							sibling = parent->right;
						}
						sibling->color = parent->color;
						parent->color = Black;
						if (sibling->right)
							sibling->right->color = Black;
						_leftRotate(parent);
						break;
					}
				}
				else //x == parent->right, mirror actions
				{
					node * sibling = parent->left;

					if (sibling->color == Red)
					{
						sibling->color = Black;
						parent->color = Red;
						_rightRotate(parent);
						sibling = parent->left;
					}
					if ((!sibling->left || sibling->left->color == Black)
						&& (!sibling->right || sibling->right->color == Black))
					{
						sibling->color = Red;
						x = parent;
						parent = x->parent;
					}
					else
					{
						if (!sibling->left || sibling->left->color == Black)
						{
							if (sibling->right)
								sibling->right->color = Black;
							sibling->color = Red;
							_leftRotate(sibling);
							sibling = parent->left;
						}
						sibling->color = parent->color;
						parent->color = Black;
						if (sibling->left)
							sibling->left->color = Black;
						_rightRotate(parent);
						break;
					}
				}
			}
			if (x)
				x->color = Black;
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
									node *left = 0, node *right = 0, Color c = Red)
		{
			node *	ret;

			ret = _nodeAlloc.allocate(1);
			_nodeAlloc.construct(ret, node(val, parent, left, right, c));
			return (ret);
		}

		node *	_copyNodeRecur(node *root, node * parent = 0)
		{
			node * cp = 0;

			if (root)
			{
				cp = _createNode(root->val, parent, 0, 0, root->color);
				cp->left = _copyNodeRecur(root->left, cp),
				cp->right = _copyNodeRecur(root->right, cp);
			}
			return cp;
		}

		void	_clearNode(node * nd)
		{
			if (nd)
			{
				_nodeAlloc.destroy(nd);
				_nodeAlloc.deallocate(nd, 1);
				if (_size)
					_size--;
				if (!_size)
				{
					_root = 0;
					_end->left = 0;
				}
			}
		}

		void	_parentUpdateChild(node *oldChild, node *newChild)
		{
			if (!oldChild)
				return ;
			if (_root == oldChild)
				_root = newChild;
			if (oldChild->parent)
			{
				if (oldChild->parent->right == oldChild)
					oldChild->parent->right = newChild;
				else if (oldChild->parent->left == oldChild)
					oldChild->parent->left = newChild;
			}
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

		void	_leftRotate(node * x)
		{
			node * y = x->right;

			x->right = y->left;
			if (x->right)
				x->right->parent = x;

			y->parent = x->parent;
			_parentUpdateChild(x, y);

			y->left = x;
			x->parent = y;
		}

		void	_rightRotate(node *x)
		{
			node * y = x->left;

			x->left = y->right;
			if (x->left)
				x->left->parent = x;

			y->parent = x->parent;
			_parentUpdateChild(x, y);

			y->right = x;
			x->parent = y;
		}

		node *		_root;
		node *		_end;
		size_t		_size;
		ValCompare	_comp;
		NodeAlloc	_nodeAlloc;
	}; //classe RBtree

} //namespace ft
#endif
