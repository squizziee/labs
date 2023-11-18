#include <iostream>
#include <iomanip>
using namespace std;

void task1()
{
	long double x;
	cin >> x;
	long double square = x * x;
	long double part1 = x * (23 * square + 32);
	long double part2 = 69 * square + 8;
	cout << part1 + part2;
	cout << part2 - part1;
}

int main() {
	task1();
    return 0;
}