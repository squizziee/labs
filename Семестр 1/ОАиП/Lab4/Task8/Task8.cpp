#include <iostream>
#include <cmath>

void readMatrix(int** matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cin >>  matrix[i][j];
		}
	}
}

void task8() {
	int n, m;
	std::cin >> n;
	int **matrix1 = new int* [n];
	for (int i = 0; i < n; i++) {
		matrix1[i] = new int[n];
	}
	readMatrix(matrix1, n, n);
	std::cin >> m;
	int **matrix2 = new int* [m];
	for (int i = 0; i < m; i++) {
		matrix2[i] = new int[n];
	}
	readMatrix(matrix2, m, m);
	int **ans = new int* [n];
	for (int i = 0; i < n; i++) {
		ans[i] = new int[n]();
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < m; k++) {
				ans[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}
	for (int j = 0; j < n; j++) {
		int k;
		for (k = 0; k < m; k++) {
			std::cout << ans[j][k];
		}
		if (k < m - 1) 
			std::cout << " ";
		std::cout << "\n";
	}
}

int main() {
	task8();
	return 0;
}