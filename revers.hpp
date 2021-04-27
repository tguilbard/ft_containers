/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revers.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <tguilbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:02:17 by user42            #+#    #+#             */
/*   Updated: 2021/04/24 11:01:09 by user42           ###   ########.fr       */
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
		reverse_iterator(pointer ptr) : it(ptr) {}
		reverse_iterator(const it &to_copy): it(to_copy) {}
		reverse_iterator(const self &to_copy): it(to_copy) {}
		~reverse_iterator() {}
		self &operator++() {it::operator--(); return *this;}
		self &operator++(int) {it::operator--(); return *this;}
		self &operator--() {it::operator++(); return *this;}
		self &operator--(int) {it::operator++(); return *this;}

		self &operator+=(int add) {it::operator-=(add); return *this;}
		self &operator-=(int sub) {it::operator+=(sub); return *this;}
};

#endif
