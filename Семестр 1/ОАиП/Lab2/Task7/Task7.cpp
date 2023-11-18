#include <iostream>
#include <cmath>
using namespace std;

void task7() {
    long double a, b, c, Y;
    long long N;
    cin >> a >> b >> c >> N;
    switch (N) {
        case 2:
            Y = b * c - a * a;
            break;
        case 56:
            Y = b * c;
            break;
        case 7:
            Y = a * a + c;
            break;
        case 3:
            Y = a - b * c;
            break;
        default:
            Y = powl(a + b, 3);
            break;
    }
    cout << Y;
}

int main() {
    task7();
    return 0;
}