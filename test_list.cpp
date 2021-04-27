/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <tguilbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:17:37 by user42            #+#    #+#             */
/*   Updated: 2021/04/27 18:01:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cmath>
#include "list.hpp"
#include "vector.hpp"

bool single_digit (const int& value) { return (value<10); }

struct is_odd {
  bool operator() (const int& value) { return (value%2)==1; }
};

bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }

struct is_near {
  bool operator() (double first, double second)
  { return (fabs(first-second)<5.0); }
};

bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }

bool compare_nocase (const std::string& first, const std::string& second)
{
  unsigned int i=0;
  while ( (i<first.length()) && (i<second.length()) )
  {
    if (tolower(first[i])<tolower(second[i])) return true;
    else if (tolower(first[i])>tolower(second[i])) return false;
    ++i;
  }
  return ( first.length() < second.length() );
}

int main()
{
	//list constructor
	list<int> first;
	list<int> second (4,100);
	list<int> third (second.begin(),second.end());
	list<int> fourth (third);

	int myints[] = {16,2,77,29};
	list<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are: ";
	for (list<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
		std::cout << *it << ' ';

	std::cout << '\n';

	//list operator=
	list<int> first2 (3);
	list<int> second2 (5);

	second2 = first2;
	first2 = list<int>();

	std::cout << "Size of first2: " << int (first2.size()) << '\n';
	std::cout << "Size of second2: " << int (second2.size()) << '\n';

	//list begin/end
	int myints2[] = {75,23,65,42,13};
	list<int> mylist (myints2,myints2+5);

	std::cout << "mylist contains:";
	for (list<int>::iterator it=mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';

	//list rbegin/rend
	list<int> mylist2;
	for (int i=1; i<=5; ++i) mylist2.push_back(i);

	std::cout << "mylist2 backwards:";
	for (list<int>::reverse_iterator rit=mylist2.rbegin(); rit!=mylist2.rend(); ++rit)
		std::cout << ' ' << *rit;

	std::cout << '\n';

	//list empty
	list<int> mylist3;
	int sum (0);

	for (int i=1;i<=10;++i) mylist3.push_back(i);

	while (!mylist3.empty())
	{
		sum += mylist3.front();
		mylist3.pop_front();
	}

	std::cout << "total: " << sum << '\n';

	//list size
	list<int> myints3;
	std::cout << "0. size: " << myints3.size() << '\n';

	for (int i=0; i<10; i++) myints3.push_back(i);
	std::cout << "1. size: " << myints3.size() << '\n';

	myints3.insert (myints3.begin(),10,100);
	std::cout << "2. size: " << myints3.size() << '\n';

	myints3.pop_back();
	std::cout << "3. size: " << myints3.size() << '\n';	

	//list max_size
	std::cout << mylist.max_size() << std::endl;

	//list front
	list<int> mylist4;

	mylist4.push_back(77);
	mylist4.push_back(22);

	mylist4.front() -= mylist4.back();

	std::cout << "mylist4.front() is now " << mylist4.front() << '\n';

	//list back
	list<int> mylist5;

	mylist5.push_back(10);

	while (mylist5.back() != 0)
	{
		mylist5.push_back ( mylist5.back() -1 );
	}

	std::cout << "mylist5 contains:";
	for (list<int>::iterator it=mylist5.begin(); it!=mylist5.end() ; ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';

	//list assign
	list<int> first3;
	list<int> second3;

	first3.assign (7,100);

	second3.assign (first3.begin(),first3.end());

	int myints4[]={1776,7,4};
	first3.assign (myints4,myints4+3);

	std::cout << "Size of first3: " << int (first3.size()) << '\n';
	std::cout << "Size of second3: " << int (second3.size()) << '\n';

	//list push_front
	list<int> mylist6 (2,100);
	mylist6.push_front (200);
	mylist6.push_front (300);

	std::cout << "mylist6 contains:";
	for (list<int>::iterator it=mylist6.begin(); it!=mylist6.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';

	//list pop_front
	list<int> mylist7;
	mylist7.push_back (100);
	mylist7.push_back (200);
	mylist7.push_back (300);

	std::cout << "Popping out the elements in mylist7:";
	while (!mylist7.empty())
	{
	std::cout << ' ' << mylist7.front();
	mylist7.pop_front();
	}

	std::cout << "\nFinal size of mylist7 is " << mylist7.size() << '\n';

	//list pop_back
	list<int> mylist8;
	int sum2 (0);
	mylist8.push_back (100);
	mylist8.push_back (200);
	mylist8.push_back (300);

	while (!mylist8.empty())
	{
		sum2+=mylist8.back();
		mylist8.pop_back();
	}

	std::cout << "The elements of mylist8 summed " << sum2 << '\n';

	//list insert
	list<int> mylist9;
	list<int>::iterator it;

	for (int i=1; i<=5; ++i) mylist9.push_back(i);

	it = mylist9.begin();
	++it;
	mylist9.insert (it,10);
	mylist9.insert (it,2,20);
	--it;

	vector<int> myvector (2,30);
	mylist9.insert (it,myvector.begin(),myvector.end());

	std::cout << "mylist9 contains:";
	for (it=mylist9.begin(); it!=mylist9.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//list erase
	list<int> mylist10;
	list<int>::iterator it1,it2;

	for (int i=1; i<10; ++i) mylist10.push_back(i*10);

	it1 = it2 = mylist10.begin();
	for (int i = 0; i < 6; i++) it2++;
	++it1;

	it1 = mylist10.erase (it1);
	it2 = mylist10.erase (it2);
	++it1;
	--it2;

	mylist10.erase (it1,it2);

	std::cout << "mylist10 contains:";
	for (it1=mylist10.begin(); it1!=mylist10.end(); ++it1)
		std::cout << ' ' << *it1;
	std::cout << '\n';

	//list swap

	list<int> first4 (3,100);
	list<int> second4 (5,200);

	first4.swap(second4);

	std::cout << "first4 contains:";
	for (list<int>::iterator it=first4.begin(); it!=first4.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "second4 contains:";
	for (list<int>::iterator it=second4.begin(); it!=second4.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//list resize
	list<int> mylist11;

	for (int i=1; i<10; ++i) mylist11.push_back(i);

	mylist11.resize(5);
	mylist11.resize(8,100);
	mylist11.resize(12);

	std::cout << "mylist11 contains:";
	for (list<int>::iterator it=mylist11.begin(); it!=mylist11.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';

	//list clear
	list<int> mylist12;

	mylist12.push_back (100);
	mylist12.push_back (200);
	mylist12.push_back (300);

	std::cout << "mylist12 contains:";
	for (it=mylist12.begin(); it!=mylist12.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	mylist12.clear();
	mylist12.push_back (1101);
	mylist12.push_back (2202);

	std::cout << "mylist12 contains:";
	for (it=mylist12.begin(); it!=mylist12.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//list splice
	list<int> mylist13, mylist14;

	for (int i=1; i<=4; ++i)
		mylist13.push_back(i);

	for (int i=1; i<=3; ++i)
		mylist14.push_back(i*10);

	it = mylist13.begin();
	++it;

	mylist13.splice (it, mylist14);
	mylist14.splice (mylist14.begin(),mylist13, it);
	it = mylist13.begin();
	for (int i = 0; i < 3; i++) it++;

	mylist13.splice ( mylist13.begin(), mylist13, it, mylist13.end());

	std::cout << "mylist13 contains:";
	for (it=mylist13.begin(); it!=mylist13.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "mylist14 contains:";
	for (it=mylist14.begin(); it!=mylist14.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//list remove
	int myints5[]= {17,89,7,14};
	list<int> mylist15 (myints5,myints5+4);

	mylist15.remove(89);

	std::cout << "mylist15 contains:";
	for (list<int>::iterator it=mylist15.begin(); it!=mylist15.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//list remove_if
	int myints6[]= {15,36,7,17,20,39,4,1};
	list<int> mylist16 (myints6,myints6+8);

	mylist16.remove_if (single_digit);

	mylist16.remove_if (is_odd());

	std::cout << "mylist16 contains:";
	for (list<int>::iterator it=mylist16.begin(); it!=mylist16.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//list unique
	double mydoubles[]={ 12.15,  2.72, 73.0,  12.77,  3.14,
                       12.77, 73.35, 72.25, 15.3,  72.25 };
	list<double> mylist17 (mydoubles,mydoubles+10);
  
	mylist17.sort();
	mylist17.unique();
	mylist17.unique (same_integral_part);
	mylist17.unique (is_near());

	std::cout << "mylist17 contains:";
	for (list<double>::iterator it=mylist17.begin(); it!=mylist17.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//list merge
	list<double> first5, second5;

	first5.push_back (3.1);
	first5.push_back (2.2);
	first5.push_back (2.9);

	second5.push_back (3.7);
	second5.push_back (7.1);
	second5.push_back (1.4);

	first5.sort();
	second5.sort();

	first5.merge(second5);

	second5.push_back (2.1);

	first5.merge(second5,mycomparison);

	std::cout << "first5 contains:";
	for (list<double>::iterator it=first5.begin(); it!=first5.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//list sort
	list<std::string> mylist18;
	list<std::string>::iterator it4;
	mylist18.push_back ("one");
	mylist18.push_back ("two");
	mylist18.push_back ("Three");

	mylist18.sort();

	std::cout << "mylist18 contains:";
	for (it4=mylist18.begin(); it4!=mylist18.end(); ++it4)
		std::cout << ' ' << *it4;
	std::cout << '\n';

	mylist18.sort(compare_nocase);

	std::cout << "mylist18 contains:";
	for (it4=mylist18.begin(); it4!=mylist18.end(); ++it4)
		std::cout << ' ' << *it4;
	std::cout << '\n';

	//list reverse
	list<int> mylist19;

	for (int i=1; i<10; ++i) mylist19.push_back(i);

	mylist19.reverse();

	std::cout << "mylist19 contains:";
	for (list<int>::iterator it=mylist19.begin(); it!=mylist19.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';

	//list relational operator
	int lista[] = {10, 20, 30};
	list<int> a(lista, lista+3);
	int listb[] = {10, 20, 30};
	list<int> b(listb, listb+3);
	int listc[] = {30, 20, 10};
	list<int> c(listc, listc+3);

	
	if (a==b) std::cout << "a and b are equal\n";
	if (b!=c) std::cout << "b and c are not equal\n";
	if (b<c) std::cout << "b is less than c\n";
	if (c>b) std::cout << "c is greater than b\n";
	if (a<=b) std::cout << "a is less than or equal to b\n";
	if (a>=b) std::cout << "a is greater than or equal to b\n";

	//list swap template
	list<int> foo (3,100);
	list<int> bar (5,200);

	swap(foo,bar);

	std::cout << "foo contains:";
	for (list<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "bar contains:";
	for (list<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}
