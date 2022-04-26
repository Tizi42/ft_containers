/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:58:25 by tyuan             #+#    #+#             */
/*   Updated: 2022/03/24 17:58:33 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ITERATOR_H
# define FT_ITERATOR_H

# include <cstddef>

namespace ft
{
/* ************************************************************************** */
/*                                                                            */
/*                            iterator_traits				 				  */
/*  																	      */
/* ************************************************************************** */

	template <class Iterator>
	class iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	class iterator_traits<T*>
	{
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <class T>
	class iterator_traits<const T*>
	{
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef random_access_iterator_tag	iterator_category;
	};

/* ************************************************************************** */
/*                                                                            */
/*                         		iterator			  		 				  */
/*  																	      */
/* ************************************************************************** */

	template <class Category, class T, class Distance = ptrdiff_t,
				class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	

/* ************************************************************************** */
/*                                                                            */
/*                         reverse_iterator			  		 				  */
/*  																	      */
/* ************************************************************************** */

	template <class Iterator>
	class reverse_iterator
	{
	public:
	//typedef
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;

	//constructors & destructor & copy assign
		reverse_iterator() : _base() {}

		explicit reverse_iterator(iterator_type it) : _base(it) {}

		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev_it) : _base(rev_it._base) {}
		
		~reverse_iterator() {}

		template <class Iter>
		reverse_iterator & operator=(const reverse_iterator<Iter>& rev_it) 
		{
			this->_base = rev_it._base;
			return (this->_base);
		}
	
	//other member funcs
		iterator_type base() const 
		{
			return (this->_base);
		}

		reference operator*() const
		{
			iterator_type	it(this->_base);

			return (*--it);
		}

		reverse_iterator operator+(difference_type n) const
		{
			return (reverse_iterator(this->_base - n));
		}

		reverse_iterator& operator++()
		{
			--this->_base;
			return(*this);
		}

		reverse_iterator  operator++(int)
		{
			reverse_iterator	tmp(*this);

			--this->_base;
			return (tmp);
		}

		reverse_iterator& operator+=(difference_type n)
		{
			this->_base -= n;
			return (*this);
		}

		reverse_iterator operator-(difference_type n) const
		{
			return (reverse_iterator(this->_base + n));
		}

		reverse_iterator& operator--()
		{
			++this->_base;
			return(*this);
		}

		reverse_iterator  operator--(int)
		{
			reverse_iterator	tmp(*this);

			++this->_base;
			return (tmp);
		}

		reverse_iterator& operator-=(difference_type n)
		{
			this->_base += n;
			return (*this);
		}

		pointer operator->() const
		{
			return (&(operator*()));
		}

		reference operator[] (difference_type n) const
		{
			return (this->_base[- n - 1]);
		}

	private:
		iterator_type	_base;
	};

	//reverse_iterator non member funcs
	template <class Iterator1, class Iterator2>
	bool operator==(const reverse_iterator<Iterator1>& lhs,
                   const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() == lhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator!=(const reverse_iterator<Iterator1>& lhs,
                   const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() != lhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<(const reverse_iterator<Iterator1>& lhs,
                   const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() > lhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator1>& lhs,
                   const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() >= lhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>(const reverse_iterator<Iterator1>& lhs,
                   const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() < lhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator1>& lhs,
                   const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() <= lhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator>
		operator+(
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n); 
	}

	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type
		operator-(
			const reverse_iterator<Iterator1>& lhs,
			const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() - rhs.base());
	}
}

#endif
