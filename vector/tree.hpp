#ifndef TREE_H
# define TREE_H

# include <memory>

namespace ft
{

/* ************************************************************************** */
/*                                                                            */
/*                        		node										  */
/*  																	      */
/* ************************************************************************** */

	template <class T, class Compare>
	struct Node
	{
		T		val;
		Node *	parent;
		Node *	left;
		Node *	right;

		Node(const T& val, Node *parent = 0, Node *left = 0, Node *right = 0)
			: val(val), parent(parent), left(left), right(right) {}
		
		Node(const Node& rhs) { *this = rhs; }

		~Node(void) {}

		Node& operator=(const Node& rhs)
		{
			if (this != &rhs) {
				this->value = rhs.value;
				this->left = rhs.left;
				this->right = rhs.right;
				this->parent = rhs.parent;
			}
			return (*this);
		}
	};

/* ************************************************************************** */
/*                                                                            */
/*                        	binary tree										  */
/*  																	      */
/* ************************************************************************** */

//basic BTS, not balanced
	template <class T, class Compare, class NodeAlloc = std::allocator<Node<T> > >
	class Btree
	{
	public:
		typedef T										value_type;
		typedef Node<T>									node;
		typedef Tree_iterator<T> 						iterator;
		typedef Tree_iterator<const T>					const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	//canonical
		Btree() : _size(0), _nodeAlloc(NodeAlloc())
		{
			this->_root = this->allocNode();
			this->_rightmost = this->_root;
			this->_leftmost = this->_root;
		}

		Btree(const Btree& rhs) : _size(rhs._size), _nodeAlloc(rhs._alloc),
								/*	_root(rhs._root), _rightmost(rhs._rightmost),
									_leftmost(_leftmost) */
		{
			//deep copy needed here
		}

		~Btree
		{

		}

		Btree &	operator=(const Btree & rhs)
		{
			if (this != &rhs)
			{
				//deep copy needed here
			}
			return (*this);
		}
	
	//iterators
		iterator 		begin() { return iterator(this->_leftmost()); }
		const_iterator	begin() const { return const_iterator(this->_leftmost()); }
		iterator		end() { return iterator(this->_rightmost()->right); }
		const_iterator	end() const { return const_iterator(this->_rightmost()->right); }

		reverse_iterator		rbegin() { return reverse_iterator(this->end()); }	
		const_reverse_iterator	rbegin() { return reverse_iterator(this->end()); }
		reverse_iterator rend() { return reverse_iterator(this->begin()); }
		const_reverse_iterator rend() { return reverse_iterator(this->begin()); }
	
	//capacity
		size_type size() const { return (this->_size); }
		size_type max_size() const { return (this->_alloc.max_size()); }
	
	//insertion
		pair<iterator, bool> insert(const value_type& x)
		{
			iterator it = this->lower_bound(x);

			if (_comp(*it, x) )
			{

				return ft::make_pair(, true);
			}
			return ft::make_pair(it, false);
		}

		iterator insert(iterator position, const value_type& x)
		{
			iterator it = this->lower_bound(x);

			if (*it != x)
			{

				
			}
			return it;
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
			
		}

		size_type erase(const value_type& x)
		{
			
		}

		void erase(iterator first, iterator last)
		{
			
		}

	//other modifiers
		void swap(map<Key,T,Compare,Allocator>& rhs)
		{
			
		}

		void clear()
		{
			
		}

	//operations
		iterator		find(const value_type& x)
		{
			
		}

		const_iterator	find(const value_type& x) const
		{
			
		}
	
		iterator		lower_bound(const value_type& x)
		{
			
		}

		const_iterator	lower_bound(const value_type& x) const
		{
		}

		iterator		upper_bound(const value_type& x)
		{
			
		}

		const_iterator	upper_bound(const value_type& x) const
		{
		}

	//relational operations
		friend bool operator==(const map<Key,T,Compare,Allocator>& x,
						const map<Key,T,Compare,Allocator>& y)
		{
			return (x._tree == y._tree);
		}

		friend bool operator!=(const map<Key,T,Compare,Allocator>& x,
						const map<Key,T,Compare,Allocator>& y)
		{
			return (x._tree == y._tree);
		}

		friend bool operator<(const map<Key,T,Compare,Allocator>& x,
						const map<Key,T,Compare,Allocator>& y)
		{
			return (x._tree < y._tree);
		}

		friend bool operator>(const map<Key,T,Compare,Allocator>& x,
						const map<Key,T,Compare,Allocator>& y)
		{
			return (x._tree > y._tree);
		}

		friend bool operator>=(const map<Key,T,Compare,Allocator>& x,
						const map<Key,T,Compare,Allocator>& y)
		{
			return (x._tree >= y._tree);
		}

		friend bool operator<=(const map<Key,T,Compare,Allocator>& x,
						const map<Key,T,Compare,Allocator>& y)
		{
			return (x._tree <= y._tree);
		}

	private:
		node *		_root;
		size_t		_size;
		NodeAlloc	_nodeAlloc;
		Compare		_comp;

		iterator	_insert(node * root, node * nd)
		{

		}

		node*	_erase(node * root, value_type val)
		{
			node * tmp;

			if (!root)
				return (0);
			if (_comp(root->val, val))
				_erase(root->right, nd);
			else if (_comp(val, root->val))
				_erase(root->left, nd->val)
			else if (root->left && root->right)
			{
				tmp = root->right;
				while (tmp->left)
					tmp = tmp->left;
				root->val = tmp->val;
				root->right = erase(root->right, tmp->val);
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
				_nodeAlloc.destroy(tmp);
				_nodeAlloc.deallocate(tmp);
				tmp = 0;
				_size--;
			}
			return root;
		}

		node *	_leftmost()
		{
			node * ret = _root;

			while (ret)
				ret = ret->left;
			return (ret);
		}

		node *	_rightmost()
		{
			node * ret = _root;

			while (ret)
				ret = ret->right;
			return (ret);
		}

	}; //classe Btree

} //namespace ft
#endif