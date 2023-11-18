#include <iostream>

void task10() {
	int n;
	std::cin >> n;
	int* matrix = new int [n];
	for (int i = 1; i <= n; i++) {
		matrix[i - 1] = i - 1;
	}
	int count = 0;
	for (int i = 0; i < n; i++) {
		count += matrix[i];
	}
	std::cout << count + 1;
}

int main() {
	task10();
	return 0;
}