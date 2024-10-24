#pragma once
#include <ostream>
#include <istream>
using namespace std;
class Vector2D
{
	
public:
	Vector2D(); // constructor
	Vector2D(double px, double py);
	~Vector2D();// destructor

	double getX() const;
	double getY();

	void setX(double x);

	Vector2D operator+(const Vector2D& other);
	friend Vector2D operator-(const Vector2D& v1, const Vector2D& v2);

	friend ostream& operator<<(ostream& os, const Vector2D& v);
	
	static int getNumInstances();
private:
	double x;
	double y;
	static int NUM_INSTANCES;
	
};

