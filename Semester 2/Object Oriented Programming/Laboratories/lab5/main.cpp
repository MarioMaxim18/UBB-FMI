#include <iostream>
using namespace std;

class Shape {
protected:
    // coordinates of the center of the shape
    // protected - can be accessed by the derived classes
    double m_x;
    double m_y;
public:
    Shape(double x, double y) {
        m_x = x;
        m_y = y;
    }
    // this method is inherited by the derived class
    void translate(double dx, double dy) {
        m_x += dx;
        m_y += dy;
    }
    void displayInfo(){
        cout<<"Centroid: ("<<m_x<<", "<<m_y<<")"<<endl;
    }
};

class Circle : public Shape {
private:
    double m_radius;
public:
    // we call the base class constructor Shape{x, y}
    // this will initialize the inherited m_x and m_y attributes
    Circle(double x, double y, double r) : Shape{x, y} {
        m_radius = r;
    }
    // redefine the displayInfo method
    void displayInfo(){
        cout<<"Circle:"<<endl<<"\t";
        Shape::displayInfo(); // call the displayInfo method from the parent class
        cout<<"\tRadius: "<<m_radius<<endl;
        cout<<endl;
    }
};

class Rectangle : public Shape {
private:
    double m_width;
    double m_height;
public:
    Rectangle(double x, double y, double w, double h) : Shape{x, y} {
      m_width = w; m_height = h;
    }
    // redefine the displayInfo method
    void displayInfo(){
        cout<<"Rectangle:"<<endl<<"\t";
        Shape::displayInfo(); // call the displayInfo method from the parent class
        cout<<"\tSize: ("<<m_width<<", "<<m_height<<")"<<endl;
        cout<<endl;
    }
};

int main(){
    Circle c{10, 20, 4};
    Rectangle r{0, 0, 20, 30};
    c.displayInfo();
    r.displayInfo();
    cout<<"Translate circle with (20, -4)"<<endl;
    c.translate(20, -4);
    c.displayInfo();
    return 0;
}