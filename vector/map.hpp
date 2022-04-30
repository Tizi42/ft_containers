#ifndef FT_MAP_H
# define FT_MAP_H

# include <memory>
# include "tools.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
	public:
	//typedef
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef pair<const Key, T>						value_type;
		typedef Compare									key_compare;
		typedef Alloc									allocator_type;

		typedef allocator_type::reference				reference;
		typedef allocator_type::const_reference			const_reference;
		typedef allocator_type::pointer					pointer;
		typedef allocator_type::const_pointer			const_pointer;

		typedef ft::Btree<value_type, value_compare>	tree_type;
		typedef tree_type::iterator						iterator;
		typedef tree_type::const_iterator				const_iterator;
		typedef reverse_iterator<iterator>				reverse_iterator;
		typedef reverse_iterator<const_iterator>		const_reverse_iterator;

		typedef size_t									size_type;
		typedef ptrdiff_t								difference_type;


	//nested class
		class value_compare
		{
			friend class map;
		
		protected:
			value_compare(Compare c) : comp(c) {}
			Compare comp;
			
		public:
			typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;

			bool operator()(const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		}; //class value_compare

	//allocation/deallocation
		explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
			: _comp(comp), _alloc(alloc), _tree()
		{}

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			: _comp(comp), _alloc(alloc), _tree()
		{
			this->_tree.insert(first, last);
		}

		map (const map& rhs) : _alloc(rhs._alloc), _comp(rhs._comp),
								_tree(rhs._tree)
		{}

		~map()
		{
			this->clear();
		}

		map& operator=(const map& rhs)
		{
			if (this != &rhs)
			{
				this->_alloc = rhs._alloc;
				this->_comp = rhs._comp;
				this->_tree = rhs._tree;
			}
			return (*this);
		}

	//observers
		key_compare key_comp() const { return (key_compare()); }
		value_compare value_comp() const { return (value_compare(key_compare())); }

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
	
		const_reverse_iterator rbegin()
		{
			return (this->_tree.rbegin());
		}

		reverse_iterator rend()
		{
			return (this->_tree.rend());
		}

		const_reverse_iterator rend()
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
	
	//element access
		T& operator[](const key_type& x)
		{
			iterator it(this->find(x));
			if (it == this->end())
				return this->insert(ft::make_pair(k, mapped_type())).first->second;
			return it->second;
		}

	//modifiers
		pair<iterator, bool>	insert(const value_type& x)
		{
			return (this->_tree.insert(x));
		}

		iterator insert(iterator position, const value_type& x)
		{
			return (this->_tree.insert(position, x));
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			this->_tree.insert(first, last);
		}

		void erase(iterator position)
		{
			this->_tree.erase(position);
		}

		size_type erase(const key_type& x)
		{
			return (this->_tree.erase(x));
		}

		void erase(iterator first, iterator last)
		{
			this->_tree.erase(first, last);
		}

		void swap(map<Key,T,Compare,Allocator>& rhs)
		{
			if (this != &rhs)
				this->_tree.swap(rhs._tree);
		}

		void clear()
		{
			this->_tree.clear();
		}

	//map operations
		iterator		find(const key_type& x)
		{
			return (this->_tree.find(ft::make_pair(x, mapped_type())));
		}

		const_iterator	find(const key_type& x) const
		{
			return (this->_tree.find(ft::make_pair(x, mapped_type())));
		}

		size_type		count(const key_type& x) const
		{
			return (this->find(x) != this->end());
		}
	
		iterator		lower_bound(const key_type& x)
		{
			return (this->_tree.lower_bound(ft::make_pair(x, mapped_type())));
		}

		const_iterator	lower_bound(const key_type& x) const
		{
			return (this->_tree.lower_bound(ft::make_pair(x, mapped_type())));
		}

		iterator		upper_bound(const key_type& x)
		{
			return (this->_tree.upper_bound(ft::make_pair(x, mapped_type())));
		}

		const_iterator	upper_bound(const key_type& x) const
		{
			return (this->_tree.upper_bound(ft::make_pair(x, mapped_type())));
		}

		pair<iterator, iterator> 				equal_range(const key_type& x)
		{
			return (ft::make_pair(this->lower_bound(x), this->upper_bound(x)));
		}

		pair<const_iterator, const_iterator>	equal_range(const key_type& x) const
		{
			return (ft::make_pair(this->lower_bound(x), this->upper_bound(x)));
		}

	//allocator
		allocator_type get_allocator() const
		{
			return (this->_alloc);
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
		allocator_type	_alloc;
		key_compare		_comp;
						_tree;
	}; //class map

	template <class Key, class T, class Compare, class Allocator>
	void swap(map<Key,T,Compare,Allocator>& x,
			map<Key,T,Compare,Allocator>& y)
	{
		x.swap(y);
	}

} //namespace ft

# endif