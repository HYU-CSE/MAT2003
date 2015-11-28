
#include <iostream>
#include "measure.h"

using namespace  std;
int fibonachi(int i)
{
	if( i <2)
		return 1;
	else
		return fibonachi(i-1) + fibonachi(i-2);
}

int main()
{
	cout << CLOCKS_PER_SEC << endl;
	TIME_TEST(test, 10)
	{
		fibonachi(33);
	}
	cout << test.total << endl;
	cout << test.average << endl;
}