#include <iostream>
#include <cmath>

void task6() {
    long long parts;
    std::cin >> parts;
    long double step = 2.0 / parts;
    long double const LOWER_LIM = 0.5,
                      UPPER_LIM = 1.5,
                      LIM_STEP = (UPPER_LIM - LOWER_LIM) / parts;
    long double minVal = LDBL_MAX,
                minValX = LDBL_MAX;
    for (int i = 0; i < parts; i++) {
        for (long double x = LOWER_LIM + i * LIM_STEP;
        x <= UPPER_LIM - (parts - i - 1) * LIM_STEP; x+=step) {
            long double funcVal = sqrtl(cosl(x)) + logl(sinl(x)) - 0.5;
            if (fabsl(funcVal) < fabsl(minVal)) {
                minVal = funcVal;
                minValX = x;
            }
        }
    }
    std::cout << minValX;
}

int main() {
    task6();
    return 0;
}
