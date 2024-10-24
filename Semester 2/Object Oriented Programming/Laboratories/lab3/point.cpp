#include "Point.h"
#include <iomanip>

// definition of the static variable (we initialize it to 0)
// we don't use the static keyword anymore, but we use the scope resolution operator
unsigned long long Point::CREATED_INSTANCES_PARAM{ 0 };
Point::Point() : m_x{ 0.0f }, m_y{0.0f} // uniform initialization
{}

Point::Point(float x, float y) {
    m_x = x; m_y = y;
    CREATED_INSTANCES_PARAM++; // another instance was created
}

float Point::x() const {
    return this->m_x;
}

void Point::setX(float x) {
    m_x = x;
}

void Point::setY(float y) {
    m_y = y;
}

// notice that operator+ belongs to the Point class Point::operator+
// :: -> scope resolution operator
Point Point::operator+(const Point& other) const {
    return Point(m_x+other.m_x, m_y+other.m_y);
}

unsigned long long Point::numCreatedParametrized() {
    // we don't have access to this pointer
    return CREATED_INSTANCES_PARAM;
}

// notice that operator- is not a member of the class
// we don't use the friend keyword when defining the function
Point operator-(const Point& p1, const Point& p2) {
return Point(p1.m_x - p2.m_x, p1.m_y - p2.m_y);
}

// not a member of the class
// we don't use the friend keyword when defining the function
std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "(" <<std::setprecision(2)<<std::fixed << point.m_x << ", " <<
       point.m_y << ")";
    return os;
}

// not a member of the class
// we don't use the friend keyword when defining the function
std::istream& operator>>(std::istream& is, Point& point) {
    is >> point.m_x>> point.m_y;
    return is;
}