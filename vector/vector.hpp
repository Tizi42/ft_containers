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
# include <algorithm>

namespace ft 
{	
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:

	//Typedef
		typedef typename Allocator::reference					reference;
		typedef typename Allocator::const_reference				const_reference;
		typedef	Vector_iterator<value_type>						iterator;
		typedef	Vector_iterator<const value_type>				const_iterator;
		typedef	size_t											size_type;
		typedef	ptrdiff_t										difference_type;
		typedef	T												value_type;
		typedef	Allocator 										allocator_type;
		typedef	typename Allocator::pointer						pointer;
		typedef	typename Allocator::const_pointer				const_pointer
		typedef	ft::reverse_iterator<iterator>					reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	//Canonical form
		explicit vector(const allocator_type& alloc = allocator_type())
		{
			this->_alloc = alloc;
			this->_begin = 0;
			this->_end = 0;
			this->capacity = 0;
		}

		explicit  vector(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
		{
			this->_alloc = alloc;
			this->_begin = this->_alloc.allocate(n);
			this->_end = this->_begin;
			this->capacity = n;
			while (n--)
			{
				this->_alloc.construct(this->_end, val);
				this->_end++;
			}
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type())
		{
			difference_type	n = ft::distance(first, last);

			this->_alloc = alloc;
			this->_begin = this->_alloc.allocate(n);
			this->_end = this->_begin;
			this->capacity = n;

			while (first != last)
			{
				this->_alloc.constrcut(this->_end, *(first++));
				this->_end++;
			}
		}

		vector(const vector& x)
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
				this->assign(x.begin(), x.end());
			return (*this);
		}

	//Iterators
		iterator	begin()
		{
			return (this->_begin);
		}

		const_iterator	begin() const
		{
			return (this->_begin);
		}

		iterator	end()
		{
			return (this->_end);
		}

		const_iterator	end() const
		{
			return (this->_end);
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
			return ((size_type)(this->_end - this->_begin));
		}

		size_type	max_size() const
		{
			return (allocator_type().max_size());
		}

		void	resize(size_type n, T val = T())
		{
			size_type	sz = this->size();

			this->reserve(n);
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
			if (n > this->max_size())
				throw std::length_error;
			else if (n <= this->_capacity)
				return ;
			
			pointer	old_begin = this->_begin;

			this->_begin = this->_alloc.allocate(n);
			for (int i = 0; old_begin != this->_end; i++)
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
			return (&(this->_begin + n));
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
		void	assign(InputIterator first, InputIterator last)
		{
			this->clear();
			this->insert(this->_end, fisrt, last);
		}

		void	assign(size_type n, const T& val)
		{
			this->clear();
			this->insert(this->_end, n, val); //or begin
		}

		void	push_back(const T& val)
		{
			this->insert(this->_end, val);
		}

		void	pop_back()
		{
			this->erase(this->_end - 1);
		}

		
		iterator	insert(iterator position, const T& val)
		{
			insert(position, 1, val);
			return (position);
		}

		
		void	insert(iterator position, size_type n, const T& val)
		{
			iterator new_pos = position + n;

			this->reserve(this->size() + n);
			for (int i = 0; position + i != this->_end; i++, new_pos++)
				*new_pos = *(position + i);
			this->end = new_pos;		
			for (int i = 0; i < n; i++)
				*(position + i) = val;
		}

		
		template <class InputIterator>
		void	insert(typename iterator position,
							InputIterator first, InputIterator last)
		{
			size_type	n = (size_type)(last - first);
			iterator	new_pos = position + n;

			this->reserve(this->size() + n);
			for (int i = 0; position + i != this->end; i++, new_pos++)
				*new_pos = *(position + i);
			this->end = new_pos;
			for (; first != last; position++, first++)
				*position = *first;
		}

		iterator	erase(typename iterator position)
		{
			this->_alloc.destroy(position);
			for (int i = 0; position + i + 1 != this->_end; i++)
			{
				*(position + i) = *(position + i + 1);
			}
			this->_end--;
			return (position);
		}

		iterator	erase(iterator first, iterator last)
		{
			for (int i = 0; (first + i) != last; i++)
			{
				this->_alloc.destroy(fisrt + i);
			}
			for (int i = 0; last != this->_end; i++, last++)
			{
				*(first + i) = *last;
			}
			this->_end = first + i;
			return (first);
		}
		
		void	swap(vector<T, Allocator>& x)
		{
			std::swap(this->_begin, x._begin);
			std::swap(this->_end, x._end);
			std::swap(this->_alloc, x._alloc);
			std::swap(this->_capacity, x._capacity);
		}

		void	clear()
		{
			for (; this->_end != this->_begin; )
				this->_alloc.destroy(--this->_end);
		}

	private:
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
		
		typename vector<T, Allocator>::const_iterator	xbegin = x.begin();
		typename vector<T, Allocator>::const_iterator	xend = x.end();
		typename vector<T, Allocator>::const_iterator	ybegin = y.begin();

		for (; xbegin != xend; xbegin++, ybegin++)
		{
			if (xbegin != ybegin)
				return (false);
		}
		return (true);
	}

	template <class T, class Allocator>
	bool	operator<(const vector<T,Allocator>& x, const vector<T,Allocator>& y)
	{
		return (lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
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
