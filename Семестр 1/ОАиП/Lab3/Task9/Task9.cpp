#include <iostream>
#include <cmath>

void task9() {
    long a0, n, sum = 0, d;
    std::cin >> a0 >> n >> d;
    long prev = a0;
    for (int i = 1; i <= n; i++) {
        long current = power(2, i - 1) * power(-1, i - 1) * prev;
        std::cout << sum << " ";
        sum += current;
        prev += d;
    }
    std::cout << sum;
}

int main() {
    task9();
    return 0;
}
