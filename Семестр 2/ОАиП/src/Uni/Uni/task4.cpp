#include <iostream>
#include "task4.h"
using namespace std;

void task4::deploy()
{
	long double b1, q, n = 16;
	q = 1.0 / (n + 1.0);
	cin >> b1;
	cout << b1 / (1.0 - q);
}
