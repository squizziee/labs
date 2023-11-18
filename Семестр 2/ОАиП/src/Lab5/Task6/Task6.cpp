#include <iostream>
#include <vector>

int F(int n) {
    if (n % 10 > 0) {
        return n % 10;
    }
    else if (n == 0) {
        return 0;
    }
    else {
        return F(n / 10);
    }
}

int S(int p, int q) {
    int ans = 0;
    for (int i = p; i <= q; i++) {
        ans += F(i);
    }
    return ans;
}

int main() {
    int p = 1, q = 2;
    std::vector<int> output;
    while (p >= 0 && q >= 0) {
        std::cin >> p >> q;
        if (p < 0 || q < 0) {
            break;
        }
        output.push_back(S(p, q));
    }
    for (int el : output) {
        std::cout << el << "\n";
    }
}