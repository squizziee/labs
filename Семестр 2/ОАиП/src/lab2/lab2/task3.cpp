#include <iostream>
#include <vector>
#include "task3.h"
using namespace std;

vector<long double> sort(vector<long double> arr, int size);

void task3::deploy()
{
	long long X, Y;
	long double A, B, C, K;
	cin >> X >> Y >> A >> B >> C >> K;
	if (X < Y) {
		X = 0;
	}
	else if (X > Y) {
		Y = 0;
	}
	else {
		X = 0;
		Y = 0;
	}
	vector<long double> vect = {A, B, C};
	vect = sort(vect, 3);
	for (auto e : vect) {
		cout << e << "\n";
	}
}

vector<long double> sort(vector<long double> arr, int size) {
	vector<long double> result = arr;
	for (int i = 0; i < size - 1; i++) {
		int min = i;
		for (int j = i + 1; j < size; j++) {
			if (result[min] > result[j])
				min = j;
		}
		if (min != i) {
			long double temp = result[min];
			result[min] = result[i];
			result[i] = temp;
		}
	}
	return result;
}