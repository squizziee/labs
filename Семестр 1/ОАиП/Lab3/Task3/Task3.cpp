#include <iostream>
#include <cmath>

void task3() {
    double B = acos(-1) / 2;
    int A = 0,
        M = 20;
    double x = 0;
    for (int i = 0; x < B; i++) {
        x = A + i * ((B - A) / M);
        std::cout << sin(x) - cos(x) << "\n";
    }
}

int main() {
    task3();
    return 0;
}
