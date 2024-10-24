#include <iostream>
#include <vector>
using namespace std;

class Animal{
public:
    virtual void speak(){ cout<<"???"<<endl;} // the function is marked as virtual
};

class Cat: public Animal{
public:
    void speak() override{ cout<<"Meow!"<<endl;} // good practice: use the override specifier
};

class Dog: public Animal{
public:
    void speak() override{ cout<<"Woof!"<<endl;}
};

int main(){
    Dog d{};
    Cat *c{new Cat{}};
    Animal* aCat{c};
    Animal& aDog{d};
    aCat->speak();
    aDog.speak();
    delete c;
    return 0;
}