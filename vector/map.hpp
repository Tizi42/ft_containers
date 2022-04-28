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

		typedef ?										iterator;
		typedef ?										const_iterator;
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
		{

		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
		{

		}

		map (const map& rhs)
		{

		}

		~map()
		{

		}

		map& operator=(const map& x)
		{

		}

	//observers
		key_compare key_comp() const { return (key_compare()); }
		value_compare value_comp() const { return (value_compare(key_compare())); }

	//iterators
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin();
		reverse_iterator rend();
		const_reverse_iterator rend();
	
	//capacity
		bool empty() const;
		size_type size() const;
		size_type max_size() const;
	
	//element access
		T& operator[](const key_type& x);

	//modifiers
		pair<iterator, bool> insert(const value_type& x);
		iterator insert(iterator position, const value_type& x);
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last);
		void erase(iterator position);
		size_type erase(const key_type& x);
		void erase(iterator first, iterator last);
		void swap(map<Key,T,Compare,Allocator>&);
		void clear();

	//map operations
		iterator		find(const key_type& x);
		const_iterator	find(const key_type& x) const;
		size_type		count(const key_type& x) const;
	
		iterator		lower_bound(const key_type& x);
		const_iterator	lower_bound(const key_type& x) const;
		iterator		upper_bound(const key_type& x);
		const_iterator	upper_bound(const key_type& x) const;

		pair<iterator, iterator> 				equal_range(const key_type& x);
		pair<const_iterator, const_iterator>	equal_range(const key_type& x) const;

	//allocator
		get_allocator

	}; //class map

//
	template <class Key, class T, class Compare, class Allocator>
	bool operator==(const map<Key, T, Compare, Allocator>& x,
							const map<Key, T, Compare, Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool operator<(const map<Key, T, Compare, Allocator>& x,
			const map<Key, T, Compare, Allocator>& y);

} //namespace ft

# endif