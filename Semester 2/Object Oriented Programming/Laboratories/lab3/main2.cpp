#include "point.h"
#include <iostream>
using namespace std;

int main(void) {
    Point p1{}; // default constructor
    // use cin to read the coordinates of a point
    cout << "Please enter the coordinates of the point separated by space:" << endl;
    // stream extraction operator
    cin >> p1;
    // stream insertion operator
    cout << "You entered: " << p1 << endl;
    Point p2{ 10, 20 }; // parametrized constructor
    // add the two points
    Point p3{ p1 + p2 };
    // or, because the addition operator is a member of the class, we can do
    Point p4{ p1.operator+(p2) };
    cout << p1 << "+" << p2 << "=" << p3 << endl;
    cout << p1 << "+" << p2 << "=" << p4 << endl;

    cout << p1<<"-"<<p2<<"="<<p1 - p2<<endl;
    // calling a static method
    cout << "There were " << Point::numCreatedParametrized() << " objects created using the parametrized constructor" << endl;
    cout << "The end" << endl;
    return 0;
}