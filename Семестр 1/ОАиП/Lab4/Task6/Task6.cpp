#include <iostream>
#include <cmath>

void task6() {
	long number, i;
	std::cin >> number >> i;
	long count = 0;
	if (i >= log10l(number)) {
		std::cout << "Invalid input";
		return;
	}
	while (number > 0) {
		if (count == i) {
			std::cout << number % 10 << "\n";
		}
		number /= 10;
		count++;
	}
}

int main() {
	task6();
	return 0;
}