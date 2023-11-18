#include <iostream>
#include <cmath>

void task2() {
    long double const EPSILON = 0.001;
    long double sum = 0;
    long double dn;
    long long n = 1;
    do {
        dn = powl (1.0 / 2.0, n) + powl (1.0 / 3.0, n);
        sum += dn;
        n++;
    } while (dn >= EPSILON);
    std::cout << sum;
}

int main() {
    task2();
    return 0;
}
