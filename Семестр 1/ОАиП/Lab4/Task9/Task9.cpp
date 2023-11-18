#include <iostream>
#include <cmath>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void sort(int arr[], int length) {
	for (int i = 0; i < length - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < length; j++) {
			if (arr[j] < arr[minIndex]) {
				minIndex = j;
			}
		}
		if (i != minIndex) {
			swap(&arr[i], &arr[minIndex]);
		}
	}
}

void task9() {
	int n;
	std::cin >> n;
	if (n <= 1) {
		std::cout << "Invalid input\n";
		return;
	}
	int*** cube = (int***) malloc(4 * static_cast<size_t>(n));
	for (int i = 0; i < n; i++) {
		cube[i] = (int**) malloc(4 * static_cast<size_t>(n));
		for (int j = 0; j < n; j++) {
			cube[i][j] = (int*) malloc(4 * static_cast<size_t>(n));
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				int temp;
				std::cin >> temp;
				if (temp < 0) {
					std::cout << "Invalid input\n";
					return;
				}
				cube[i][j][k] = temp;
			}
		}
	}
	int sums[4] = {};
	for (int i = 0; i < n; i++) {
		sums[0] += cube[i][i][i];
	}
	for (int i = 0; i < n; i++) {
		sums[1] += cube[i][n - i - 1][n - i - 1];
	}
	for (int i = 0; i < n; i++) {
		sums[2] += cube[i][n - i - 1][i];
	}
	for (int i = 0; i < n; i++) {
		sums[3] += cube[i][i][n - i - 1];
	}
	sort(sums, 4);
	std::cout << sums[3];
}

int main() {
	task9();
	return 0;
}