#include <iostream>
#include <cmath>

void swapd(long double *a, long double *b) {
    long double temp = *a;
    *a = *b;
    *b = temp;
}

void sort(long double base[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (base[j] < base[minIndex])
                minIndex = j;
        }
        if (minIndex != i) {
            swapd(&base[minIndex], &base[i]);
        }
    }
}

long double power(long double a, long long b) {
    long double result = 1;
    for (int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}

long double absolute(long double x) {
    return (x < 0) ? (-x) : (x);
}

long double rotate(long double x) {
    long double PI = acos(-1);
    bool isPositive = true;
    if (x < 0) isPositive = false;
    x = absolute(x);
    auto sector = (unsigned long long) (x / (2.0 * PI));
    int frac = 10;
    for (int i = 0; i < frac; i++) {
        x -= sector * (PI / frac);
    }

    x -= sector * (PI / 2.0);
    x -= sector * (PI / 2.0);
    if (isPositive) {
        return x;
    } else {
        return -x;
    }
}

long double countSin(long double x) {
    x = rotate(x);
    long long n = 10;
    
    long double val = 0;
    for (long long j = 0; j <= n; j++) {
        val = val + power(-1, j) * (power(x, 2 * j + 1) / factorial(2 * j + 1));
    }
    return val;
}

long double countCos(long double x) {
    x = rotate(x);
    x = absolute(x);
    long long n = 10;
    long double val = 0;
    for (long long j = 0; j <= n; j++) {
        val = val + power(-1, j) * (power(x, 2 * j) / factorial(2 * j));
    }
    return val;
}

long double e = 2.7182818284590452353602874713527;

long double countLn(long double x) {
    if (x == 0) {
        std::cout << "Invalid input";
        exit(1488);
    }
    x = absolute(x);
    long long powers = 0;
    while (x > 1) {
        ++powers;
        x /= e;
    }
    while (x < 0.01) {
        powers--;
        x *= e;
    }
    long long n = 200;
    long double temp = (x - 1.0) / (1.0 + x);
    long double ans = 0;
    for (int i = 0; i <= n; i++) {
        ans += power(temp, 2 * i + 1) * (1 / (2.0L * i + 1));
    }
    return ans * 2 + powers;
}

void task7() {
    long double x;
    std::cin >> x;
    long double result1 = countSin(x),
                result2 = countCos(x),
                result3 = countLn(x);
    std::cout << result1 << "\n"
              << result2 << "\n"
              << result3 << "\n";
    long double arr[] = {countSin(x), countCos(x), countLn(x)};
    sort(arr, 3);
    std::cout << arr[0];
}

int main() {
    task7();
    return 0;
}
