#include <iostream>

std::string revert(std::string str) {
    char sign = str[0];
    std::string ans;
    ans.push_back(sign);
    for (int i = 1; i < str.size(); i++) {
        if (str[i] == '1') {
            ans.push_back('0');
        }
        else if (str[i] == '0') {
            ans.push_back('1');
        }
        else {
            std::cout << "Invalid input";
            return "";
        }
    }
    return ans;
}

int main() {
    std::string invertedCode;
    std::cin >> invertedCode;
    std::cout << revert(invertedCode);

}