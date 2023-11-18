#include <iostream>
using namespace std;

void task4()
{
	long double b1, q, n = 16;
	q = 1.0 / (n + 1.0);
	cin >> b1;
	cout << b1 / (1.0 - q);
}

int main() {
	task4();
	return 0;
}