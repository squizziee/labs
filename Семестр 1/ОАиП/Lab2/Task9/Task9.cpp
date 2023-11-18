#include <iostream>
#include <cmath>
using namespace std;

void task9() {
    // number 8
    short funcID;
    long double x, a, c, z;
    long double function = -1;
    cin >> funcID >> a >> c >> z;
    if (z >= 0) {
        x = 2 * z + 1;
    } else {
        x = log(z * z - z);
    }
    switch (funcID) {
        case 1:
            function = 2 * x;
            break;
        case 2:
            function = x * x * x;
            break;
        case 3:
            function = x / 3;
            break;
        default:
            cout << "Incorrect input (funcId)";
            break;
    }
    long double y = powl(sin(function), 2.0) + a * powl(cos(x * x * x),  5.0)
            + c * log(powl(x, 0.4));
    cout << y << "\n";
}

int main() {
    task9();
    return 0;
}