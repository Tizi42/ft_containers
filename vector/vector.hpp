/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:14:44 by tyuan             #+#    #+#             */
/*   Updated: 2022/03/22 15:14:49 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include <memory>
# include <limits>
# include <algorithm>
# include <stdexcept>
# include <iostream>
# include <stdint.h>
# include "iterator.hpp"
# include "tools.hpp"

namespace ft 
{	
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:

	//Typedef
		typedef typename Allocator::reference			reference;
		typedef typename Allocator::const_reference		const_reference;
		typedef	T										value_type;
		typedef	Vector_iterator<value_type>				iterator;
		typedef	Vector_iterator<const value_type>		const_iterator;
		typedef	size_t									size_type;
		typedef	ptrdiff_t								difference_type;
		typedef	Allocator 								allocator_type;
		typedef	typename Allocator::pointer				pointer;
		typedef	typename Allocator::const_pointer		const_pointer;
		typedef	ft::reverse_iterator<iterator>			reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	//Canonical form
		explicit vector(const allocator_type& alloc = allocator_type())
				:  _begin(0), _end(_begin), _capacity(0), _alloc(alloc)
		{}

		explicit  vector(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
						: _capacity(n), _alloc(alloc)
		{
			this->_begin = this->_alloc.allocate(n);
			this->_end = this->_begin;
			while (n--)
			{
				this->_alloc.construct(this->_end, val);
				this->_end++;
			}
		}

		template <class InputIterator>
		vector(InputIterator first, typename ft::enable_if
					<!ft::is_integral<InputIterator>::value,
					InputIterator>::type last,
				const allocator_type& alloc = allocator_type())
				: _alloc(alloc)
		{
			difference_type	n = ft::distance(first, last);

			this->_begin = this->_alloc.allocate(n);
			this->_end = this->_begin;
			this->_capacity = n;

			while (first != last)
			{
				this->_alloc.construct(this->_end, *(first++));
				this->_end++;
			}
		}

		vector(const vector& x) :  _begin(0), _end(_begin),
									_capacity(0), _alloc(x._alloc)
		{
			*this = x;
		}

		~vector()
		{
			this->clear();
			this->_alloc.deallocate(this->_begin, this->_capacity);
		}

		vector<T, Allocator>& operator=(const vector& rhs)
		{
			if (this != &rhs)
			{
				this->clear();
				this->assign(rhs.begin(), rhs.end());
			}
			return (*this);
		}

	//Iterators
		iterator	begin()
		{
			return iterator(this->_begin);
		}

		const_iterator	begin() const
		{
			return const_iterator(this->_begin);
		}

		iterator	end()
		{
			return iterator(this->_end);
		}

		const_iterator	end() const
		{
			return const_iterator(this->_end);
		}

		reverse_iterator	rbegin()
		{
			return reverse_iterator(this->_end);
		}

		const_reverse_iterator	rbegin() const
		{
			return const_reverse_iterator(this->_end);
		}

		reverse_iterator	rend()
		{
			return reverse_iterator(this->_begin);
		}

		const_reverse_iterator	rend() const
		{
			return const_reverse_iterator(this->_begin);
		}

	//Allocator
		allocator_type	get_allocator() const
		{
			allocator_type	alloc_copy(this->_alloc);
			return (alloc_copy);
		}

	//Capacity
		size_type	size() const 
		{
			return ((size_type)(_end - _begin));
		}

		size_type	max_size() const
		{
			if (sizeof(T) == 1)
				return (std::numeric_limits<ptrdiff_t>::max());
			return (_alloc.max_size());
		}

		void	resize(size_type n, T val = T())
		{
			size_type	sz = this->size();

			this->reserve(_calNewCapacity(n));
			if (n > sz)
				this->insert(this->end(), n - sz, val);
			else
			{
				for ( ; sz > n; sz--)
				{
					this->_alloc.destroy(--this->_end);
				}
			}
		}

		size_type	capacity() const
		{
			return (this->_capacity);
		}

		bool	empty() const
		{
			return (this->_begin == this->_end);
		}

		void	reserve(size_type n)
		{
			if (n <= this->_capacity)
				return ;
			else if (n > this->max_size())
				throw std::length_error("vector: length error");
			
			pointer	old_begin = this->_begin;

			this->_begin = this->_alloc.allocate(n);
			int	i = 0;
			for ( ; old_begin + i != this->_end; i++)
			{
				this->_alloc.construct(this->_begin + i, *(old_begin + i));
				this->_alloc.destroy(old_begin + i);
			}
			this->_alloc.deallocate(old_begin, this->_capacity);
			this->_end = this->_begin + i;
			this->_capacity = n;
		}

	//Element access
		reference		operator[](size_type n)
		{
			return (*(this->_begin + n));
		}
		
		const_reference	operator[](size_type n) const
		{
			return (*(this->_begin + n));
		}

		reference		at(size_type n)
		{
			if (n >= this->size())
				throw std::out_of_range("vector: out of range");
			return (*(this->_begin + n));
		}

		const_reference	at(size_type n) const
		{
			if (n >= this->size())
				throw std::out_of_range("vector: out of range");
			return (*(this->_begin + n));
		}

		reference		front()
		{
			return (*this->_begin);
		}

		const_reference	front() const
		{
			return (*this->_begin);
		}
		
		reference		back()
		{
			return (*(this->_end - 1));
		}

		const_reference	back() const
		{
			return (*(this->_end - 1));
		}

	//Modifiers
		template <class InputIterator>
		void	assign(InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value,
							InputIterator>::type last)
		{
			clear();
			difference_type	n = ft::distance(first , last);
			reserve(_calNewCapacity(n));
			insert(begin(), first, last);
		}

		void	assign(size_type n, const T& val)
		{
			clear();
			reserve(_calNewCapacity(n));		
			insert(begin(), n, val);
		}

		void	push_back(const T& val)
		{
			if (size() == _capacity)
				reserve(_calNewCapacity(size() + 1));
			_alloc.construct(_end, val);
			_end++;
		}

		void	pop_back()
		{
			_alloc.destroy(_end--);
		}

		
		iterator	insert(iterator position, const T& val)
		{
			insert(position, 1, val);
			return (position);
		}

		
		void	insert(iterator position, size_type n, const T& val)
		{
			size_type	n_reloc = _end - position.base();

			reserve(_calNewCapacity(size() + n));
			pointer	new_end = _end + n;

			for (size_type i = 0; i < n_reloc; i++)
			{
				 _alloc.construct(--new_end, *(--_end));
				 _alloc.destroy(_end);
			}
			for (size_type i = 0; i < n; i++)
			{
				_alloc.construct(--new_end, val);
			}
			_end = new_end + n_reloc + n; 
		}

		
		template <class InputIterator>
		void	insert(iterator position, InputIterator first,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value,
							InputIterator>::type last)
		{
			difference_type	n = ft::distance(first , last);
			size_type		n_reloc = _end - position.base();
	
			reserve(_calNewCapacity(size() + n));
			pointer	new_end = _end + n;

			for (size_type i = 0; i < n_reloc; i++)
			{
				 _alloc.construct(--new_end, *(--_end));
				 _alloc.destroy(_end);
			}
			for (int i = 0; i < n; i++)
			{
				_alloc.construct(--new_end, *(--last));
			}
			_end = new_end + n_reloc + n; 
		}

		iterator	erase(iterator position)
		{
			this->_alloc.destroy(position.base());
			for (int i = 0; position + i + 1 != this->end(); i++)
			{
				this->_alloc.construct((position + i).base(), *(position + i + 1));
			}
			this->_end--;
			return (position);
		}

		iterator	erase(iterator first, iterator last)
		{
			int	i = 0;

			for (i = 0; (first + i) != last; i++)
			{
				this->_alloc.destroy((first + i).base());
			}
			for (i = 0; last != this->end(); i++, last++)
			{
				this->_alloc.construct((first + i).base(), *last);
			}
			this->_end = (first + i).base();
			return (first);
		}
		
		void	swap(vector<T, Allocator>& x)
		{
			ft::swap(this->_begin, x._begin);
			ft::swap(this->_end, x._end);
			ft::swap(this->_alloc, x._alloc);
			ft::swap(this->_capacity, x._capacity);
		}

		void	clear()
		{
			while(this->_end != this->_begin)
				this->_alloc.destroy(--this->_end);
		}

	private:
		size_type	_calNewCapacity(size_type n)
		{
			if (n <= _capacity)
				return (_capacity);
			else if (_capacity * 2 >= n)
				return (_capacity * 2);
			else
				return (n);
		}

		pointer			_begin;
		pointer			_end;
		size_type		_capacity;
		allocator_type	_alloc;
	};

/* ************************************************************************** */
/*                                                                            */
/*                 Implementation of Non-member function			  		  */
/*  																	      */
/* ************************************************************************** */

//Relational operators
	template <class T, class Allocator>
	bool	operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		if (x.size() != y.size())
			return (false);
		return (ft::equal(x.begin(), x.end(), y.begin()));
	}

	template <class T, class Allocator>
	bool	operator<(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
	}

	template <class T, class Allocator>
	bool	operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		return (!(x == y));
	}

	template <class T, class Allocator>
	bool	operator>(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		return (y < x);
	}

	template <class T, class Allocator>
	bool	operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		return (!(x < y));
	}

	template <class T, class Allocator>
	bool	operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		return (!(y < x));
	}

//Algo non member
	template <class T, class Allocator>
	void	swap(vector<T,Allocator>& x, vector<T,Allocator>& y)
	{
		x.swap(y);
	}

} //namesapce ft

#endif
