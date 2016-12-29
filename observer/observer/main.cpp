#include <iostream>
#include <vector>

using namespace std;

class Observer // Observer类
{
public:
    
    virtual void update(string name, float height, float weight) = 0;
    virtual void display() = 0;
};

class Subject
{
public:
    
    virtual void registerObserver(Observer* pObserver) = 0;
    
    virtual void removeObserver(Observer* pObserver) = 0;
    
    virtual void notifyObservers() = 0;
};

class Figure:public Subject
{
public:
    
    void setParameters(string name, float height, float weight) // 设置身高体重
    {
        this->n	= name;
        this->h	= height;
        this->w	= weight;
        notifyObservers();
    }
    
    void registerObserver(Observer* ob)
    {
        vObserver.push_back(ob);
    }
    
    void removeObserver(Observer* ob)
    {
        vObserver.erase(remove(vObserver.begin(), vObserver.end(), ob), vObserver.end());
    }
    
    void notifyObservers()
    {
        vector<Observer*>::iterator iter;
        for(iter = vObserver.begin(); iter != vObserver.end(); ++iter)
        {
            (*iter)->update(n, h, w);
        }
    }
    
private:
    
    vector<Observer*> vObserver;
    
    string n;
    float h, w;
    
};

class Person:public Observer
{
public:
    
    Person(Figure* fig) //构造函数
    {
        fig->registerObserver(this);
    }
    
    void update(string name, float height, float weight) //重写Update函数
    {
        this->n	= name;
        this->h	= height;
        this->w	= weight;
        display();
    }
    
    void display() //重写Display函数
    {
        cout << n <<"'s height is: " << h <<"cm." << endl;
        cout << n <<"'s weight is: " << w <<"kg." << endl;
    }
    
private:
    
    string n;
    float h, w;
    
};

int main()
{
    Figure* fig = new Figure;
    fig->setParameters("Alice", 168.0f, 55.5f);
    Person *p1 = new Person(fig);
    
    p1->display();
    cout << endl;
    fig->setParameters("Alice", 168.0f, 55.5f);
    
    cout << endl << endl;
    //system("pause");
    return 0;
}
