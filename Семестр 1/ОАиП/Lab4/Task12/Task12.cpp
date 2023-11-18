#include <iostream>
#include <cstring>

void goLeft(int** matrix, int i, int j, int n, int& num);
void goDown(int** matrix, int i, int j, int n, int &num) {
	for (int k = 0; k < n; k++) {
		if (matrix[k][j - 1] < 0) {
			goLeft(matrix, k, j, n, num);
			return;
		}
		else {
			matrix[k][j] = num++;
		}
	}
}

void goLeft(int** matrix, int i, int j, int n, int &num) {
	for (int k = j; k >= 0; k--) {
		matrix[i][k] = num++;
	}
}

void fill(int** matrix, int n, int &num) {
	int i = 0, j = 1;
	for (; j < n; j++) {
		goDown(matrix, i, j, n, num);
	}
}

void task12() {
	int el;
	int n = 10;
	std::cin >> el;
	int** matrix = new int* [n];
	for (int j = 0; j < n; j++) {
		matrix[j] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = -1;
		}
	}
	matrix[0][0] = 1;
	int count = 2;
	fill(matrix, n, count);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] == el) {
				std::cout << i << " " << j;
				break;
			}
		}
	}
	std::cout << "\n";
}

int main() {
	task12();
	return 0;
}