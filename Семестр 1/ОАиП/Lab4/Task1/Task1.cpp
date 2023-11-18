#include <iostream>

void printArray(int arr[], int length) {
	for (int i = 0; i < length; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << "\n";
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

int main() {
	task1();
	return 0;
}