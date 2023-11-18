#include <iostream>
#include <string>
#include "descriptions.h"

void credits() {
	printf("|   Done by Ivan Lyango, 253504, variant 8   |\n\n");
}

void run(void (*taskPtr)(void), void (*descPtr)(void)) {
	credits();
	descPtr();
	taskPtr();
	while (1) {
		std::cout << "Repeat? Enter 1 to continue, -1 to terminate";
		int flag;
		std::cin >> flag;
		if (flag == 1)
			taskPtr();
		else
			break;
		}
}

void printArray(int arr[], int length) {
	for (int i = 0; i < length; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << "\n";
}

void printMatrix(int** matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d ", matrix[i][j]);
		}
		std::cout << "\n";
	}
}

template <size_t rows, size_t cols>
void printSMatrix(int (&matrix)[rows][cols]){
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			printf("%7d", matrix[i][j]);
		}
		std::cout << "\n";
	}
}

template <size_t rows, size_t cols>
void readSMatrix(int(&matrix)[rows][cols]) {
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			std::cin >> matrix[i][j];
		}
	}
}

void readMatrix(int** matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cin >>  matrix[i][j];
		}
	}
}

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

void task1() {
	const int k = 7;
	int arr[k]{};
	for (int i = 0; i < k; i++) {
		std::cin >> arr[i];
	}
	std::cout << "Input: ";
	printArray(arr, k);
	sort(arr, k);
	int min = arr[0],
		max = arr[k - 1],
		leftOffset = 1,
		rightOffset = 1;
	for (int i = 1; i < k; i++) {
		if (arr[i] == min) leftOffset++;
	}
	for (int i = k - 2; i > 0; i--) {
		if (arr[i] == max) rightOffset++;
	}
	std::cout << "Output: ";
	int newLen = k - (leftOffset + rightOffset);
	if (newLen <= 0) {
		std::cout << "Empty array";
	}
	else {
		int* ans = new int[newLen];
		for (int i = leftOffset; i < k - rightOffset; i++) {
			ans[i - leftOffset] = arr[i];
		}
		printArray(ans, newLen);
		delete [] ans;
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
	delete[] arr;
	std::cout << count;
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

void task6() {
	long number, i;
	std::cin >> number >> i;
	long count = 0;
	if (i >= log10l(number)) {
		std::cout << "Invalid input";
		return;
	}
	while (number > 0) {
		if (count == i) {
			std::cout << number % 10 << "\n";
		}
		number /= 10;
		count++;
	}
}

bool contains(int* arr, int n, int toFind) {
	for (int i = 0; i < n; i++) {
		if (arr[i] == toFind) return true;
	}
	return false;
}

void task7_() {
	int n;
	std::cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		std::cin >> arr[i];
	}
	int minIndex = 0;
	int maxIndex = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] < arr[minIndex]) {
			minIndex = i;
		}
	}
	for (int i = 0; i < n; i++) {
		if (arr[i] > arr[maxIndex]) {
			maxIndex = i;
		}
	}
	int leftBorder = (minIndex < maxIndex) ? minIndex : maxIndex;
	int rightBorder = (minIndex < maxIndex) ? maxIndex : minIndex;
	for (int i = leftBorder + 1; i < rightBorder; i++) {
		arr[i] = 0;
	}
	//printf("leftBorder: %d rightBorder: %d\n", leftBorder, rightBorder);
	//printArray(arr, n);
	//return;
	int size = 0;
	int* toErase = (int*) malloc(size);
	for (int i = 0; i < n; i++) {
		if (arr[i] == 0) {
			size += 4;
			toErase = (int*) realloc(toErase, size);
			toErase[size / 4 - 1] = i;
		}
	}
	int size2 = 0;
	int* ans = (int*)malloc(size);
	for (int i = 0; i < n; i++) {
		if (!contains(toErase, n, i)) {
			size2 += 4;
			ans = (int*) realloc(ans, size2);
			ans[size2 / 4 - 1] = arr[i];
		}
	}
	printArray(ans, size2 / 4);
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
	//printMatrix(ans, n, n);
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

void task10() {
	int n;
	std::cin >> n;
	int* matrix = new int [n];
	for (int i = 1; i <= n; i++) {
		matrix[i - 1] = i - 1;
	}
	int count = 0;
	for (int i = 0; i < n; i++) {
		count += matrix[i];
	}
	std::cout << count + 1;
}

bool isInBounds(int i, int j, int rows, int cols) {
	if ((i >= 0) && (i < rows) && (j >= 0) && (j < cols))
		return true;
	return false;
}

char getMineNum(int count) {
	switch (count) {
	case 0: return '.';
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	}
	return 0;
}

