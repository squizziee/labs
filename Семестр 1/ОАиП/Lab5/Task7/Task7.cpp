#include <iostream>
#include <vector>
#include <cmath>

unsigned long long recursive_func(unsigned long long arg1,
    unsigned long long arg2,
    unsigned long long arg3) {
    if (arg2 == 0) {
        return 1;
    }
    if (arg2 % 2 != 0) {
        return arg1 * recursive_func((arg1 * arg1) % arg3, arg2 / 2, arg3) % arg3;
    }
    return recursive_func((arg1 * arg1) % arg3, arg2 / 2, arg3);
}

int main() {
    std::vector<unsigned long long> results;
    int _case = 1;
    while (1) {
        unsigned long long k, n, t;
        std::cin >> k >> n >> t;
        if (k == 0 && n == 0 && t == 0) {
            break;
        }
        unsigned long long temp = powl(10, t);
        unsigned long long ans;
        ans = recursive_func(k % temp, n, temp);
        results.push_back(ans);
    }
    for (unsigned long long ans : results) {
        std::cout << "Case #" << _case++ << ": " << ans << "\n";
    }
    return 0;
}