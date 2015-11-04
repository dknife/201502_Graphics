#include "circle.h"

Circle::Circle()
{
	radius = 1;
	cout << "积己磊 荐青: " << radius << endl;
}
Circle::Circle(int r)
{
	radius = r;
	cout << "积己磊 荐青: " << radius << endl;
}

int Circle::getRadius()
{
	return radius;
}

Circle::~Circle()
{
	cout << "家戈磊 荐青: " << radius << endl;
}
