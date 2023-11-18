#include <iostream>
using namespace std;

#define g 9.81

void task2()
{
	int h;
	cin >> h;
	cout << sqrt(2.0 * h / g);
}

int main() {
	task2();
}