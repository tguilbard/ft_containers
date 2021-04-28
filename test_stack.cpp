/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <tguilbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 10:43:00 by user42            #+#    #+#             */
/*   Updated: 2021/04/28 11:11:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "stack.hpp"
#include "vector.hpp"
#include "list.hpp"

int main()
{
	//stack constructor
	list<int> mylist (3,100);
	vector<int> myvector (2,200);

	stack<int> first;
	stack<int> second (mylist);

	stack<int,vector<int> > third;
	stack<int,vector<int> > fourth (myvector);

	std::cout << "size of first: " << first.size() << '\n';
	std::cout << "size of second: " << second.size() << '\n';
	std::cout << "size of third: " << third.size() << '\n';
	std::cout << "size of fourth: " << fourth.size() << '\n';

	//stack empty
	stack<int> mystack;
	int sum (0);

	for (int i=1;i<=10;i++) mystack.push(i);

	while (!mystack.empty())
	{
	sum += mystack.top();
	mystack.pop();
	}

	std::cout << "total: " << sum << '\n';

	//stack size
	stack<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i=0; i<5; i++) myints.push(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.pop();
	std::cout << "2. size: " << myints.size() << '\n';

	//stack top
	stack<int> mystack2;

	mystack2.push(10);
	mystack2.push(20);

	mystack2.top() -= 5;

	std::cout << "mystack2.top() is now " << mystack2.top() << '\n';

	//stack push/pop
	stack<int> mystack3;

	for (int i=0; i<5; ++i) mystack3.push(i);

	std::cout << "Popping out elements...";
	while (!mystack3.empty())
	{
		std::cout << ' ' << mystack3.top();
		mystack3.pop();
	}
	std::cout << '\n';

	//stack relational operator (= vector relational operator)
	vector<int> ctnr1 (3,100);
	vector<int> ctnr2 (2,200);
	stack<int, vector<int> > foo(ctnr1);
	stack<int, vector<int> > bar(ctnr2);

	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

	return 0;
}
