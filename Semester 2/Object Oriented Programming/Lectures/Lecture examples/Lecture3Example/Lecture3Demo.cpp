// Lecture3Demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Vector2D.h"
#include <iostream>


void modify(const char& c) {
    //c = 'e';
}
int main()
{
    std::cout << "Hello World!\n";
    {
        Vector2D v;
        Vector2D v1{};
        Vector2D v2();

        v.setX(10);
        std::cout << v.getX();

        Vector2D add = v + v1;
        add = v.operator+(v1);

        Vector2D diff = v1 - v;
        //v.operator-(v1);
        std::cout << "diff result " << diff.getX() << " " << diff.getY() << std::endl;
        std::cout<<Vector2D::getNumInstances()<<" "<<v1.getNumInstances();
        
        std::cout << v;
        //char c = 'c';
        //char& rc = c; // reference to c
        //char d='x';
        //rc = d;
        //std::cout << (int*)&c << " " << (int*) & rc;
        //rc = 'd';
        //std::cout <<std::endl<< c << " " << rc;
        //modify(c);
        //std::cout << std::endl << c << " " << rc;
    }
    return 0;
}
