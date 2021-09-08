#include "set.h"
#include "map.h"
#include "vector.h"
#include "list.h"

#include <iostream>
int main()
{
	int num1 = 22;
	int num2 = 11;
	mySTL::multiset<int>* m = new mySTL::multiset<int>();
	m->insert(num1);
	m->insert(num2);
	m->insert(14);
	m->insert(33);
	m->insert(48);
	m->insert(2);
	m->insert(12);
	m->insert(44);
	m->insert(76);
	m->insert(2);
	m->insert(28);
	m->insert(44);
	m->insert(55);
	m->insert(2);
	m->remove(num1);

	m->remove(14);

	m->clear();
	m->insert(22);

	delete m;

	mySTL::set<int>* s = new mySTL::set<int>();
	s->insert(1);
	s->insert(15);
	s->insert(18);
	s->insert(22);
	s->insert(3);
	s->insert(3);

	delete s;

	mySTL::multimap<int, int> multimap;
	multimap.insert(1, 2);
	int tempmm = multimap[1];
	multimap[1] = 5;
	std::cout << multimap[1] << std::endl;

	mySTL::map<int, int> map;
	map.insert(1, 2);
	int tempm = map[1];
	map[1] = 5;
	map[1] = 5;
	std::cout << map[1] << std::endl;

	mySTL::vector<int> vec;
	vec.insert(10);
	vec.insert(22);
	vec.remove(0);
	auto biba = vec[0];

	mySTL::list<int> list;
	list.push_front(1);
	list.push_back(3);
	list.push_back(5);
	list.push_back(7);
	list.push_back(22);
	list.push_back(41);
	list.push_back(58);

	list.remove(100);
	list.remove(4);
	list.insert(505, 5);

	std::cout << list[0] << std::endl;
	std::cout << list[3] << std::endl;
}