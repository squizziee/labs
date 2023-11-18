#include <iostream>

#include "task1.h"
using namespace std;

void task1::deploy()
{
	long long X, Y;
	try {
		cin >> X >> Y;
		if (X == 0 && Y != 0) {
			cout << "YES";
		}
		else if (Y == 0 && X != 0) {
			cout << "YES";
		}
		else {
			if (Y % X == 0 || X % Y == 0)
				cout << "YES";
			else
				cout << "NO";
		}
	}
	catch (...) {
		cout << "ERROR";
	}
}
