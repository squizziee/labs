#include <iostream>
#include <cstring>

int vectorMult(int vector1[], int vector2[], int length) {
	int ans = 0;
	for (int i = 0; i < length; i++) {
		ans += vector1[i] * vector2[i];
	}
	return ans;
}

void task3() {
	int n;
	std::cin >> n;
	int** arr = new int*[n];
	for (int i = 0; i < n; i++) {
		arr[i] = new int[n];
	}
	readMatrix(arr, n, n);
	std::cout << "Input: \n";
	printMatrix(arr, n, n);
	std::cout << "Output: ";
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (vectorMult(arr[i], arr[j], n) != 0 ||
				vectorMult(arr[i], arr[i], n) != 1) {
				std::cout << "not orthogonal\n";
				return;
			}
		}
	}
	delete[] arr;
	std::cout << "orthogonal\n";
}

int main() {
	task3();
	return 0;
}