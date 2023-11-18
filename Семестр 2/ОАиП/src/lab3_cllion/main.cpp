#include <iostream>
#include <cmath>
#include <iomanip>

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

long long factorial(long long n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

void task5() {
    long long testsCount, n;
    std::cin >> testsCount >> n;
    if (n > 40) {
        std::cout << "n is too big, try n <= 40\n";
        return;
    }
    for (int i = 0; i < testsCount; i++) {
        long double temp;
        std::cin >> temp;
        if (temp > 1 || temp < 0.09999) {
            std::cout << "Invalid input";
            return;
        }
		long double val1, val2 = 0;
		for (long long j = 1; j < n; j++) {
			val2 = val2 + (powl(2 * temp, j) / factorial(j));
		}
		val1 = expl(2 * temp);
		std::cout << val1 << " " << 1 + val2 << "\n";
    }
   
}

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
//    if (x >= 2 * PI) {
//        while (x > 0) {
//            x -= 2 * PI;
//        }
//    } else if (x <= -2 * PI) {
//        while (x < 0) {
//            x += 2 * PI;
//        }
//    }
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
    task7();
    //std::cout << std::setprecision(22) << countSin(1e-20);
    //std::cout << std::setprecision(22) << (long double) 0.3;
    return 0;
}
