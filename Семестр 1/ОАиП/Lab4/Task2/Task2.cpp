#include <iostream>
#include <string>

template <size_t rows, size_t cols>
void printSMatrix(int (&matrix)[rows][cols]){
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			printf("%7d", matrix[i][j]);
		}
		std::cout << "\n";
	}
}

void task2() {
	const int n = 3,
			  m = 4;
	int arr[n][m]{ {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} };
	std::cout << "Input: \n";
	printSMatrix(arr);
	int minVal = INT32_MAX;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (j > i && arr[i][j] < minVal) {
				minVal = arr[i][j];
			}
		}
	}
	std::cout << "Output: ";
	std::cout << minVal << "\n";
}

int main() {
	task2();
	return 0;
}