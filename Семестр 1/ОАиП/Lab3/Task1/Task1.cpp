#include <iostream>
#include <cmath>

void task1() {
    long double sum = 0;
    int i = 1;
    while (i <= 30) {
        if (i % 2 == 0) {
            sum += powl((long double) i / 2 - i * i * i, 2);
        } else {
            sum += powl((long double) i - i * i, 2);
        }
        ++i;
    }
    std::cout << sum;
}

int main() {
    task1();
    return 0;
}
