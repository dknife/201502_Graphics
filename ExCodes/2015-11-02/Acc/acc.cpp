#include "acc.h"
int main()
{
	Accumulator acc(20);

	acc.add(10).add(20);
	cout << "����� : " << acc.get() << endl;

	return 0;
}
