#include "circle.h"

Circle::Circle()
{
	radius = 1;
	cout << "������ ����: " << radius << endl;
}
Circle::Circle(int r)
{
	radius = r;
	cout << "������ ����: " << radius << endl;
}

int Circle::getRadius()
{
	return radius;
}

Circle::~Circle()
{
	cout << "�Ҹ��� ����: " << radius << endl;
}
