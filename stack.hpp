/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 10:26:52 by user42            #+#    #+#             */
/*   Updated: 2021/07/04 20:44:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <memory>
# include "utils.hpp"
# include "vector.hpp"

template <typename T, class Container = vector<T> >
class stack
{
	public :
		typedef T								value_type;
		typedef Container						container_type;
		typedef typename Container::size_type	size_type;

	private :
		Container _ctnr;

	public :
		explicit stack(const container_type& ctnr = container_type())
		: _ctnr(ctnr)
		{}

		bool empty() const
		{return _ctnr.empty();}

		size_type size() const
		{return _ctnr.size();}

		value_type &top()
		{return _ctnr.back();}

		const value_type& top() const
		{return _ctnr.back();}

		void push(const value_type& val)
		{_ctnr.push_back(val);}

		void pop()
		{_ctnr.pop_back();}

		template <class TN, class ContainerN>
		friend bool operator== (const stack<TN,ContainerN>& lhs, const stack<TN,ContainerN>& rhs);

		template <class TN, class ContainerN>
		friend bool operator!= (const stack<TN,ContainerN>& lhs, const stack<TN,ContainerN>& rhs);

		template <class TN, class ContainerN>
		friend bool operator<  (const stack<TN,ContainerN>& lhs, const stack<TN,ContainerN>& rhs);

		template <class TN, class ContainerN>
		friend bool operator<= (const stack<TN,ContainerN>& lhs, const stack<TN,ContainerN>& rhs);

		template <class TN, class ContainerN>
		friend bool operator>  (const stack<TN,ContainerN>& lhs, const stack<TN,ContainerN>& rhs);

		template <class TN, class ContainerN>
		friend bool operator>= (const stack<TN,ContainerN>& lhs, const stack<TN,ContainerN>& rhs);

};

template <class T, class Container>
bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{return lhs._ctnr == rhs._ctnr;}

template <class T, class Container>
bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{return lhs._ctnr != rhs._ctnr;}

template <class T, class Container>
bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{return lhs._ctnr <  rhs._ctnr;}

template <class T, class Container>
bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{return lhs._ctnr <= rhs._ctnr;}

template <class T, class Container>
bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{return lhs._ctnr >  rhs._ctnr;}

template <class T, class Container>
bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{return lhs._ctnr >= rhs._ctnr;}

#endif
