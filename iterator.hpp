/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revers.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:02:17 by user42            #+#    #+#             */
/*   Updated: 2021/07/04 20:00:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERS_HPP
# define REVERS_HPP

namespace ft
{

struct Iterator_Trait {};

template<typename it>
class rvrs_iterator: public it
{
	public :
		using typename it::value_type;
		using typename it::pointer;
		using typename it::reference;
	private :
		typedef rvrs_iterator<it> self;

	public :
		rvrs_iterator(): it() {}
		rvrs_iterator(pointer ptr) : it(ptr) {}
		rvrs_iterator(const it &to_copy): it(to_copy) {}
		rvrs_iterator(const self &to_copy): it(to_copy) {}
		~rvrs_iterator() {}
		self &operator++() {it::operator--(); return *this;}
		self &operator++(int) {it::operator--(); return *this;}
		self &operator--() {it::operator++(); return *this;}
		self &operator--(int) {it::operator++(); return *this;}

		self &operator+=(int add) {it::operator-=(add); return *this;}
		self &operator-=(int sub) {it::operator+=(sub); return *this;}
};

}

#endif
