#include <iostream>
#include "task2.h"
using namespace std;

void task2::deploy()
{
	long double x, y, z;
	cin >> x >> y >> z;
	if (x + y > z &&
		x + z > y &&
		y + z > x)
		cout << "YES";
	else
		cout << "NO";
}
