#include "acc.h"
int main()
{
	Accumulator acc(20);

	acc.add(10).add(20);
	cout << "°á°ú´Â : " << acc.get() << endl;

	return 0;
}
