#include <iostream>
using namespace std;

void task3() {
    long long x, y;
    long double a, b, c, k;
    cin >> x >> y >> a >> b >> c >> k;
    if (x < y) {
        x = 0;
    } else if (x > y) {
        y = 0;
    } else {
        y = 0;
        x = 0;
    }
    if (a > b) {
        if (a > c) {
            a -= k;
        } else {
            c -= k;
        }
    } else if (b > a) {
        if (b > c) {
            b -= k;
        } else {
            c -= k;
        }
    }
    cout << x << " ";
    cout << y << "\n";
    cout << a << " ";
    cout << b << " ";
    cout << c;
}

int main() {
    task3();
    return 0;
}