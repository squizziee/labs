#include <iostream>
using namespace std;

void task6() {
    long double a, b, c, d, Z;
    cin >> a >> b >> c >> d;
    if (c >= d && a < d)
        Z = a + b / c;
    else if (c < d && a >= d)
        Z = a - b / c;
    else
        Z = 0;
    cout << Z;
}

int main() {
    task6();
    return 0;
}