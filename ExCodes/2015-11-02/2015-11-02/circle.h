#ifndef CIRCLE_H
#define CIRCLE_H
#include <iostream>
using namespace std;

class Circle
{
	int radius;
public:
	Circle();
	Circle(int r);
	~Circle(); //�Ҹ���
	int getRadius();
	void setRadius(int r) { radius = r; };
};


#endif;