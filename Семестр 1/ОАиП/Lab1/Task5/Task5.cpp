#include <iostream>
using namespace std;

double calc(long double a1, long double d, int index);

void task5()
{
	long long a1, a100;
	long double d;
	cin >> a1 >> a100;
	d = (a100 - a1) / 99.0;
	cout << d << " " << 70.0 / 2.0 * (a1 + calc(a1, d, 70));
}

double calc(long double a1, long double d, int index) {
	return a1 + (index - 1) * d;
}

int main() {
	task5();
	return 0;
}
