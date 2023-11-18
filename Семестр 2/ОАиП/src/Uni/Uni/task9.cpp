#include <iostream>
using namespace std;

void task9()
{
	int a, b;
	cin >> a >> b;
	printf("a : %d | b : %d\n", a, b);
	a = a ^ b;
	printf("a : %d | b : %d\n", a, b);
	b = b ^ a;
	printf("a : %d | b : %d\n", a, b);
	a = a ^ b;
	printf("a : %d | b : %d\n", a, b);
}

int main() {
	task9();
	return 0;
}