#include <iostream>

void printMatrix(int** matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d ", matrix[i][j]);
		}
		std::cout << "\n";
	}
}

void readMatrix(int** matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cin >>  matrix[i][j];
		}
	}
}

void task5() {
	int n, m;
	std::cin >> n >> m;
	int** matrix = new int* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[m];
	}
	readMatrix(matrix, n, m);
	int maxVal = INT32_MIN; 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = i; k >= 0; k--) {
				for (int t = j; t >= 0; t--) {
					if (matrix[k][t] > matrix[i][j]) {
						matrix[i][j] = matrix[k][t];
					}
				}
			}
		}
	}
	printMatrix(matrix, n, m);
}

int main() {
	task5();
	return 0;
}