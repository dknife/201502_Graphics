#include "circle.h"

void increase(Circle &c);
void readRadius(Circle &c);

int main()
{

	Circle waffer(30);
	readRadius(waffer);
	increase( waffer);
	cout << "반지름:" << waffer.getRadius() << endl;
	return 0;
}

void readRadius(Circle &c)
{
	int r;

	cout << "반지름: ";
	cin >> r;
	c.setRadius(r);
}

void increase(Circle &c)
{
	int r;
	r = c.getRadius();
	c.setRadius(r+1);
}