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

int vectorMult(int vector1[], int vector2[], int length) {
	int ans = 0;
	for (int i = 0; i < length; i++) {
		ans += vector1[i] * vector2[i];
	}
	return ans;
}

void task4() {
	int n, m;
	std::cin >> n >> m;
	int** arr = new int* [n];
	for (int i = 0; i < n; i++) {
		arr[i] = new int[m];
	}
	readMatrix(arr, n, m);
	std::cout << "Input : \n";
	printMatrix(arr, n, m);
	int count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i == 0 && j == 0) {
				if (arr[i][j] < arr[i][j + 1] &&
					arr[i][j] < arr[i + 1][j]) {
					count++;
				}
			}
			else if (i == 0 && j == m - 1) {
				if (arr[i][j] < arr[i][j - 1] &&
					arr[i][j] < arr[i + 1][j]) {
					count++;
				}
			} 
			else if (i == n - 1 && j == m - 1) {
				if (arr[i][j] < arr[i][j - 1] &&
					arr[i][j] < arr[i - 1][j]) {
					count++;
				}
			}
			else if (i == n - 1 && j == 0) {
				if (arr[i][j] < arr[i][j + 1] &&
					arr[i][j] < arr[i - 1][j]) {
					count++;
				}
			}
			else if (i == 0) {
				if (arr[i][j] < arr[i][j + 1] &&
					arr[i][j] < arr[i + 1][j] &&
					arr[i][j] < arr[i][j - 1]) {
					count++;
				}
			}
			else if (j == 0) {
				if (arr[i][j] < arr[i][j + 1] &&
					arr[i][j] < arr[i + 1][j] &&
					arr[i][j] < arr[i][j + 1] &&
					arr[i][j] < arr[i - 1][j]) {
					count++;
				}
			}
			else if (j == m - 1) {
				if (arr[i][j] < arr[i + 1][j] &&
					arr[i][j] < arr[i - 1][j] &&
					arr[i][j] < arr[i][j - 1]) {
					count++;
				}
			}
			else if (i == n - 1) {
				if (arr[i][j] < arr[i - 1][j] &&
					arr[i][j] < arr[i][j - 1] &&
					arr[i][j] < arr[i][j + 1]) {
					count++;
				}
			}
			else {
				if (arr[i][j] < arr[i][j + 1] &&
					arr[i][j] < arr[i + 1][j] &&
					arr[i][j] < arr[i][j - 1] &&
					arr[i][j] < arr[i - 1][j]) {
					count++;
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		delete arr[i];
	}
	delete[] arr;
	std::cout << count;
}

int main() {
	task4();
	return 0;
}