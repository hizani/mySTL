#include "set.h"

int main()
{
    //multiset
    mySTL::multiset<int>* mset = new mySTL::multiset<int>();
    
    int a = 22;
    int b = 11;
    
    mset->insert(a);
	mset->insert(b);
	mset->insert(12);
	mset->insert(44);
	mset->insert(55);
	mset->insert(2);
	mset->remove(a);
	mset->remove(11);
	mset->remove(2);
    
    mset->find(4);

    mset->contains(12);

    //set
    mySTL::set<int>* set = new mySTL::set<int>();

    set->insert(a);
    set->insert(b);
    set->insert(4);
    set->insert(45);
    set->insert(12);
    set->insert(11);
    set->insert(5);
    
    set->find(4);

    set->contains(12);

    
}