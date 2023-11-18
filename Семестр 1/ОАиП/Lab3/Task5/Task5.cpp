#include <iostream>
#include <cmath>

void task5() {
    long long testsCount, n;
    std::cin >> testsCount >> n;
    if (n > 40) {
        std::cout << "n is too big, try n <= 40\n";
        return;
    }
    for (int i = 0; i < testsCount; i++) {
        long double temp;
        std::cin >> temp;
        if (temp > 1 || temp < 0.09999) {
            std::cout << "Invalid input";
            return;
        }
		long double val1, val2 = 0;
		for (long long j = 1; j < n; j++) {
			val2 = val2 + (powl(2 * temp, j) / factorial(j));
		}
		val1 = expl(2 * temp);
		std::cout << val1 << " " << 1 + val2 << "\n";
    }  
}

int main() {
    task5();
    return 0;
}
