#ifndef TREE_H
# define TREE_H

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
	};

/* ************************************************************************** */
/*                                                                            */
/*                        	binary tree										  */
/*  																	      */
/* ************************************************************************** */

//basic BTS, not balanced
	template <class T>
	class Btree
	{
	public:
		typedef Node<T>		node;

	private:
		node *	root;

	};

} //namespace ft
#endif