#include <iostream>
#include <set>

int subtract(uint32_t x, uint32_t y) {
    while (y) {
        uint32_t borrow = (~x) & y;
        x = x ^ y;
        y = borrow << 1;
    }
    return x;
}

int add(uint32_t x, uint32_t y) {
    while (y) {
        uint32_t carry = x & y;
        x = x ^ y;
        y = carry << 1;
    }
    return x;
}

uint32_t divide(int num1, int num2) {
    int temp = 1, result = 0;
    while (num2 <= num1) {
        num2 <<= 1;
        temp <<= 1;
    }
    while (temp > 1) {
        num2 >>= 1;
        temp >>= 1;
        if (num1 >= num2) {
            num1 =  subtract(num1, num2);
            result = add(result, temp);
        }
    }
        return result;
}

uint32_t multiply(uint32_t a, uint32_t b) {
    uint32_t result = 0;
    while (b)
    {
        if (b & 01)
        {
            result = add(result, a);
        }
        a <<= 1;
        b >>= 1;
    }
    return result;
}

uint32_t mod(uint32_t a, uint32_t b) {
    uint32_t r = divide(a, b);
    return subtract(a, multiply(r, b));
}

int main()
{
    int n;
    std::cin >> n;
    if (mod(n, 11) == 0) {
        std::cout << "Can be divided by 11\n";
    }
    else {
        std::cout << "Can not be divided by 11\n";
    }
    if (mod(n, 31) == 0) {
        std::cout << "Can be divided by 31\n";
    }
    else {
        std::cout << "Can not be divided by 31\n";
    }
    if (mod(n, 113) == 0) {
        std::cout << "Can be divided by 113\n";
    }
    else {
        std::cout << "Can not be divided by 113\n";
    }
    // 11 31 113
}