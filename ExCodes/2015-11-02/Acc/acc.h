#ifndef ACC_H
#define ACC_H
#include <iostream>
using namespace std;

class Accumulator
{
	int value;
public:
	Accumulator(int v) { value = v; };
	Accumulator& add(int n) { value += n; return *this; };
	int get() { return value; };
};


#endif;