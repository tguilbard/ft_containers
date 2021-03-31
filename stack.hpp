/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <tguilbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:21:14 by user42            #+#    #+#             */
/*   Updated: 2021/03/29 10:45:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

template<typename T>
class stack<T>:
{
	private :
	size_t	_size;
	T*		_first;

	public :
	stack();
	bool empty();
	size_t size();
	T top();
	cosnt T top() const;
	void push(const T &val);
	void pop();


};

template<typename T>
stack<T>::stack(): _size (0), _first (0)

template<typename T>
bool stack<T>::empty()
{
	return (_size);
}

template<typename T>
size_t stack<T>::size()
{
	return (_size);
}

template<typename T>
T stack<T>::top()
{
	return ()
}

#endif
