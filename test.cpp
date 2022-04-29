#include <map>
#include <iostream>

int main()
{
	std::map<int, int> a;

	a.insert(std::make_pair(3, 0));
	a.insert(std::make_pair(7, 0));
	a.insert(std::make_pair(4, 0));
	a.insert(std::make_pair(0, 0));
	a.insert(std::make_pair(-9, 0));
	a.insert(std::make_pair(-1, 0));
	a[2] = 0;
	
	for (std::map<int, int>::iterator it = a.begin(); it != a.end(); it++)
	{
		std::cout << it->first << std::endl;
		std::cout << &*it << std::endl;
	}

	std::map<int, int>::iterator it = a.end();
	std::cout << &*it << std::endl;
	it--;
	std::cout << &*it << std::endl;
	
	std::map<int, int>::iterator it2 = a.begin();
	std::cout << &*it2 << std::endl;
	it2++;
	std::cout << &*it2 << std::endl;

	std::map<int, int>::iterator	lo = a.lower_bound(1);
	std::map<int, int>::iterator	up = a.upper_bound(1);

	std::cout << lo->first << std::endl;
	std::cout << up->first << std::endl;

}