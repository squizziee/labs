#include <iostream>
#include <cmath>
using namespace std;

void task10() {
    long double x1, y1, r, x2, y2, R;
    cin >> x1 >> y1 >> r >> x2 >> y2 >> R;
    long double dist = sqrt(powl(x2 - x1, 2) + powl(y2 - y1, 2));
    long double radiusSum = R + r;
    if (radiusSum >= dist && dist < R - r && r < R) {
        cout << "Yes";
    } else if (radiusSum >= dist && dist < r - R && r > R) {
        cout << "Yes, but the other way around";
    } else if (radiusSum < dist) {
        cout << "None of the conditions are true";
    } else if (radiusSum >= dist) {
        cout << "Circles intersect";
    }
}

int main() {
    task10();
    return 0;
}