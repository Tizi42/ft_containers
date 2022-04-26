#ifndef FT_MAP_H
# define FT_MAP_H

namespace ft
{
	template <class Key, class T, class Compare = less<Key>,
				class Alloc = allocator<pair<const Key,T> >
	class map
	{
	public:
	//typedef
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef pair<const Key, T>						value_type;
		typedef Compare									key_compare;
		typedef Alloc									allocator_type;
		typedef a bidirectional iterator to value_type	iterator;
		typedef ... to const value_type					const_iterator;
		typedef allocator_type::pointer					pointer;
		typedef allocator_type::const_pointer			const_pointer;
		typedef allocator_type::reference				reference;
		typedef allocator_type::const_reference			const_reference;
		typedef size_t									size_type;
		typedef ptrdiff_t								difference_type;
		typedef reverse_iterator<iterator>				reverse_iterator;
		typedef reverse_iterator<const_iterator>		const_reverse_iterator;

		class value_compare
			: public binary_function<value_type, value_type, bool> 
		{
			friend class map;
			protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}
		public:
			bool operator()(const value_type& x, const value_type& y)
			{ return comp(x.first, y.first);}
		};

	//allocation/deallocation:
		map(const Compare& comp = Compare());
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
		const Compare& comp = Compare()); map(const map<Key, T, Compare, Allocator>& x); ~map();
			map<Key, T, Compare, Allocator>&
		operator=(const map<Key, T, Compare, Allocator>& x);
		void swap(map<Key, T, Compare, Allocator>& x);

	//accessors:
		key_compare key_comp() const;
		value_compare value_comp() const;
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin();
		reverse_iterator rend();
		const_reverse_iterator rend();
		bool empty() const;
		size_type size() const;
		size_type max_size() const;
		Allocator<T>::reference operator[](const key_type& x);

	//insert/erase:
		pair<iterator, bool> insert(const value_type& x);
		iterator insert(iterator position, const value_type& x);
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last);
		void erase(iterator position);
		size_type erase(const key_type& x);
		void erase(iterator first, iterator last);

	// map operations:
		iterator find(const key_type& x);
		const_iterator find(const key_type& x) const;
		size_type count(const key_type& x) const;
		iterator lower_bound(const key_type& x);
		const_iterator lower_bound(const key_type& x) const;
		iterator upper_bound(const key_type& x);
		const_iterator upper_bound(const key_type& x) const;
		pair<iterator, iterator> equal_range(const key_type& x); pair<const_iterator, const_iterator> equal_range(const key_type& x) const;
		};
			template <class Key, class T, class Compare, class Allocator>
			bool operator==(const map<Key, T, Compare, Allocator>& x,
							const map<Key, T, Compare, Allocator>& y);
			template <class Key, class T, class Compare, class Allocator>
			bool operator<(const map<Key, T, Compare, Allocator>& x,
		const map<Key, T, Compare, Allocator>& y);

} //namespace ft

# endif