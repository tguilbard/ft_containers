/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <tguilbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:11:36 by user42            #+#    #+#             */
/*   Updated: 2021/04/19 11:47:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "vector.hpp"

int main()
{
	//vector constructor
	vector<int> first;
	vector<int> second (4, 100);
	vector<int> third (second.begin(),second.end());
	vector<int> fourth (third);

	int myints[] = {16,2,77,29};
	vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are:";
	for (vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';

	//vector assignement
	vector<int> foo (3,0);
	vector<int> bar (5,0);

	bar = foo;
	foo = vector<int>();

	std::cout << "Size of foo: " << int(foo.size()) << '\n';
	std::cout << "Size of bar: " << int(bar.size()) << '\n';

	//vector begin/end
	vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);

	std::cout << "myvector contains:";
	for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//vector rbegin/rend
	vector<int> myvector2 (5);

	int i=0;

	vector<int>::reverse_iterator rit = myvector2.rbegin();
	for (; rit != myvector2.rend(); ++rit)
		*rit = ++i;

	std::cout << "myvector2 contains:";
	for (vector<int>::iterator it = myvector2.begin(); it != myvector2.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//vector size
	vector<int> myints2;
	std::cout << "0. size: " << myints2.size() << '\n';

	for (int i=0; i<10; i++) myints2.push_back(i);
	std::cout << "1. size: " << myints2.size() << '\n';

	myints2.insert (myints2.end(),10,100);
	std::cout << "2. size: " << myints2.size() << '\n';

	myints2.pop_back();
	std::cout << "3. size: " << myints2.size() << '\n';

	return 0;
}
