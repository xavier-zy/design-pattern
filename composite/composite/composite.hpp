
#ifndef composite_hpp
#define composite_hpp

#include <list>
using std::list;

#include <string>
using std::string;

#include <iostream>
using namespace std;

class Component
{
public:
    Component(char* name):c_Name(name){}
    virtual void add(Component* com){}
    virtual void remove(Component* com){}
    virtual void display(string str){}
    
protected:
    char* c_Name;
    list<Component* > c_List;
};

class Branch:public Component{
public:
    Branch(char* name):Component(name){}
    virtual void add(Component* com);
    virtual void remove(Component* com);
    virtual void display(string str);
    
};

class Leaf:public Component{
public:
    Leaf(char* name):Component(name){}
    virtual void display(string str);
    
    
};


#endif /* composite_hpp */
