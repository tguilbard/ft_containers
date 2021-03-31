/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <tguilbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:11:36 by user42            #+#    #+#             */
/*   Updated: 2021/03/31 13:28:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "vector.hpp"

int main()
{
	vector<int> first;                                // empty vector of ints
	vector<int> second (4, 100);                       // four ints with value 100
	vector<int> third (second.begin(),second.end());  // iterating through second
	vector<int> fourth (third);                       // a copy of third

/*
	int myints[] = {16,2,77,29};
	std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are:";
	for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';
*/
	return 0;
}
