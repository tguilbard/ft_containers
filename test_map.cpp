/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 09:30:28 by user42            #+#    #+#             */
/*   Updated: 2021/07/05 12:28:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

#ifndef TEST
	#include <map>
	using namespace std;
#else
	#include "map.hpp"
	using namespace ft;
#endif

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
bool	operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};

int	main ()
{
	struct timespec start, end;
	
	clock_gettime(CLOCK_MONOTONIC, &start);

	//map constructor
	map<char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;

	map<char,int> second (first.begin(),first.end());

	map<char,int> third (second);

	map<char,int,classcomp> fourth;

	bool(*fn_pt)(char,char) = fncomp;
	map<char,int,bool(*)(char,char)> fifth (fn_pt);

	//map operator=
	map<char,int> first2;
	map<char,int> second2;

	first2['x']=8;
	first2['y']=16;
	first2['z']=32;

	second2=first2;
	first2=map<char,int>();

	std::cout << "Size of first2: " << first2.size() << '\n';
	std::cout << "Size of second2: " << second2.size() << '\n';

	//map begin/end
	map<char,int> mymap;

	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;

	for (map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';	

	//map rbegin/rend
	map<char,int> mymap2;

	mymap2['x'] = 100;
	mymap2['y'] = 200;
	mymap2['z'] = 300;

	map<char,int>::reverse_iterator rit;
	for (rit=mymap2.rbegin(); rit!=mymap2.rend(); ++rit)
		std::cout << rit->first << " => " << rit->second << '\n';

	//map empty
	map<char,int> mymap3;

	mymap3['a']=10;
	mymap3['b']=20;
	mymap3['c']=30;

	while (!mymap3.empty())
	{
		std::cout << mymap3.begin()->first << " => " << mymap3.begin()->second << '\n';
		mymap3.erase(mymap3.begin());
	}

	//map size
	map<char,int> mymap4;
	mymap4['a']=101;
	mymap4['b']=202;
	mymap4['c']=302;

	std::cout << "mymap4.size() is " << mymap4.size() << '\n';

	//map max_size
	int i;
	map<int,int> mymap5;

	if (mymap5.max_size()>1000)
	{
		for (i=0; i<1000; i++) mymap5[i]=0;
		std::cout << "The map contains 1000 elements.\n";
	}
	else std::cout << "The map could not hold 1000 elements.\n";

	mymap5.clear();

	//map operator[]
	map<char,std::string> mymap6;

	mymap6['a']="an element";
	mymap6['b']="another element";
	mymap6['c']=mymap6['b'];

	std::cout << "mymap6['a'] is " << mymap6['a'] << '\n';
	std::cout << "mymap6['b'] is " << mymap6['b'] << '\n';
	std::cout << "mymap6['c'] is " << mymap6['c'] << '\n';
	std::cout << "mymap6['d'] is " << mymap6['d'] << '\n';

	std::cout << "mymap6 now contains " << mymap6.size() << " elements.\n";

	//map insert
	map<char,int> mymap7;

	mymap7.insert (pair<char,int>('a',100) );
	mymap7.insert (pair<char,int>('z',200) );

	pair<map<char,int>::iterator,bool> ret;
	ret = mymap7.insert (pair<char,int>('z',500) );
	if (ret.second==false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}

	map<char,int>::iterator it = mymap.begin();
	mymap7.insert (it, pair<char,int>('b',300));
	mymap7.insert (it, pair<char,int>('c',400));

	map<char,int> anothermap;
	anothermap.insert(mymap7.begin(),mymap7.find('c'));

	std::cout << "mymap7 contains:\n";
	for (it=mymap7.begin(); it!=mymap7.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it=anothermap.begin(); it!=anothermap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	//map erase
	map<char,int> mymap8;

	mymap8['a']=10;
	mymap8['b']=20;
	mymap8['c']=30;
	mymap8['d']=40;
	mymap8['e']=50;
	mymap8['f']=60;
	
	it=mymap8.find('b');
	mymap8.erase (it);

	mymap8.erase ('c');

	it=mymap8.find ('e');
	mymap8.erase ( it, mymap8.end() );

	if (mymap8.find('a') == mymap8.end())
		std::cout << "merde" << std::endl;
		
	for (it=mymap8.begin(); it!=mymap8.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';


	//map swap
	map<char,int> foo,bar;

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

	foo.swap(bar);

	std::cout << "foo contains:\n";
	for (map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "bar contains:\n";
	for (map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	//map clear
	map<char,int> mymap9;

	mymap9['x']=100;
	mymap9['y']=200;
	mymap9['z']=300;

	std::cout << "mymap9 contains:\n";
	for (map<char,int>::iterator it=mymap9.begin(); it!=mymap9.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	mymap9.clear();
	mymap9['a']=1101;
	mymap9['b']=2202;

	std::cout << "mymap9 contains:\n";
	for (map<char,int>::iterator it=mymap9.begin(); it!=mymap9.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	//map key_comp
	map<char,int> mymap10;

	map<char,int>::key_compare mycomp = mymap10.key_comp();

	mymap10['a']=100;
	mymap10['b']=200;
	mymap10['c']=300;

	std::cout << "mymap10 contains:\n";

	char highest = mymap10.rbegin()->first;

	it = mymap10.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( mycomp((*it++).first, highest) );

	//map value_comp
	map<char,int> mymap11;

	mymap11['x']=1001;
	mymap11['y']=2002;
	mymap11['z']=3003;

	std::cout << "mymap11 contains:\n";

	pair<char,int> highest2 = *mymap11.rbegin();

	it = mymap11.begin();
	do {
	std::cout << it->first << " => " << it->second << '\n';
	} while ( mymap11.value_comp()(*it++, highest2) );

	//map find
	map<char,int> mymap12;

	mymap12['a']=50;
	mymap12['b']=100;
	mymap12['c']=150;
	mymap12['d']=200;

	it = mymap12.find('b');
	if (it != mymap12.end())
		mymap12.erase (it);

	std::cout << "elements in mymap12:" << '\n';
	std::cout << "a => " << mymap12.find('a')->second << '\n';
	std::cout << "c => " << mymap12.find('c')->second << '\n';
	std::cout << "d => " << mymap12.find('d')->second << '\n';

	//map count
	map<char,int> mymap13;
	char c;

	mymap13 ['a']=101;
	mymap13 ['c']=202;
	mymap13 ['f']=303;

	for (c='a'; c<'h'; c++)
	{
		std::cout << c;
		if (mymap13.count(c)>0)
			std::cout << " is an element of mymap13.\n";
		else 
			std::cout << " is not an element of mymap13.\n";
	}

	//map lower_bound/upper_bound
	map<char,int> mymap14;
	map<char,int>::iterator itlow,itup;

	mymap14['a']=20;
	mymap14['b']=40;
	mymap14['c']=60;
	mymap14['d']=80;
	mymap14['e']=100;

	itlow=mymap14.lower_bound ('b');
	itup=mymap14.upper_bound ('d');

	mymap14.erase(itlow,itup);

	for (map<char,int>::iterator it=mymap14.begin(); it!=mymap14.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	//map equal_range
	map<char,int> mymap15;

	mymap15['a']=10;
	mymap15['b']=20;
	mymap15['c']=30;

	pair<map<char,int>::iterator,map<char,int>::iterator> ret2;
	ret2 = mymap15.equal_range('b');

	std::cout << "lower bound points to: ";
	std::cout << ret2.first->first << " => " << ret2.first->second << '\n';

	std::cout << "upper bound points to: ";
	std::cout << ret2.second->first << " => " << ret2.second->second << '\n';

	//map get_allocator
	int psize;
	map<char,int> mymap16;
	pair<const char,int>* p;

	p=mymap16.get_allocator().allocate(5);

	psize = sizeof(map<char,int>::value_type)*5;

	std::cout << "The allocated array has a size of " << psize << " bytes.\n";

	mymap16.get_allocator().deallocate(p,5);

	clock_gettime(CLOCK_MONOTONIC, &end);
	
	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e9;
	time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
	
	std::cout << " execution time: " << std::fixed << time_taken << std::endl;
	
	return 0;
}
