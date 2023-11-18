#include <iostream>
#include <iomanip>

#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"
#include "task6.h"
#include "task7.h"
#include "task8.h"
#include "task9.h"
using namespace std;

int main()
{
	task7::deploy();
	return 0;
}

//void findDist() {
//	long double k, x, y;
//	cin >> k >> x >> y;
//	if (x <= k && x >= 0 && y <= k && y >= 0) {
//		long double xDist = k - x,
//					yDist = k - y;
//		long double arr[] = {x, y, xDist, yDist};
//		sort(arr, arr + 4);
//		cout << arr[0];
//	}
//	else {
//		if (x > 0 && y > 0) {
//			if (y > k && x > k) {
//				cout << sqrt((x - k) * (x - k) + (y - k) * (y - k));
//			}
//			else if (x <= k && y > k) {
//				cout << y - k;
//			}
//			else if (x > k && y <= k) {
//				cout << x - k;
//			}
//		}
//		else {
//			if (x <= 0 && y <= 0) {
//				cout << sqrt(x * x + y * y);
//			}
//			else if (x <= k && x > 0 && y < 0) {
//				cout << -y;
//			}
//			else if (x > k && y < 0) {
//				cout << -y;
//			}
//			else if (x <= 0 && y <= k && y > 0) {
//				cout << -x;
//			}
//			else if (x <= 0 && y > k) {
//				cout << sqrt(x * x + (y - k) * (y - k));
//			}
//		}
//	}
//	cout << endl;
//}