void task11() {
	int n = 1, m;
	int size = sizeof(char*);
	char** arr = (char**)malloc(size);
	int rowPointer = 1;
	std::string firstLine;
	std::getline(std::cin, firstLine, '\n');
	int firstLineLength = firstLine.size();
	m = firstLineLength;
	char* temp = new char[firstLineLength + 1];
	strcpy_s(temp, sizeof temp, firstLine.c_str());
	arr[0] = (char*)malloc(m);
	for (int j = 0; j < m; j++) {
		arr[0][j] = temp[j];
	}
	do {
		std::string s;
		std::getline(std::cin, s, '\n');
		int lineLength = s.length();
		if (lineLength == 0) {
			break;
		}
		if (lineLength != firstLineLength) {
			std::cout << "Invalid input\n";
			return;
		}
		char* char_array = new char[lineLength + 1];
		strcpy_s(char_array, sizeof char_array, s.c_str());
		size += sizeof (char*);
		arr = (char**)realloc(arr, size);
		arr[rowPointer] = (char*)malloc(m);
		for (int j = 0; j < m; j++) {
			arr[rowPointer][j] = char_array[j];
		}
		rowPointer++;
		n++;
	} while (1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int count = 0;
			if (arr[i][j] == '.') {
				if (isInBounds(i - 1, j, n, m)) {
					if (arr[i - 1][j] == '*') {
						count++;
					}
				}
				if (isInBounds(i + 1, j, n, m)) {
					if (arr[i + 1][j] == '*') {
						count++;
					}
				}
				if (isInBounds(i - 1, j + 1, n, m)) {
					if (arr[i - 1][j + 1] == '*') {
						count++;
					}
				}
				if (isInBounds(i + 1, j + 1, n, m)) {
					if (arr[i + 1][j + 1] == '*') {
						count++;
					}
				}
				if (isInBounds(i - 1, j - 1, n, m)) {
					if (arr[i - 1][j - 1] == '*') {
						count++;
					}
				}
				if (isInBounds(i, j + 1, n, m)) {
					if (arr[i][j + 1] == '*') {
						count++;
					}
				}
				if (isInBounds(i, j - 1, n, m)) {
					if (arr[i][j - 1] == '*') {
						count++;
					}
				}
				if (isInBounds(i + 1, j - 1, n, m)) {
					if (arr[i + 1][j - 1] == '*') {
						count++;
					}
				}
				arr[i][j] = getMineNum(count);
			}
			else if (arr[i][j] == '*') {
				continue;
			}
			else {
				std::cout << "Invalid input";
				exit(69);
			}
		}
	}
	std::cout << "Output : \n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%7c", arr[i][j]);
		}
		std::cout << "\n";
	}
	for (int i = 0; i < n; i++) {
		free(arr[i]);
	}
	free(arr);
}

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
	//printMatrix(matrix, n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] == el) {
				std::cout << i << " " << j;
				break;
			}
		}
	}
	std::cout << "\n";
	printMatrix(matrix, n, n);
	//std::cout << "Invalid input";
}

void calcOdd(int** matrix, int n) {
	int nsqr = n * n;
	int i = 0, j = n / 2;
	for (int k = 1; k <= nsqr; k++) {
		matrix[i][j] = k;
		i--;
		j++;
		if (k % n == 0) {
			i += 2;
			--j;
		}
		else {
			if (j == n) j -= n;
			else if (i < 0) i += n;
		}
	}
}

void calcDoubleEven(int** matrix, int n) {
	int** I = new int* [n];
	int** J = new int* [n];
	for (int i = 0; i < n; i++) {
		I[i] = new int[n];
		J[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			I[i][j] = 0;
			J[i][j] = 0;
		}
	}

	int i, j;
	int index = 1;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			I[i][j] = ((i + 1) % 4) / 2;
			J[j][i] = ((i + 1) % 4) / 2;
			matrix[i][j] = index;
			index++;
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (I[i][j] == J[i][j])
				matrix[i][j] = n * n + 1 - matrix[i][j];
		}
	}
}

void solveSquare(int** matrix, int n);
void calcSingleEven(int** matrix, int n)
{
	int p = n / 2;

	int** M = new int* [n];
	for (int i = 0; i < n; i++) {
		M[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			M[i][j] = 0;
		}
	}
	solveSquare(M, p);
	int i, j, k;
	for (i = 0; i < p; i++) {
		for (j = 0; j < p; j++) {
			matrix[i][j] = M[i][j];
			matrix[i + p][j] = M[i][j] + 3 * p * p;
			matrix[i][j + p] = M[i][j] + 2 * p * p;
			matrix[i + p][j + p] = M[i][j] + p * p;
		}
	}
	if (n == 2)
		return;
	int* I = new int[p];
	for (i = 0; i < p; i++) {
		I[i] = i + 1;
	}
	k = (n - 2) / 4;
	int segment = 4; // bytes
	int size = 4;
	int* J = (int*) malloc(size);
	for (i = 1; i <= k; i++) {
		J[(size / segment) - 1] = i;
		size += segment;
		J = (int*) realloc(J, size);
	}
	for (i = n - k + 2; i <= n; i++) {
		J[(size / segment) - 1] = i;
		size += segment;
		J = (int*) realloc(J, size);
	}
	int temp;
	for (i = 1; i <= p; i++)
		for (j = 1; j <= size / segment - 1; j++)
		{
			temp = matrix[i - 1][J[j - 1] - 1];
			matrix[i - 1][J[j - 1] - 1] = matrix[i + p - 1][J[j - 1] - 1];
			matrix[i + p - 1][J[j - 1] - 1] = temp;
		}
	i = k;
	j = 0;
	temp = matrix[i][j]; matrix[i][j] = matrix[i + p][j]; matrix[i + p][j] = temp;
	j = i;
	temp = matrix[i + p][j]; matrix[i + p][j] = matrix[i][j]; matrix[i][j] = temp;
}

void solveSquare(int** matrix, int n) {
	if (n % 2 == 1)
		calcOdd(matrix, n);
	else {
		if (n % 4 == 0) {
			calcDoubleEven(matrix, n);
		}
		else {
			calcSingleEven(matrix, n);
		}
	}
}

void task13() {
	int n;
	std::cin >> n;
	if (n <= 2) {
		std::cout << "Invalid input\n";
		return;
	}
	int** matrix = new int* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 0;
		}
	}
	solveSquare(matrix, n);
	printMatrix(matrix, n, n);
}

int main() {
	//task13();
	run(&task13, &descriptions::task13);
	return 0;
}