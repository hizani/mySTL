#include "set.h"

int main()
{
    //multiset
    mySTL::multiset<int>* mset = new mySTL::multiset<int>();
    
    int a = 23;
    int b = 71;
    
    mset->insert(a);
    mset->insert(b);
    mset->insert(4);
    mset->insert(45);
    mset->insert(12);
    mset->insert(11);
    mset->insert(5);
    
    mset->find(4);

    mset->contains(12);

    //set
    
}