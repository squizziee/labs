#include <iostream>

char getDigit(int remainder) {
    return remainder + 48;
}

void replaceAll(std::string& str, std::string toReplace, std::string replacement) {
    int occurence = str.find(toReplace);
    while (occurence != std::string::npos) {
        str.replace(occurence, 2, replacement);
        occurence = str.find(toReplace);
    }
}

std::string convert(long long n) {
        std::string ans;
        while (n >= 3) {
            ans.push_back(getDigit(n % 3));
            n /= 3;
        }
        ans.push_back(getDigit(n));
        reverse(ans.begin(), ans.end());
        replaceAll(ans, "10", "03");
        replaceAll(ans, "20", "13");
        replaceAll(ans, "30", "23");
        return (ans[0] == '0') ? ans.substr(1) : ans;
}

int main()
{
    int number;
    std::cin >> number;
    std::cout << convert(number);
}