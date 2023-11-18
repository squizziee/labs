#include <iostream>
#include <cstring>

void printMatrix(int** matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d ", matrix[i][j]);
		}
		std::cout << "\n";
	}
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
	task13();
	return 0;
}