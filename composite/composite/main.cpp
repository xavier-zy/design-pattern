#include <iostream>
#include <string>
#include <vector>
#include "composite.hpp"

using namespace std;

int main()
{
    cout<<"添加分支和叶节点"<<endl;
    
    Branch university("同济大学");
    Leaf college1("电信学院");
    Leaf college2("传媒学院");
    Leaf college3("汽车学院");
    
    university.add(&college1);
    university.add(&college2);
    university.add(&college3);

    
    Branch college4("软件学院");
    Leaf department1("学工办");
    Leaf department2("党支部");
    Leaf department3("教研室");
    
    college4.add(&department1);
    college4.add(&department2);
    college4.add(&department3);
    
    Branch college5("中德学院");
    Leaf department4("学工办");
    Leaf department5("党支部");
    
    college5.add(&department4);
    college5.add(&department5);
    
    university.add(&college4);
    
    university.add(&college5);
    
    string str("--->");
    university.display(str);
    
    cout<<endl;
    cout<<"删除叶节点"<<endl;
    college4.remove(&department3);
    
    university.display(str);
    
    
    cout<<endl;
    cout<<"删除分支"<<endl;
    university.remove(&college5);
    university.display(str);
    return 0;
}
