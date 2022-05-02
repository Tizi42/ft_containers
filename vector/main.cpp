#include <iostream>
#include <string>
#include <deque>

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
	std::cout << "myMap0.empty(): " << myMap0.empty() << std::endl;
	std::cout << "myMap0.size(): " << myMap0.size() << std::endl;
	std::cout << "myMap0.max_size(): " << myMap0.max_size() << std::endl;
	std::cout << "myMap0.clear()" << std::endl;  myMap0.clear();
	std::cout << "myMap0[0]: " << myMap0[0] << std::endl;
	std::cout << "myMap0.insert(ft::make_pair(3, 9))" << std::endl; myMap0.insert(ft::make_pair(3, 9));
	std::cout << "myMap0.size(): " << myMap0.size() << std::endl;
	std::cout << "myMap0.clear()" << std::endl;  myMap0.clear();
	std::cout << "myMap0.size(): " << myMap0.size() << std::endl;

	myMap0.insert(ft::make_pair(3, 30));
	myMap0.insert(ft::make_pair(2, 20));
	myMap0.insert(ft::make_pair(9, 90));
	myMap0.insert(ft::make_pair(7, 70));
	myMap0.insert(ft::make_pair(-1, -10));

	ft::map<int, int>::iterator	it = myMap0.begin();
//	for ( ; it != myMap0.end(); it++)

	
		std::cout << it->first << ": " << it->second << "  ";
		it++;
		std::cout << it->first << ": " << it->second << "  ";
		it++;
		std::cout << it->first << ": " << it->second << "  ";
		it++;
		std::cout << it->first << ": " << it->second << "  ";
		it++;
		std::cout << it->first << ": " << it->second << "  ";
		it++;
		std::cout << it->first << ": " << it->second << "  ";
		it++;
		std::cout << it->first << ": " << it->second << "  ";
		it++;
	std::cout << std::endl;


	std::cout << std::endl;
	std::cout << "TEST END" << std::endl;
}