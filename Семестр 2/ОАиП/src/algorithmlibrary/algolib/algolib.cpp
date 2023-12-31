#include "algolib.h"
using namespace algolib;

int SortMachine::shellSort(int arr[]) {
	int n = sizeof(arr) / sizeof(arr[0]);
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++) {
			int temp = arr[i];
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
				arr[j] = arr[j - gap];
			}
			arr[j] = temp;
		}
	}
	return 0;
}