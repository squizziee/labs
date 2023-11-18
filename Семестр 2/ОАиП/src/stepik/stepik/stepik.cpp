#include <iostream>
#include <string>
#include <set>
#include <algorithm>

void findIndexes() {
    std::string str;
    int i;
    std::cin >> str >> i;
    std::set<char> uniqueChars;
    for (int j = 0; j < str.size(); j++) {
        uniqueChars.insert(str[j]);
    }
    std::cout << uniqueChars.size() << "\n";
    char digit = str[i - 1];
    std::reverse(str.begin(), str.end());
    for (int j = 0; j < str.size(); j++) {
        if (str[j] == digit) {
            std::cout << j << " ";
        }
    }
}

void initMatrix(int** matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[m];
	}
}

void printMatrix(int** matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void fillMatrix1(int** matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i <= 5) {
				matrix[i][j] = 3 * i * j - 3;
			}
			else {
				matrix[i][j] = 2 * i * j - 2;
			}
		}
	}
}

void fillMatrix2(int** matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i <= 7) {
				matrix[i][j] = 5 * i * j - 4;
			}
			else {
				matrix[i][j] = 4 * i * j - 5;
			}
		}
	}
}

int sumOfBorderElements(int** matrix, int n, int m) {
	int sum = 0;
	for (int i = 0; i < m - 1; i++) {
		sum += matrix[0][i];
	}
	for (int i = 0; i < n - 1; i++) {
		sum += matrix[i][n - 1];
	}
	for (int i = n - 1; i > 0; i--) {
		sum += matrix[n - 1][i];
	}
	for (int i = n - 2; i >= 0; i--) {
		sum += matrix[i][0];
	}
	return sum;
}

void deployTask1() {
	int n;
	std::cin >> n;
	int** matrix1 = new int* [n];
	int** matrix2 = new int* [n];
	initMatrix(matrix1, n, n);
	initMatrix(matrix2, n, n);
	fillMatrix1(matrix1, n, n);
	fillMatrix2(matrix2, n, n);
	std::cout << sumOfBorderElements(matrix1, n, n) << "\n";
	printMatrix(matrix1, n, n);
	std::cout << sumOfBorderElements(matrix2, n, n) << "\n";
	printMatrix(matrix2, n, n);
}

int main() {
	deployTask1();
}