#include <iostream>
#include <cmath>

void printArray(int arr[], int length) {
	for (int i = 0; i < length; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << "\n";
}

void task7() {
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

int main() {
	task7();
	return 0;
}