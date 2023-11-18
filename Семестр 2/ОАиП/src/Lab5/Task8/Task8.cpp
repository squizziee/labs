#include <iostream>
#include <vector>

long long calcDivisor(long long n) {
	if (n == 0) {
		return 0;
	}
	long long k = (n + 1) / 2;
	return k * k + calcDivisor(n / 2);
}

int main() {
	int k;
	long long n;
	std::cin >> k;
	std::vector<long long> output;
	for (int i = 0; i < k; i++) {
		std::cin >> n;
		output.push_back(calcDivisor(n));
	}
	for (int i = 0; i < k; i++) {
		std::cout << output[i] << "\n";
	}
}