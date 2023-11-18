#include <iostream>
#include <algorithm>
#include "Vector.h"

void sort(Vector<int>& vect) {
	for (int i = 0; i < vect.size(); i++) {
		int minIndex = i;
		for (int j = i + 1; j < vect.size(); j++) {
			if (vect[j] < vect[minIndex]) {
				minIndex = j;
			}
		}
		int temp = vect[i];
		vect[i] = vect[minIndex];
		vect[minIndex] = temp;
	}
}

int main() {
	Vector<int> input({ 1, 5, 1, 4, 5, 6, 2, 1, 3, 4, 4, 4, 5, 7 });
	Vector<int> rotated;
	Vector<int> output;
	for (auto iter = input.rbegin(); iter != input.rend(); iter++) {
		rotated.push_back(*iter);
	}
	while (!rotated.empty()) {
		Vector<int> temp;
		for (int i = 0; i < 3; i++) {
			if (rotated.empty()) {
				break;
			}
			temp.push_back(rotated[rotated.size() - 1]);
			rotated.pop_back();
		}
		sort(temp);
		if (temp.size() == 2) {
			output.push_back((temp[0] + temp[1]) / 2);
		}
		else if (temp.size() == 1) {
			output.push_back(temp[0]);
		}
		else {
			output.push_back(temp[1]);
		}
	}
	for (int i : output) {
		std::cout << i << " ";
	}
	return 0;
}