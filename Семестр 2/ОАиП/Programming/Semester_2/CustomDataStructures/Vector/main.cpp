#include <iostream>
#include "Vector.h"

int main() {
	Vector<int> vector;
	vector.reserve(5);
	vector.push_back({ 1, 2, 6, 7, 11 });
	for (auto i = vector.begin(); i != vector.end(); i++) {
		if (*i == 6) {
			vector.push_back(89);
		}
	}
	for (auto& i : vector) {
		std::cout << i << "\n";
	}
	return 0;
}