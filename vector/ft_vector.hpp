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
/* ************************************************************************** */
/*                                                                            */
/*                            Prototypes			  		 				  */
/*  																	      */
/* ************************************************************************** */	
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:

	//Typedef
		typedef typename Allocator::reference			reference;
		typedef typename Allocator::const_reference		const_reference;
		typedef											iterator;
		typedef											const_iterator;
		typedef	size_t									size_type;
		typedef	ptrdiff_t								difference_type;
		typedef	T										value_type;
		typedef	Allocator 								allocator_type;
		typedef	typename Allocator::pointer				pointer;
		typedef	typename Allocator::const_pointer		const_pointer
		typedef	std::reverse_iterator<iterator>			reverse_iterator;
		typedef	std::reverse_iterator<const_iterator>	const_reverse_iterator;

	//Canonical form
		explicit vector(const allocator_type& alloc = allocator_type());	
		explicit vector(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type());
		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type());	
		vector(const vector& x);
		~vector();
		vector& operator=(const vector& x);

	//Iterators
		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;
		allocator_type			get_allocator() const;

	//Capacity
		size_type	size() const;
		size_type	max_size() const;
		void		resize(size_type n, T val = T());
		size_type	capacity() const;
		bool		empty() const;
		void		reserve(size_type n);

	//Element access
		reference		operator[](size_type n);
		const_reference	operator[](size_type n) const;
		reference		at(size_type n);
		const_reference	at(size_type n) const;
		reference		front();
		const_reference	front() const;
		reference		back();
		const_reference	back() const;

	//Modifiers
		template <class InputIterator>
		void		assign(InputIterator first, InputIterator last);
		void		assign(size_type n, const T& val);
		void		push_back(const T& val);
		void		pop_back();
		iterator	insert(iterator position, const T& val);
		void		insert(iterator position, size_type n, const T& val);
		template <class InputIterator>
		void		insert(iterator position,
							InputIterator first, InputIterator last);
		iterator	erase(iterator position);
		iterator	erase(iterator first, iterator last);
		void		swap(vector& x);
		void		clear();

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
	bool	operator==(const vector<T,Allocator>& x,
						const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool	operator<(const vector<T,Allocator>& x,
						const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool	operator!=(const vector<T,Allocator>& x,
						const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool	operator>(const vector<T,Allocator>& x,
						const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool	operator>=(const vector<T,Allocator>& x,
						const vector<T,Allocator>& y);
	template <class T, class Allocator>
	bool	operator<=(const vector<T,Allocator>& x,
						const vector<T,Allocator>& y);

//Algo non member
	template <class T, class Allocator>
	void	swap(vector<T,Allocator>& x, vector<T,Allocator>& y)
	{
		x.swap(y);
	}

/* ************************************************************************** */
/*                                                                            */
/*                 Implementation of Member function			  	 		  */
/*  																	      */
/* ************************************************************************** */

//Canonical form
	template <typename T, typename Allocator>
	vector<T, Allocator>::vector(const allocator_type& alloc = allocator_type())
	{
		this->_alloc = alloc;
		this->_begin = this->_alloc.allocate(0);
		this->_end = this->_begin;
		this->capacity = 0;
	}

	template <typename T, typename Allocator>
	vector<T, Allocator>::vector(size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type())
	{
		this->_alloc = alloc;
		this->_begin = this->_alloc.allocate(n);
		this->_end = this->_begin;
		this->capacity = n;
		this->assign(n, val);
	}

	template <typename T, typename Allocator>
	template <class InputIterator>
	vector<T, Allocator>::vector(InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type())
	{
		this->_alloc = alloc;
		this->_begin = this->_alloc.allocate(n);
		this->_end = this->_begin;
		this->capacity = n;
		this->assign(first, last);
	}

	template <typename T, typename Allocator>
	vector<T, Allocator>::vector(const vector& x)
	{
		*this = x;
	}

	template <typename T, typename Allocator>
	vector<T, Allocator>::~vector()
	{
		this->clear();
		this->_alloc.deallocate(this->_begin, this->_capacity);
	}

	template <typename T, typename Allocator>
	vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& x)
	{
		this->assign(x.begin(), x.end());
		return (*this);
	}

//Iterators
	iterator				begin();
	const_iterator			begin() const;
	iterator				end();
	const_iterator			end() const;
	reverse_iterator		rbegin();
	const_reverse_iterator	rbegin() const;
	reverse_iterator		rend();
	const_reverse_iterator	rend() const;
	allocator_type			get_allocator() const;

//Capacity
	template <typename T, typename Allocator>
	inline typename vector<T, Allocator>::size_type	vector<T, Allocator>::size() const 
	{
		return ((size_type)(this->_end - this->_begin));
	}

	template <typename T, typename Allocator>
	inline typename vector<T, Allocator>::size_type	vector<T, Allocator>::max_size() const
	{
		return (allocator_type().max_size());
	}

	template <typename T, typename Allocator>
	void	vector<T, Allocator>::resize(size_type n, T val = T())
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

	template <typename T, typename Allocator>
	inline typename vector<T, Allocator>::size_type	vector<T, Allocator>::capacity() const
	{
		return (this->_capacity);
	}

	template <typename T, typename Allocator>
	inline bool	vector<T, Allocator>::empty() const
	{
		return (this->_begin == this->_end);
	}

	template <typename T, typename Allocator>
	void	vector<T, Allocator>::reserve(size_type n)
	{
		if (n > this->max_size())
			throw length_error;
		else if (n <= this->_capacity)
			return ;
		
		pointer old_begin = this->_begin;
		this->_begin = this->_alloc.allocate(n); //Maybe allocate more than asked?
		for (int i = 0; old_begin != this->_end; i++, old_begin++)
			*(this->_begin + i) =  *old_begin;
		this->_end = this->_begin + i;
		this->_capacity = n; //Maybe allocate more than asked?
	}

//Element access
	template <typename T, typename Allocator>
	reference	vector<T, Allocator>::operator[](size_type n)
	{
		return (&(this->_begin + n));
	}

	template <typename T, typename Allocator>
	const_reference	vector<T, Allocator>::operator[](size_type n) const
	{
		return (&(this->_begin + n));
	}

	template <typename T, typename Allocator>
	reference	vector<T, Allocator>::at(size_type n)
	{
		return (&(this->_begin + n));
	}

	template <typename T, typename Allocator>
	const_reference	vector<T, Allocator>::at(size_type n) const
	{
		if (n >= this->size())
			throw out_of_range;
		return (&(this->_begin + n));
	}

	template <typename T, typename Allocator>
	reference	vector<T, Allocator>::front()
	{
		return (&this->_begin);
	}

	template <typename T, typename Allocator>
	const_reference	vector<T, Allocator>::front() const
	{
		return (&this->_begin);
	}

	template <typename T, typename Allocator>
	reference	vector<T, Allocator>::back()
	{
		return (&this->_end);
	}

	template <typename T, typename Allocator>
	const_reference	back() vector<T, Allocator>::const
	{
		return (&this->_begin);
	}

//Modifiers
	template <typename T, typename Allocator>
	template <class InputIterator>
	void	vector<T, Allocator>::assign(InputIterator first, InputIterator last)
	{
		this->clear();
		this->insert(this->_end, fisrt, last);
	}

	template <typename T, typename Allocator>
	void	vector<T, Allocator>::assign(size_type n, const T& val)
	{
		this->clear();
		this->insert(this->_end, n, val); //or begin
	}

	template <typename T, typename Allocator>
	void	vector<T, Allocator>::push_back(const T& val)
	{
		this->insert(this->_end, val);
	}

	template <typename T, typename Allocator>
	void	vector<T, Allocator>::pop_back()
	{
		this->erase(this->_end - 1);
	}

	template <typename T, typename Allocator>
	iterator	vector<T, Allocator>::insert(iterator position, const T& val)
	{
		insert(position, 1, val);
		return (position);
	}

	template <typename T, typename Allocator>
	void	vector<T, Allocator>::insert(iterator position, size_type n, const T& val)
	{
		iterator new_pos = position + n;

		this->reserve(this->size() + n);
		for (int i = 0; position + i != this->_end; i++, new_pos++)
			*new_pos = *(position + i);
		this->end = new_pos;		
		for (int i = 0; i < n; i++)
			*(position + i) = val;
	}

	template <typename T, typename Allocator>
	template <class InputIterator>
	void	vector<T, Allocator>::insert(iterator position,
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

	template <typename T, typename Allocator>
	iterator	vector<T, Allocator>::erase(iterator position)
	{
		this->_alloc.destroy(position);
		for (int i = 0; position + i + 1 != this->_end; i++)
		{
			*(position + i) = *(position + i + 1);
		}
		this->_end--;
		return (position);
	}

	template <typename T, typename Allocator>
	iterator	vector<T, Allocator>::erase(iterator first, iterator last)
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

	template <typename T, typename Allocator>
	void	vector<T, Allocator>::swap(vector<T, Allocator>& x)
	{
		std::swap(&this->_begin, &x._begin);
		std::swap(&this->_end, &x._end);
		std::swap(&this->_alloc, &x._alloc);
		std::swap(&this->_capacity, &x._capacity);
	}

	template <typename T, typename Allocator>
	void	vector<T, Allocator>::clear()
	{
		for (; this->_end != this->_begin; )
			this->_alloc.destroy(--this->_end);
	}


}

#endif
