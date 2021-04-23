/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <tguilbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:11:36 by user42            #+#    #+#             */
/*   Updated: 2021/04/23 10:16:21 by user42           ###   ########.fr       */
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

	//vector size/max_size/capacity
	vector<int> myints2;
	std::cout << "0. size: " << myints2.size() << '\n';

	for (int i=0; i<10; i++) myints2.push_back(i);
	std::cout << "1. size: " << myints2.size() << '\n';

	myints2.insert (myints2.end(),10,100);
	std::cout << "2. size: " << myints2.size() << '\n';

	myints2.pop_back();
	std::cout << "3. size: " << myints2.size() << '\n';


	vector<int> myvector3;

	for (int i=0; i<100; i++) myvector3.push_back(i);

	std::cout << "size: " << myvector3.size() << "\n";
	std::cout << "capacity: " << myvector3.capacity() << "\n";
	std::cout << "max_size: " << myvector3.max_size() << "\n";

	//vector resize
	vector<int> myvector4;

	for (int i=1;i<10;i++) myvector4.push_back(i);

	myvector4.resize(5);
	myvector4.resize(8,100);
	myvector4.resize(12);


	std::cout << "myvector4 contains:";
	for (size_t i=0; i<myvector4.size();i++)
		std::cout << ' ' << myvector4[i];
	std::cout << '\n';

	//vector empty
	vector<int> myvector5;
	int sum (0);

	for (int i=1;i<=10;i++) myvector5.push_back(i);

	while (!myvector5.empty())
	{
		sum += myvector5.back();
		myvector5.pop_back();
	}

	std::cout << "total: " << sum << '\n';

	//vector reserve
	vector<int>::size_type sz;

	vector<int> foo2;
	sz = foo2.capacity();
	std::cout << "making foo2 grow:\n";
	for (int i=0; i<100; ++i) {
		foo2.push_back(i);
		if (sz!=foo2.capacity()) {
			sz = foo2.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	vector<int> bar2;
	sz = bar2.capacity();
	bar2.reserve(100);
	std::cout << "making bar2 grow:\n";
	for (int i=0; i<100; ++i) {
		bar2.push_back(i);
		if (sz!=bar2.capacity()) {
			sz = bar2.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	//vector operator[]

	vector<int> myvector6 (10);

	vector<int>::size_type sz2 = myvector6.size();

	for (unsigned i=0; i<sz2; i++) myvector6[i]=i;

	for (unsigned i=0; i<sz2/2; i++)
	{
		int temp;
		temp = myvector6[sz2-1-i];
		myvector6[sz2-1-i]=myvector6[i];
		myvector6[i]=temp;
	}

	std::cout << "myvector6 contains:";
	for (unsigned i=0; i<sz2; i++)
		std::cout << ' ' << myvector6[i];
	std::cout << '\n';

	// vector at
	vector<int> myvector7 (10);

	for (unsigned i=0; i<myvector7.size(); i++)
		myvector7.at(i)=i;

	std::cout << "myvector7 contains:";
	for (unsigned i=0; i<myvector7.size(); i++)
		std::cout << ' ' << myvector7.at(i);
	std::cout << '\n';

	// vector front
	vector<int> myvector8;

	myvector8.push_back(78);
	myvector8.push_back(16);

	myvector8.front() -= myvector8.back();

	std::cout << "myvector8.front() is now " << myvector8.front() << '\n';

	//vector back
	vector<int> myvector9;

	myvector9.push_back(10);

	while (myvector9.back() != 0)
	{
		myvector9.push_back ( myvector9.back() -1 );
	}

	std::cout << "myvector9 contains:";
	for (unsigned i=0; i<myvector9.size() ; i++)
		std::cout << ' ' << myvector9[i];
	std::cout << '\n';

	//vector assign
	vector<int> first2;
	vector<int> second2;
	vector<int> third2;

	first2.assign (7,100);

	vector<int>::iterator it;
	it=first2.begin()+1;

	second2.assign (it,first2.end()-1);

	int mylist[] = {1776,7,4};
	third2.assign (mylist,mylist+3);

	std::cout << "Size of first2: " << int (first2.size()) << '\n';
	std::cout << "Size of second2: " << int (second2.size()) << '\n';
	std::cout << "Size of third2: " << int (third2.size()) << '\n';

	//vector pop_back
	vector<int> myvector10;
	int sum2 (0);
	myvector10.push_back (100);
	myvector10.push_back (200);
	myvector10.push_back (300);

	while (!myvector10.empty())
	{
		sum2+=myvector10.back();
		myvector10.pop_back();
	}

	std::cout << "The elements of myvector10 add up to " << sum2 << '\n';

	//vector insert
	vector<int> myvector11 (3,100);
	vector<int>::iterator it2;

	it2 = myvector11.begin();
	it2 = myvector11.insert ( it2 , 200 );
	myvector11.insert (it2,2,300);

	it2 = myvector11.begin();

	vector<int> anothervector (2,400);
	myvector11.insert (it2+2,anothervector.begin(),anothervector.end());
	
	int myarray [] = { 501,502,503 };
	myvector11.insert (myvector11.begin(), myarray, myarray+3);

	std::cout << "myvector11 contains:";
	for (it2=myvector11.begin(); it2<myvector11.end(); it2++)
		std::cout << ' ' << *it2;
	std::cout << '\n';

	//vector erase
	vector<int> myvector12;

	for (int i=1; i<=10; i++) myvector12.push_back(i);

	myvector12.erase (myvector12.begin()+5);

	myvector12.erase (myvector12.begin(),myvector12.begin()+3);

	std::cout << "myvector12 contains:";
	for (unsigned i=0; i<myvector12.size(); ++i)
		std::cout << ' ' << myvector12[i];
	std::cout << '\n';

	//vector swap
	vector<int> foo3 (3,100);
	vector<int> bar3 (5,200);

	foo3.swap(bar3);

	std::cout << "foo3 contains:";
	for (unsigned i=0; i<foo3.size(); i++)
		std::cout << ' ' << foo3[i];
	std::cout << '\n';

	std::cout << "bar3 contains:";
	for (unsigned i=0; i<bar3.size(); i++)
		std::cout << ' ' << bar3[i];
	std::cout << '\n';

	//vector clear
	vector<int> myvector13;
	myvector13.push_back (100);
	myvector13.push_back (200);
	myvector13.push_back (300);

	std::cout << "myvector13 contains:";
	for (unsigned i=0; i<myvector13.size(); i++)
		std::cout << ' ' << myvector13[i];
	std::cout << '\n';

	myvector13.clear();
	myvector13.push_back (1101);
	myvector13.push_back (2202);

	std::cout << "myvector13 contains:";
	for (unsigned i=0; i<myvector13.size(); i++)
		std::cout << ' ' << myvector13[i];
	std::cout << '\n';

	//vector relational operator
	vector<int> foo4 (3,100);
	vector<int> bar4 (2,200);

	if (foo4==bar4) std::cout << "foo4 and bar are equal\n";
	if (foo4!=bar4) std::cout << "foo4 and bar are not equal\n";
	if (foo4< bar4) std::cout << "foo4 is less than bar\n";
	if (foo4> bar4) std::cout << "foo4 is greater than bar\n";
	if (foo4<=bar4) std::cout << "foo4 is less than or equal to bar\n";
	if (foo4>=bar4) std::cout << "foo4 is greater than or equal to bar\n";

	//vector swap fonction
	vector<int> foo5 (3,100);
	vector<int> bar5 (5,200);

	swap(foo5, bar5);

	std::cout << "foo5 contains:";
	for (vector<int>::iterator it = foo5.begin(); it!=foo5.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "bar5 contains:";
	for (vector<int>::iterator it = bar5.begin(); it!=bar5.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}
