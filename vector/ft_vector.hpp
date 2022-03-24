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
		pointer			_val;
		size_type		_size;
		allocator_type	_alloc;
	};
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
	void	swap(vector<T,Allocator>& x, vector<T,Allocator>& y);

/* ************************************************************************** */
/*                                                                            */
/*                            Implementation			  		 			  */
/*  																	      */
/* ************************************************************************** */

//Canonical form
		explicit vector::vector(const allocator_type& alloc = allocator_type())
		{
			this->_size = 0;
			this->_alloc = alloc;
			this->_val = this->_alloc.allocate(this->_size);
		}

		explicit vector::vector(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
		{
			this->_size = n;
			this->_alloc = alloc;
			this->_val = this->_alloc.allocate(this->_size);
			this->assign(n, val);
		}

		template <class InputIterator>
		vector::vector(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type())
		{
			this->_size = last - first;
			this->_alloc = alloc;
			this->_val = this->_alloc.allocate(this->_size);
			this->assign(first, last);
		}

		vector::vector(const vector& x)
		{
			*this = x;
		}

		~vector::vector()
		{
			for (pointer p = this->_val + size; p != this->_val;)
				this->_alloc.destroy(--p);
			this->_alloc.deallocate(this->_val, this->_size);
		}

		vector& vector::operator=(const vector& x)
		{
			//_size? _alloc?
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
}

#endif
