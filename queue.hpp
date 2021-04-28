/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <tguilbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 10:26:52 by user42            #+#    #+#             */
/*   Updated: 2021/04/28 11:23:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

# include <memory>
# include "utils.hpp"
# include "list.hpp"

template <typename T, class Container = list<T> >
class queue
{
	public :
		typedef T								value_type;
		typedef Container						container_type;
		typedef typename Container::size_type	size_type;

	private :
		Container _ctnr;

	public :
		explicit queue(const container_type& ctnr = container_type())
		: _ctnr(ctnr)
		{}

		bool empty() const
		{return _ctnr.empty();}

		size_type size() const
		{return _ctnr.size();}

		value_type &front()
		{return _ctnr.front();}

		const value_type &front() const
		{return _ctnr.front();}

		value_type &back()
		{return _ctnr.back();}

		const value_type &back() const
		{return _ctnr.back();}

		void push(const value_type& val)
		{_ctnr.push_back(val);}

		void pop()
		{_ctnr.pop_front();}

		template <class TN, class ContainerN>
		friend bool operator== (const queue<TN,ContainerN>& lhs, const queue<TN,ContainerN>& rhs);

		template <class TN, class ContainerN>
		friend bool operator!= (const queue<TN,ContainerN>& lhs, const queue<TN,ContainerN>& rhs);

		template <class TN, class ContainerN>
		friend bool operator<  (const queue<TN,ContainerN>& lhs, const queue<TN,ContainerN>& rhs);

		template <class TN, class ContainerN>
		friend bool operator<= (const queue<TN,ContainerN>& lhs, const queue<TN,ContainerN>& rhs);

		template <class TN, class ContainerN>
		friend bool operator>  (const queue<TN,ContainerN>& lhs, const queue<TN,ContainerN>& rhs);

		template <class TN, class ContainerN>
		friend bool operator>= (const queue<TN,ContainerN>& lhs, const queue<TN,ContainerN>& rhs);

};

template <class T, class Container>
bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
{return lhs._ctnr == rhs._ctnr;}

template <class T, class Container>
bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
{return lhs._ctnr != rhs._ctnr;}

template <class T, class Container>
bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
{return lhs._ctnr <  rhs._ctnr;}

template <class T, class Container>
bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
{return lhs._ctnr <= rhs._ctnr;}

template <class T, class Container>
bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
{return lhs._ctnr >  rhs._ctnr;}

template <class T, class Container>
bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
{return lhs._ctnr >= rhs._ctnr;}

#endif
