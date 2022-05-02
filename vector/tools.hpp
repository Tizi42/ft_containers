#ifndef TOOLS_H
# define TOOLS_H

# include <iostream>

namespace ft
{
/* ************************************************************************** */
/*                                                                            */
/*                        lexicographical_compare			  				  */
/*  																	      */
/* ************************************************************************** */
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first1 > *first2)
				return (false);
			if (*first1 < *first2)
				return (true);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return (false);
			if (comp(*first1, *first2))
				return (true);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

/* ************************************************************************** */
/*                                                                            */
/*                        		enable_if					  				  */
/*  																	      */
/* ************************************************************************** */
	template<bool Cond, class T = void>
	struct enable_if {};
 
	template<class T>
	struct enable_if<true, T>
	{
		typedef T	type;
	};

/* ************************************************************************** */
/*                                                                            */
/*                        		is_integral									  */
/*  																	      */
/* ************************************************************************** */

	template<class T, T v>
	struct integral_constant
	{
		static const T value = v;

		typedef T	value_type;
		typedef integral_constant<T, v>		type;
	
		operator value_type() const {return v;}; //noexcept, constexpr
	};

	typedef integral_constant<bool, false>	false_type;
	typedef integral_constant<bool, true>	true_type;

// is_integral_base default
	template <typename T>
	struct is_integral_base : public false_type {};

// is_integral_base's template specialization
	template<> struct is_integral_base<bool> : public true_type {};
	template<> struct is_integral_base<char> : public true_type {};
	template<> struct is_integral_base<signed char> : public true_type {};
	template<> struct is_integral_base<short int> : public true_type {};
	template<> struct is_integral_base<int> : public true_type {};
	template<> struct is_integral_base<long int> : public true_type {};
	template<> struct is_integral_base<long long int> : public true_type {};
	template<> struct is_integral_base<unsigned char> : public true_type {};
	template<> struct is_integral_base<unsigned short int> : public true_type {};
	template<> struct is_integral_base<unsigned int> : public true_type {};
	template<> struct is_integral_base<unsigned long int> : public true_type {};
	template<> struct is_integral_base<unsigned long long int> : public true_type {};

	template <typename T>
	struct is_integral : public is_integral_base<T> {};

/* ************************************************************************** */
/*                                                                            */
/*                        		pair & make_pair							  */
/*  																	      */
/* ************************************************************************** */

	template <class T1, class T2>
	struct pair
	{
	public:

		typedef T1	first_type;
		typedef T2	second_type;

		pair() : first(), second() {}

		template<class U, class V>
		pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}

		pair (const first_type& a, const second_type& b) : first(a), second(b) {}

		~pair() {}

		// note: implicitly declared ???
		pair& operator=(const pair& pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		}

		first_type	first;
		second_type	second;
	};

//pair's non member relational operators
	template <class T1, class T2>
	bool	operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool	operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool	operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool	operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool	operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool	operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs < rhs);
	}

//make_pair
	template <class T1, class T2>
	pair<T1,T2>		make_pair (T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

/* ************************************************************************** */
/*                                                                            */
/*                        		equal										  */
/*  																	      */
/* ************************************************************************** */

	template <class InputIterator1, class InputIterator2>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1++ == *first2++))
				return false;
		}
		return true;
	}	

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
		}
		return true;
	}

}

#endif