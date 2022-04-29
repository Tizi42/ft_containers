#ifndef FT_STACK_H
# define FT_STACK_H

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{

	public:
		typedef Container	container_type;
		typedef T			value_type;
		typedef size_t		size_type;

	//constructor
		explicit stack(const container_type& ctnr = container_type())
			: c (ctnr) {}

	//member funcs
		bool empty() const
		{
			return (this->c.empty());
		}

		size_type size() const
		{
			return (this->c.size());
		}

		value_type& top()
		{
			return (this->c.back());
		}

		const value_type& top() const
		{
			return (this->c.back());
		}

		void push(const value_type& val)
		{
			return (c.push_back(val));
		}

		void pop()
		{
			return (this->c.pop_back());
		}

	//non-member funcs
		friend bool operator==(const ft::stack<T, Container>& lhs,
								const ft::stack<T, Container>& rhs)
		{
			return (lhs.c == rhs.c);
		}

		friend bool operator>=(const ft::stack<T, Container>& lhs,
								const ft::stack<T, Container>& rhs)
		{
			return (lhs.c >= rhs.c);
		}

		friend bool operator<=(const ft::stack<T, Container>& lhs,
								const ft::stack<T, Container>& rhs)
		{
			return (lhs.c <= rhs.c);
		}

		friend bool operator!=(const ft::stack<T, Container>& lhs,
								const ft::stack<T, Container>& rhs)
		{
			return (lhs.c != rhs.c);
		}

		friend bool operator>(const ft::stack<T, Container>& lhs,
								const ft::stack<T, Container>& rhs)
		{
			return (lhs.c > rhs.c);
		}

		friend bool operator<(const ft::stack<T, Container>& lhs,
								const ft::stack<T, Container>& rhs)
		{
			return (lhs.c < rhs.c);
		}

	protected:
		Container	c;

	}; //class stack
} //namespace ft

#endif