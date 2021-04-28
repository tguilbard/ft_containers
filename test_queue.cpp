/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_queue.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <tguilbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 11:20:07 by user42            #+#    #+#             */
/*   Updated: 2021/04/28 11:32:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "vector.hpp"
#include "list.hpp"
#include "queue.hpp"

int main()
{
	//queue constructor
	list<int> mylist (3,100);
	vector<int> myvector (2,200);

	queue<int> first;
	queue<int> second (mylist);

	queue<int,vector<int> > third;
	queue<int,vector<int> > fourth (myvector);

	std::cout << "size of first: " << first.size() << '\n';
	std::cout << "size of second: " << second.size() << '\n';
	std::cout << "size of third: " << third.size() << '\n';
	std::cout << "size of fourth: " << fourth.size() << '\n';

	//queue empty
	queue<int> myqueue;
	int sum (0);

	for (int i=1;i<=10;i++) myqueue.push(i);

	while (!myqueue.empty())
	{
		sum += myqueue.front();
		myqueue.pop();
	}

	std::cout << "total: " << sum << '\n';

	//queue size
	queue<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i=0; i<5; i++) myints.push(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.pop();
	std::cout << "2. size: " << myints.size() << '\n';

	//queue front
	queue<int> myqueue2;

	myqueue2.push(77);
	myqueue2.push(16);

	myqueue2.front() -= myqueue2.back();

	std::cout << "myqueue2.front() is now " << myqueue2.front() << '\n';

	//queue back
	queue<int> myqueue3;

	myqueue3.push(12);
	myqueue3.push(75);

	myqueue3.back() -= myqueue3.front();

	std::cout << "myqueue3.back() is now " << myqueue3.back() << '\n';

	//queue push/pop (stack push/pop (reverse queue pop != stack pop))
	queue<int> myqueue4;

	for (int i=0; i<5; ++i) myqueue4.push(i);

	std::cout << "Popping out elements...";
	while (!myqueue4.empty())
	{
	std::cout << ' ' << myqueue4.front();
	myqueue4.pop();
	}
	std::cout << '\n';

	//queue relational operator (= vector relational operator)
	vector<int> ctnr1 (3,100);
	vector<int> ctnr2 (2,200);
	queue<int, vector<int> > foo(ctnr1);
	queue<int, vector<int> > bar(ctnr2);

	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

	return 0;
}
