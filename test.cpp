#include "set.h"
#include "map.h"

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

	mySTL::multimap<int, int> map;
	map.insert(1,2);
	int temp = map[1];
	map[1] = 5;
	std::cout << map[2] << std::endl;
}