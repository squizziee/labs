#include <iostream>
#include <cmath>

void task4_1() {
    long long sum = 0,
              lim;
    std::cin >> lim;
    if (lim < 0) {
        std::cout << "Invalid input";
        return;
    }
    for (int i = 0; i < lim; i++) {
        if (i % 2 == 0)
            sum+= i;
    }
    std::cout << sum;
}

long long subFunc(long long sum, long long i, long long lim) {
    if (i % 2 == 0 && i < lim) sum+=i;
    if (i < lim) return subFunc(sum, ++i, lim);
    return sum;
}

void task4_2() {
    long long lim;
    std::cin >> lim;
    if (lim < 0) {
        std::cout << "Invalid input";
        return;
    }
    std::cout << subFunc(0, 1, lim);
}

int main() {
    task4_1();
    return 0;
}
