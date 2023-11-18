#include <iostream>
#include <cmath>
#include "task6.h"
using namespace std;

long double subTask1();
long double subTask2();
long double subTask3();
long double subTask4();
long double subTask5();
long double subTask6();
long double subTask7();
long double subTask8();
long double subTask9();
long double subTask10();

void task6(int variant)
{
	switch (variant) {
	case 1:
		printf("Result, variant 1 : %f", subTask1());
		break;
	case 2:
		printf("Result, variant 2 : %f", subTask2());
		break;
	case 3:
		printf("Result, variant 3 : %f", subTask3());
		break;
	case 4:
		printf("Result, variant 4 : %f", subTask4());
		break;
	case 5:
		printf("Result, variant 5 : %f", subTask5());
		break;
	case 6:
		printf("Result, variant 6 : %f", subTask6());
		break;
	case 7:
		printf("Result, variant 7 : %f", subTask7());
		break;
	case 8:
		printf("Result, variant 8 : %f", subTask8());
		break;
	case 9:
		printf("Result, variant 9 : %f", subTask9());
		break;
	case 10:
		printf("Result, variant 10 : %f", subTask10());
		break;
	default:
		break;
	}
}

long double subTask1() {
	long double A, b, x, D;
	cin >> x >> D;
	b = x + D;
	A = D * x / b;
	long double S = (A * A + b * cos(x)) / (D * D * D + (A + D - b));
	return S;
}

long double subTask2() {
	long double A, B, D, C, K, p, x;
	cin >> D >> C >> K >> p >> x;
	A = x + sin(p);
	B = exp(K);
	long double Y = 1.0 + (K * K) / (2.0 * A * B) - B + D * C;
	return Y;
}

long double subTask3() {
	long double B, C, K, D, p, n, x;
	cin >> K >> D >> p >> n >> x;
	B = cos(x);
	C = p - n;
	long double Q = (B * B) / (K * D) + B * C * C * C;
	return Q;
}

long double subTask4() {
	long double A, B, z, x, y, C, D, K;
	cin >> z >> x >> y >> C >> D >> K;
	A = x - y;
	B = sqrt(z);
	long double T = cos(x) + (A * A) / (K - C * D) - B;
	return T;
}

long double subTask5() {
	long double K, A, D, n, m, x;
	cin >> n >> m >> x >> K;
	A = fabs(n + m);
	D = tan(x);
	long double Y = 1.29 + K / A + D * D;
	return Y;
}

long double subTask6() {
	long double A, D, C, K, x, y;
	cin >> K >> C >> x >> y;
	A = x + y;
	D = fabs(C - A);
	long double S = 10.1 + A / C + D / (K * K);
	return S;
}

long double subTask7() {
	long double h, x, p, K, C, D, A, B;
	cin >> h >> x >> p >> K >> C >> D;
	A = x - p;
	B = log(h);
	long double Y = 0.78 * B + (A * A * A) / (K * C * D);
	return Y;
}

long double subTask8() {
	long double A, B, C, K, x, d;
	cin >> x >> d >> C >> K;
	A = log10(x);
	B = x + exp(d);
	long double Y = (A + B) - (C * C) / K;
	return Y;
}

long double subTask9() {
	long double A, B, C, K, D, x, z, p;
	cin >> C >> K >> D >> x >> z >> p;
	A = sin(x) - z;
	B = fabs(p - x);
	long double Y = (A + B) * (A + B) - K / (C * D);
	return Y;
}

long double subTask10() {
	long double A, B, C, k, D, x, z;
	cin >> C >> k >> D >> x >> z;
	A = log(x) - k;
	B = sqrt(z);
	long double Y = D * D + (C * C) / (0.75 * A) + B;
	return Y;
}

int main() {
	int n;
	cin >> n;
	task6(n);
	return 0;
}