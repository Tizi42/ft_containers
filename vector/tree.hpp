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

	template <class T>
	struct Node
	{
		T		val;
		Node *	parent;
		Node *	left;
		Node *	right;

		Node(const T& val, Node *parent, Node *left = 0, Node *right = 0)
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

		Node & next()
		{
			
		}

		//Node & previous();
		// ==
		// !=
		// < > <= >= 
		
	};

/* ************************************************************************** */
/*                                                                            */
/*                        	binary tree										  */
/*  																	      */
/* ************************************************************************** */

//basic BTS, not balanced
	template <class T, class NodeAlloc = std::allocator<Node<T> > >
	class Btree
	{
	public:
		typedef Node<T>		node;

		Btree() : _root(0), _leftmost(0), _rightmost(0),
					_capacity(0), _nodeAlloc(NodeAlloc()) {}

		Btree(const Btree& rhs) {*this = rhs;}

		~Btree
		{
			node *nd = _leftmost;
			node *next = 0;

			while (nd)
			{
				next = nd->next();
				_nodeAlloc.destroy(nd);
				_nodeAlloc.deallocate(nd);
				nd = next;
			}
		}

		Btree &	operator=(const Btree & rhs)
		{
			if (this != &rhs)
			{
				
			}
			return (*this);
		}


	private:
		node *		_root;
		node *		_leftmost;
		node *		_rightmost;
		size_t		_capacity;
		NodeAlloc	_nodeAlloc;
	};

} //namespace ft
#endif