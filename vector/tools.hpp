#ifndef TOOLS_H
# define TOOLS_H

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
			if (first2 = last2 || *first1 > *first2)
				return (false);
			if (*first1 < *first2)
				return (true);
			first1++;
			first2++:
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 = last2 || comp(*first2, *first1))
				return (false);
			if (comp(*first1, *first2))
				return (true);
			first1++;
			first2++:
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

/* ************************************************************************** */
/*                                                                            */
/*                        		pair & make_pair							  */
/*  																	      */
/* ************************************************************************** */




}

#endif