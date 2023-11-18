#include <iostream>
#include <cmath>

void task8() {
    long long lim;
    std::cin >> lim;
    for (long i = 1; i < lim; i++) {
        int power = (int) log10l(i) + 1;
        long temp = i;
        long double sum = 0;
        while (temp > 0) {
            sum += powl(temp % 10, power);
            temp /= 10;
        }
        if (sum == i)
            std::cout << i << " ";
    }
}

int main() {
    task8();
    return 0;
}
