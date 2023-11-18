#include <iostream>
#include "algolib.h"
using namespace std;
using namespace algolib;

int main() {
	int arr[] = {1, 2, 908, -49, 39, 758, 7190};
	SortMachine::shellSort(arr);
	for (auto e : arr)
		cout << e << " ";
	return 0;
}