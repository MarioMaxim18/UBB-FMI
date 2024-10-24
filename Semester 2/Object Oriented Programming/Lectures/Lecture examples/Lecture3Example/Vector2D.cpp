#include "Vector2D.h"
#include<iostream>
int Vector2D::NUM_INSTANCES = 0;

Vector2D::Vector2D() {
	this->x = 0;
	(*this).y = 0;
	NUM_INSTANCES++;
}

Vector2D::Vector2D(double px, double py) :x{ px }, y{ py } {
	NUM_INSTANCES++;
}

Vector2D::~Vector2D() {
	//std::cout << "destructor";
}

double Vector2D::getX() const {
	// x = 20; constant this pointer. cannot moidy the state
	return x;
}
double Vector2D::getY() {
	//y = 10;
	return y;
}

void Vector2D::setX(double x) {
	this->x = x;
}

Vector2D Vector2D::operator+(const Vector2D& other) {
	return Vector2D{x + other.x, y + other.y};
}

Vector2D operator-(const Vector2D& v1, const Vector2D& v2) {
	return Vector2D{ v1.x - v2.x, v1.y - v2.y };
}

ostream& operator<<(ostream& os, const Vector2D& v) {
	os << "(" << v.x << ", " << v.y << ")" << std::endl;
	return os;
}

 int Vector2D::getNumInstances() {
	return NUM_INSTANCES;
}