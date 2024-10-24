// DemoPoly.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>


class Animal {
protected:
    std::string name;
private :
    int id;

public:
 
    Animal(int _id) : id{ _id } {
        name = "";
    }
    virtual ~Animal() = default;

    virtual void speak() = 0;// { std::cout << " ???"; }
};

class Dog : public Animal{
    
protected:
    std::string breed;

public:
    Dog(int _id, std::string _name, std::string _breed): Animal{ _id }{
      
        breed = _breed;
        name = _name;
    }

    void speak() { std::cout << " Woof"; }
};

class Cat : public Animal {

protected:
    int furLength;
public:
    Cat(int _id, std::string _name, int fl) :Animal{ _id }, furLength{ fl } {
        name = _name;
    }
    void speak() { std::cout << " Meow!"; }
};

//Animal doSpeak(Animal &a) {
//    a.speak();
//    return a;
//}
int main()
{

    //Animal a{1};
    // std::cout << std::endl << "animal speak "; a.speak(); // class Animal is now abstract, cannot be instantiated
    Dog d{2, "dog", "chow chow"};
    Cat c{2, "cat", 20};

    
    std::cout << std::endl<< "dog speak "; d.speak();
    std::cout << std::endl<< "cat speak "; c.speak();

    //Animal an{ d };

    // POLYMORPHISM IN C++, 2 SIMPLE RULES
    // (1) - to use pointer or references to the base class
    // (2) - use virutal functions
    Animal& aRef = d ; // reference
    Animal* aPointer = &d ; // pointer
    Animal* aPointerCat = &c ; // pointer

    // downcasting
    // pointers 
   Dog* dc = dynamic_cast<Dog*>(aPointer); //
   if (!dc) {
       std::cout << "not a dog"<<std::endl;
   }
   else {
       std::cout << "a dog"<<std::endl;
   }
   Dog* df = dynamic_cast<Dog*>(aPointer); //

   Dog* cc = dynamic_cast<Dog*>(aPointerCat); //
   if (!cc) {
       std::cout << "not a dog";
   }
   else {
       std::cout << "a dog";
   }
   Dog* d1 = (Dog*)(aPointer);


    std::cout << std::endl<< "aRef speak " ; aRef.speak();
    std::cout << std::endl<<"aPointer speak " ; aPointer->speak();

   // Animal* animals[10];

    // OBJECT SLICING
    //Animal an = d; // object slicing
    //std::cout << std::endl << "an speak " << std::endl;  an.speak();
    //doSpeak(aRef);

    // auto keyword


    auto f{ 3.5f }; // type deducted to float
    auto ch = 'a' ; // deducted type char
    std::vector<Animal*> animals;
    //std::vector<Animal*>::iterator animalIt;
    auto animalIt = animals.begin(); // begin returns an interator to the vector, deducted type std::vector<Animal*>::iterator
    
    return 0;
}

