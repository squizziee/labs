#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>
#include <climits>
#include <stdio.h>
using namespace std;

#define PI 3.14159265
#define g 9.809

double calc(double a1, double d, int index);
double toDegrees(double angle);
void task1();
void task2();
void task3();
void task4();
void task5();
void task7();

int main()
{
	task5();
	return 0;
}

void task1() {
	double x;
	cin >> x;
	cout << 23 * x * x * (x + 3) + 32 * x + 8;
	cout << 23 * x * x * (3 - x) - 32 * x + 8;
}

void task2() {
	int h;
	cin >> h;
	cout << sqrt(2 * h / g);
}

void task3() {
	int t, v0, a;
	cin >> t >> v0 >> a;
	cout << v0 * t + a * pow(t, 2) / 2;
}

void task4() {
	int b1, q, n;
	n = 14;
	q = 1 / (n + 1);
	cin >> b1;
	cout << b1 / (1 - q);
}

void task5() {
	int a1, a100, d;
	cin >> a1 >> a100;
	d = (a100 - a1) / 99;
	cout << d << " " << 70 / 2 * (a1 + calc(a1, d, 70));
}

double calc(double a1, double d, int index) {
	return a1 + (index - 1) * d;
}

void task7() {
	int x1, y1, x2, y2, x3, y3;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	double side1 = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	double side2 = sqrt(pow(x2 - x3, 2) + pow(y2 - y3, 2));
	double side3 = sqrt(pow(x3 - x1, 2) + pow(y3 - y1, 2));

	double p = (side1 + side2 + side3) / 2;
	double area1 = sqrt(p * (p - side1) * (p - side2) * (p - side3));

	double height1 = 2 * area1 / side1;

	double area2 = height1 * side1 / 2;
	double area3 = 0.5 * sin(acos((pow(side2, 2) + pow(side1, 2) - pow(side3, 2)) / (2 * side2 * side1)))
		* side1 * side2;

	double height2 = 2 * area2 / side2;
	double height3 = 2 * area3 / side3;

	double median1 = sqrt(2 * (pow(side2, 2) + pow(side3, 2)) - pow(side1, 2)) / 2;
	double median2 = sqrt(2 * (pow(side1, 2) + pow(side3, 2)) - pow(side2, 2)) / 2;
	double median3 = sqrt(2 * (pow(side2, 2) + pow(side1, 2)) - pow(side3, 2)) / 2;

	double bisectrix1 = 2 * sqrt(side2 * side3 * p * (p - side1)) / (side2 + side3);
	double bisectrix2 = 2 * sqrt(side1 * side3 * p * (p - side2)) / (side1 + side3);
	double bisectrix3 = 2 * sqrt(side2 * side1 * p * (p - side3)) / (side2 + side1);

	double angle1 = acos((pow(side2, 2) + pow(side1, 2) - pow(side3, 2)) / (2 * side2 * side1));
	double angle2 = acos((pow(side1, 2) + pow(side3, 2) - pow(side2, 2)) / (2 * side1 * side3));
	double angle3 = acos((pow(side2, 2) + pow(side3, 2) - pow(side1, 2)) / (2 * side2 * side3));

	double R = (side1 * side2 * side3) / (4 * area1);
	double r = sqrt((p - side1) * (p - side2) * (p - side3) / p);

	double rArea = PI * pow(r, 2);
	double rLength = 2 * PI * r;
	double RArea = PI * pow(R, 2);
	double RLength = 2 * PI * R;

	cout << setprecision(5);
	cout << side1 << "\n";
	cout << side2 << "\n";
	cout << side3 << "\n";
	cout << height1 << "\n";
	cout << height2 << "\n";
	cout << height3 << "\n";
	cout << median1 << "\n";
	cout << median2 << "\n";
	cout << median3 << "\n";
	cout << bisectrix1 << "\n";
	cout << bisectrix2 << "\n";
	cout << bisectrix3 << "\n";
	cout << angle1 << " " << toDegrees(angle1) << "\n";
	cout << angle2 << " " << toDegrees(angle2) << "\n";
	cout << angle3 << " " << toDegrees(angle3) << "\n";
	cout << R << "\n";
	cout << r << "\n";
	cout << rLength << "\n";
	cout << rArea << "\n";
	cout << RLength << "\n";
	cout << RArea << "\n";
	printf("Square of triangle = %d or %d or %d\n", (int)area1, (int)area2, (int)area3);
	cout << p * 2 << "\n";
}

double toDegrees(double angle) {
	return angle * 180 / PI;
}