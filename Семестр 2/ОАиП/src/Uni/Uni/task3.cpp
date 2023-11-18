#include <iostream>
#include "task3.h"
using namespace std;

void task3()
{
	long double t, v0, a;
	cin >> t >> v0 >> a;
	cout << v0 * t + a * t * t / 2.0;
}

int main() {
	task3();
	return 0;
}