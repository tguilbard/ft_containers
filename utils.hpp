/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <tguilbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:02:03 by user42            #+#    #+#             */
/*   Updated: 2021/07/04 14:45:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{

template<bool, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type;};

template <bool is_integral, typename T>
struct is_integral_res {
	typedef T type;
	static const bool value = is_integral;
};

template <typename>
struct is_integral_type : public is_integral_res<false, bool> {};

template <>
struct is_integral_type<bool> : public is_integral_res<true, bool> {};

template <>
struct is_integral_type<char> : public is_integral_res<true, char> {};

template <>
struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};

template <>
struct is_integral_type<short int> : public is_integral_res<true, short int> {};
    
template <>
struct is_integral_type<int> : public is_integral_res<true, int> {};

template <>
struct is_integral_type<long int> : public is_integral_res<true, long int> {};

template <>
struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};

template <>
struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};

template <>
struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};

template <>
struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};

template <>
struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};

template <>
struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};

template <typename T>
struct is_integral : public is_integral_type<T> { };

template <class T1, class T2>
struct pair
{
	public :
		typedef T1 first_type;
		typedef T2 second_type;

		first_type	first;
		second_type	second;

		pair()
		: first(), second()
		{}

		template<class U, class V>
		pair (const pair<U, V>& pr)
		: first(pr.first), second(pr.second)
		{}

		pair (const first_type& a, const second_type& b)
		: first(a), second(b)
		{}

		pair& operator= (const pair& pr)
		{
			if (this == &pr)
				return (*this);
			first = pr.first;
			second = pr.second;
			return (*this);
		}
};

template <class T1,class T2>
pair<T1,T2> make_pair (T1 x, T2 y)
{
	return ( pair<T1,T2>(x,y) );
}

template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
	while (first1!=last1) {
		if (!(*first1 == *first2))
			return false;
		++first1;
		++first2;
	}
	return true;
}

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2)
{
	while (first1!=last1)
	{
		if (first2==last2 || *first2<*first1)
			return false;
		else if (*first1<*first2)
			return true;
		++first1;
		++first2;
	}
	return (first2!=last2);
}

}

#endif
