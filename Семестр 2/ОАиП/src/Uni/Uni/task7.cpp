#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

#define PI acos(-1)

double toDegrees(double angle);

void task7()
{
	int x1, y1, x2, y2, x3, y3;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	long double side1 = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	long double side2 = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
	long double side3 = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));

	//if (side1 + side2 >= side3 || side2 + side3 >= side2 || side3 + side1 >= side2)
	//	return;

	long double p = (side1 + side2 + side3) / 2.0;
	long double area1 = sqrt(p * (p - side1) * (p - side2) * (p - side3));

	long double height1 = 2.0 * area1 / side1;

	long double area2 = height1 * side1 / 2.0;
	long double area3 = 0.5 * sin(acos((side2 * side2 + side1 * side1 - side3 * side3) / (2 * side2 * side1))) * side1 * side2;

	long double height2 = 2.0 * area2 / side2;
	long double height3 = 2.0 * area2 / side3;

	long double median1 = 0.5 * sqrt(2 * (side2 * side2 + side3 * side3) - side1 * side1);
	long double median2 = 0.5 * sqrt(2 * (side1 * side1 + side3 * side3) - side2 * side2);
	long double median3 = 0.5 * sqrt(2 * (side2 * side2 + side1 * side1) - side3 * side3);

	long double R = (side1 * side2 * side3) / (4.0 * area1);
	long double r = area1 / p;

	long double bisectrix1 = sqrt(side2 * side3 * p * 2 * (side2 + side3 - side1)) / (side2 + side3);
	long double bisectrix2 = sqrt(side1 * side3 * p * 2 * (side1 + side3 - side2)) / (side1 + side3);
	long double bisectrix3 = sqrt(side2 * side1 * p * 2 * (side1 + side2 - side3)) / (side2 + side1);

	long double angle1 = acos((side2 * side2 + side1 * side1 - side3 * side3) / (2 * side2 * side1));
	long double angle2 = acos((side2 * side2 + side3 * side3 - side1 * side1) / (2 * side3 * side2));
	long double angle3 = acos((side1 * side1 + side3 * side3 - side2 * side2) / (2 * side3 * side1));

	long double rArea = PI * r * r;
	long double rLength = 2.0 * PI * r;
	long double RArea = PI * R * R;
	long double RLength = 2.0 * PI * R;

	cout << setprecision(5);
	cout << "Side A : " << side1 << "\n";
	cout << "Side B : " << side2 << "\n";
	cout << "Side C : " << side3 << "\n";
	cout << "Height 1 : " << height1 << "\n";
	cout << "Height 2 : " << height2 << "\n";
	cout << "Height 3 : " << height3 << "\n";
	cout << "Median 1 : " << median1 << "\n";
	cout << "Median 2 : " << median2 << "\n";
	cout << "Median 3 : " << median3 << "\n";
	cout << "Bisectrix 1 : " << bisectrix1 << "\n";
	cout << "Bisectrix 2 : " << bisectrix2 << "\n";
	cout << "Bisectrix 3 : " << bisectrix3 << "\n";
	cout << "Angle 1 : " << angle3 << " " << toDegrees(angle3) << "\n";
	cout << "Angle 2 : " << angle1 << " " << toDegrees(angle1) << "\n";
	cout << "Angle 3 : " << angle2 << " " << toDegrees(angle2) << "\n";
	cout << "Outer circumference radius : " << R << "\n";
	cout << "Inner circumference radius : " << r << "\n";
	cout << "Inner circumference length : " << rLength << "\n";
	cout << "Inner circumference area : " << rArea << "\n";
	cout << "Outer circumference length : " << RLength << "\n";
	cout << "Outer circumference area : " << RArea << "\n";
	cout << "Square of triangle = " << area2 << " or " << area2 << " or " << area2 << "\n";
	cout << "Perimeter : " << p * 2 << "\n";
}

double toDegrees(double angle) {
	return angle * 180 / PI;
}

int main() {
	task7();
	return 0;
}