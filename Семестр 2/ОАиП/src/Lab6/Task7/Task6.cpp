#include <iostream>
#include <map>

int factorial(int n) {
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        ans *= i;
    }
    return ans;
}

int main() {
    std::string str;
    std::cin >> str;
    std::map<char, int> counts;
    for (char c : str) {
        if (counts.find(c) == counts.end()) {
            counts.insert({ c, 1 });
        }
        else {
            int count = counts.at(c);
            counts.at(c) = count + 1;
        }
    }
    int tempDivident = 0;
    int tempDivisor = 1;
    for (std::pair<char, int> pair : counts) {
        tempDivident += pair.second;
        tempDivisor *= factorial(pair.second);
    }
    int divident = factorial(tempDivident);
    int divisor = tempDivisor;
    std::cout << divident / divisor;
}