#include <iostream>

struct UNumber {
private:
    int BASE;
    //int sign;
    std::string value;
    char getDigit(int remainder) {
        if (remainder <= 9) {
            return remainder + 48;
        }
        else {
            return remainder + 55;
        }
    }

    int getOffset(char digit) {
        if (digit >= 65 && digit <= 90) {
            return 55;
        }
        if (digit >= 48 && digit <= 58) {
            return 48;
        }
    }

    void addPrefix(std::string& num1, std::string& num2) {
        if (num1.size() > num2.size()) {
            std::string prefix;
            for (int i = 0; i < num1.size() - num2.size(); i++) {
                prefix.push_back('0');
            }
            num2 = prefix + num2;
        }
        else if (num2.size() > num1.size()) {
            std::string prefix;
            for (int i = 0; i < num2.size() - num1.size(); i++) {
                prefix.push_back('0');
            }
            num1 = prefix + num1;
        }
    }

    std::string add(int base, std::string num1, std::string num2) {
        /*if (num1[0] == '-') {
            return subtract()
        }*/
        bool negative = false;
        if (num1[0] == '-' && num2[0] == '-') {
            negative = true;
        }
        else if (num1[0] == '-') {
            return substract(base, num2, num1.substr(1));
        }
        else if (num2[0] == '-') {
            return substract(base, num1, num2.substr(1));
        }
        std::string result;
        int carry = 0;
        addPrefix(num1, num2);
        for (int i = num1.size() - 1; i >= 0; i--) {
            int exp = (num1[i] - getOffset(num1[i]) + num2[i] - getOffset(num2[i]) + carry);
            int remainder = exp % base;
            carry = exp / base;
            result.push_back(getDigit(remainder));
        }
        if (carry) {
            result.push_back(getDigit(carry));
        }
        if (negative) {
            result.push_back('-');
        }
        reverse(result.begin(), result.end());
        if (result[0] == '0' && result.size() > 1) {
            result = result.substr(1);
        }
        if (result[0] == '-' && result.size() > 2) {
            if (result[1] == '0') {
                result = result[0] + result.substr(2);
            }
        }
        return result;
    }

    std::string substract(int base, std::string num1, std::string num2) {
        std::string result;
        int carry = 0;
        addPrefix(num1, num2);
        bool negative = false;
        if (num1[0] == '-') {
            return add(base, num1.substr(1), num2);
        }
        else if (num2[0] == '-') {
            return add(base, num2.substr(1), num1);
        }
        if (num1 < num2) {
            std::string temp = num1;
            num1 = num2;
            num2 = temp;
            negative = true;
        }
        for (int i = num1.size() - 1; i >= 0; i--) {
            if (num1[i] >= num2[i]) {
                int exp = (num1[i] - getOffset(num1[i]) - (num2[i] - getOffset(num2[i])) + carry);
                result.push_back(getDigit(exp));
            }
            else {
                carry = base;
                num1[i - 1]--;
                int exp = (num1[i] - getOffset(num1[i]) - (num2[i] - getOffset(num2[i])) + carry);
                result.push_back(getDigit(exp));
            }
            carry = 0;
        }
        if (negative) {
            result.push_back('-');
        }
        reverse(result.begin(), result.end());
        if (result[0] == '0' && result.size() > 1) {
            result = result.substr(1);
        }
        return result;
    }
public :
    UNumber(const int base, std::string value) {
        this->BASE = base;
        this->value = value;
    }

    UNumber operator+(UNumber operand) {
        if (this->BASE == operand.BASE) {
            UNumber result(BASE, add(BASE, this->value, operand.value));
            return result;
        }
        return UNumber(BASE, "");
    }

    UNumber operator-(UNumber operand) {
        if (this->BASE == operand.BASE) {
            UNumber result(BASE, substract(BASE, this->value, operand.value));
            return result;
        }
        return UNumber(BASE, "");
    }

    std::string toString() {
        return value;
    }
};

int main() {
    //std::cout << substract(16, "CCCC", "B78");
    int base;
    std::string literal1, literal2;
    std::cin >> base >> literal1 >> literal2;
    UNumber a(36, literal1);
    UNumber b(36, literal2);
    std::cout << "Sum: " << (a + b).toString() << "\n";
    std::cout << "Diff: " << (a - b).toString() << "\n";
}