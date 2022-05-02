#include <iostream>
#include <string>
#include <deque>

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
#endif

int main()
{
	ft::map<int, int> myMap0;

	std::cout << "==== Empty map myMap0 ===="<< std::endl;
	std::cout << "ft::map<int, int> myMap0;" << std::endl;
	std::cout << std::endl;
	std::cout << "myMap0.empty() = " << myMap0.empty() << std::endl;
	std::cout << "myMap0.size() =  " << myMap0.size() << std::endl;
	std::cout << "myMap0.max_size() =  " << myMap0.max_size() << std::endl;
	std::cout << "myMap0.clear()" << std::endl;  myMap0.clear();
	std::cout << "myMap0[0] =  " << myMap0[0] << std::endl;
	std::cout << "myMap0.insert(ft::make_pair(3, 9))" << std::endl; myMap0.insert(ft::make_pair(3, 9));
	std::cout << "myMap0.size() = " << myMap0.size() << std::endl;
	std::cout << "myMap0.clear() " << std::endl;  myMap0.clear();
	std::cout << "myMap0.size() = " << myMap0.size() << std::endl;

	myMap0.insert(ft::make_pair(3, 30));
	myMap0.insert(ft::make_pair(2, 20));
	myMap0.insert(ft::make_pair(9, 90));
	myMap0.insert(ft::make_pair(7, 70));
	myMap0.insert(ft::make_pair(-1, -10));

	ft::map<int, int>::iterator	it = myMap0.begin();
	for ( ; it != myMap0.end(); it++)
		std::cout << it->first << ": " << it->second << "  ";
	std::cout << std::endl;

	std::cout << "myMap0.find(7)->second = " << myMap0.find(7)->second << std::endl;	
	std::cout << "(myMap0.find(4) == myMap0.end()) = " << (myMap0.find(4) == myMap0.end()) << std::endl;

	ft::map<char,int> mymap;
  	ft::map<char,int>::iterator it1;

	mymap['a']=50;
	mymap['b']=100;
	mymap['c']=150;
	mymap['d']=200;

	it1 = mymap.find('b');
	if (it1 != mymap.end())
		mymap.erase(it1);

	// print content:
	std::cout << "elements in mymap:" << '\n';
	std::cout << "a => " << mymap.find('a')->second << '\n';
	std::cout << "c => " << mymap.find('c')->second << '\n';
	std::cout << "d => " << mymap.find('d')->second << '\n';

	it1 = mymap.begin();
	for ( ; it1 != mymap.end(); it1++)
		std::cout << it1->first << ": " << it1->second << "  ";
	std::cout << std::endl;

	ft::map<int, int> map_int;
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}

	std::cout << std::endl;
	std::cout << "TEST END" << std::endl;
}