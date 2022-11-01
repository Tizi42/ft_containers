#ifndef FT_SET_H
# define FT_SET_H

# include <cstddef>
# include <memory>
# include "tools.hpp"
# include "iterator.hpp"
# include "RBtree.hpp"


namespace ft {
	template <class T, class Compare = std::less<T>,
				class Alloc = std::allocator<T> >
	class set 
	{
	public:
	//typedef
		typedef T			key_type;
		typedef T			value_type;
		typedef Compare		key_compare;
		typedef Compare		value_compare;
		typedef Alloc		allocator_type;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;

		typedef typename allocator_type::const_reference	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::const_pointer		pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef ft::RBtree<value_type, value_compare>		tree_type;
		typedef typename tree_type::const_iterator			const_iterator;
		typedef typename tree_type::const_iterator			iterator;
		typedef	typename tree_type::iterator				treeIt;
		typedef ft::reverse_iterator<const_iterator>		reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	//canonical
		explicit set(const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
				: _comp(comp), _alloc(alloc), _tree()
		{

		}

		template <class InputIterator>
		set(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				: _comp(comp), _alloc(alloc), _tree()
		{
			this->_tree.insert(first, last);
		}

		set(const set& rhs) : _comp(rhs._comp), _alloc(rhs._alloc),
								_tree(rhs._tree)
		{

		}

		~set()
		{
			this->clear();
		}

		set &	operator=(const set & rhs)
		{
			if (this != &rhs)
			{
				this->_alloc = rhs._alloc;
				this->_comp = rhs._comp;
				this->_tree = rhs._tree;
			}
			return (*this);
		}
	
	//iterators
		iterator begin()
		{
			return (this->_tree.begin());
		}

		const_iterator begin() const
		{
			return (this->_tree.begin());
		}

		iterator end()
		{
			return (this->_tree.end());
		}

		const_iterator end() const
		{
			return (this->_tree.end());
		}

		reverse_iterator rbegin()
		{
			return (this->_tree.rbegin());
		}
	
		const_reverse_iterator rbegin() const
		{
			return (this->_tree.rbegin());
		}

		reverse_iterator rend()
		{
			return (this->_tree.rend());
		}

		const_reverse_iterator rend() const
		{
			return (this->_tree.rend());
		}

	//capacity
		bool empty() const
		{
			return (!this->_tree.size());
		}

		size_type size() const
		{
			return (this->_tree.size());
		}

		size_type max_size() const
		{
			return (this->_tree.max_size());
		}
	
	//modifiers
		ft::pair<iterator, bool>	insert(const value_type& x)
		{
			ft::pair<treeIt, bool> ret = this->_tree.insert(x);
			return (ft::pair<iterator, bool>(ret.first, ret.second));
		}

		iterator insert(iterator position, const value_type& x)
		{
			return (this->_tree.insert((treeIt &)position, x));
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			this->_tree.insert(first, last);
		}

		void erase(iterator position)
		{
			this->_tree.erase((treeIt &)position);
		}

		size_type erase(const key_type& x)
		{
			return (this->_tree.erase(x));
		}

		void erase(iterator first, iterator last)
		{
			this->_tree.erase((treeIt &)first, (treeIt &)last);
		}

		void swap(set& rhs)
		{
			if (this != &rhs)
				this->_tree.swap(rhs._tree);
		}

		void clear()
		{
			this->_tree.clear();
		}

	//observers
		key_compare key_comp() const { return (key_compare()); }
		value_compare value_comp() const { return (value_compare()); }

	//set operations
		iterator		find(const key_type& x) const
		{
			return (this->_tree.find(x));
		}

		size_type		count(const key_type& x) const
		{
			return (this->find(x) != this->end());
		}
	
		iterator	lower_bound(const key_type& x) const
		{
			iterator	begin = this->begin();
			iterator	end = this->end();
	
			while (begin != end)
			{
				if (!(_comp(*begin, x)))
					return (begin);
				begin++;
			}
			return (begin);
		}

		iterator		upper_bound(const key_type& x) const
		{
			iterator	begin = this->begin();
			iterator	end = this->end();
	
			while (begin != end)
			{
				if (_comp(x, *begin))
					return (begin);
				begin++;
			}
			return (begin);
		}

		pair<iterator, iterator>	equal_range(const key_type& x) const
		{
			return (ft::make_pair(this->lower_bound(x), this->upper_bound(x)));
		}

	//allocator
		allocator_type get_allocator() const
		{
			return (this->_alloc);
		}

	//relational operations
		friend bool operator==(const set<T, Compare, Alloc>& x,
						const set<T, Compare, Alloc>& y)
		{
			return (x._tree == y._tree);
		}

		friend bool operator<(const set<T, Compare, Alloc>& x,
						const set<T, Compare, Alloc>& y)
		{
			return (x._tree < y._tree);
		}

		friend bool operator!=(const set<T, Compare, Alloc>& x,
						const set<T, Compare, Alloc>& y)
		{
			return !(x == y);
		}

		friend bool operator>(const set<T, Compare, Alloc>& x,
						const set<T, Compare, Alloc>& y)
		{
			return (y < x);
		}

		friend bool operator>=(const set<T, Compare, Alloc>& x,
						const set<T, Compare, Alloc>& y)
		{
			return !(x < y);
		}

		friend bool operator<=(const set<T, Compare, Alloc>& x,
						const set<T, Compare, Alloc>& y)
		{
			return !(y < x);
		}

	private: 
		key_compare		_comp;
		allocator_type	_alloc;
		tree_type		_tree;

	}; //class set

	template <class T, class Compare, class Alloc>
	void swap(set<T, Compare, Alloc>& x,
			set<T, Compare, Alloc>& y)
	{
		x.swap(y);
	}
} //namespace ft
# endif