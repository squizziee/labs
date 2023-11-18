#include <iostream>
#include <cmath>
using namespace std;

void task11() {
    long double R, P, Q;
    cin >> R >> P >> Q;
    long double radians = Q * (3.141592 / 180);
    long double r = P * sin(radians) / 2;
    if (R <= r)
        cout << "YES";
    else
        cout << "NO";
}

int main() {
    task11();
    return 0;
}