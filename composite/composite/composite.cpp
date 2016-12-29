#include "composite.hpp"
#include<iostream>
using namespace std;

void Branch::add(Component* com)
{
    if(com!=nullptr)
    {
        c_List.push_back(com);
    }
}

void Branch::remove(Component* com)
{
    if(com!=nullptr)
    {
        c_List.remove(com);
    }
}

void Branch::display(string str)
{
    list<Component* >::iterator itr = c_List.begin();
    cout<<str<<c_Name<<endl;
    str = str + str;
    for ( ; itr != c_List.end(); itr++)
    {
        (*itr)->display(str);
    }
}

void Leaf::display(string str)
{
    cout<<str<<c_Name<<endl;
}


