/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revers.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <tguilbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:02:17 by user42            #+#    #+#             */
/*   Updated: 2021/03/29 11:52:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERS_HPP
# define REVERS_HPP

template<typename it>
class reverse_iterator: public it
{
	public :
		using typename it::value_type;
		using typename it::pointer;
		using typename it::reference;
	private :
		typedef reverse_iterator<it> self;

	public :
		reverse_iterator(): it() {}
		reverse_iterator(const it &to_copy): it(to_copy) {}
		reverse_iterator(const self &to_copy): it(to_copy.p) {}
		self &operator=(const self &to_copy) {this->p = to_copy.p; return *this;}
		~reverse_iterator() {}
		self &operator++() {it tmp(*this); --tmp; return tmp;}
		self &operator++(int) {it tmp(*this); --tmp; return tmp;}
		self &operator--() {it tmp(*this); ++tmp; return tmp;}
		self &operator--(int) {it tmp(*this); ++tmp; return tmp;}
		reference operator*() const {it tmp(*this); return *tmp;}
		pointer operator->() const {it tmp(*this); return tmp;}
		self &operator+=(int add) {it tmp(*this); tmp -= add; return tmp;}
		self &operator-=(int sub) {it tmp(*this); tmp += sub; return tmp;}
};

#endif
