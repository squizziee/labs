#include <iostream>
using namespace std;

void task2() {
    long double X, Y, Z;
    std::cin >> X >> Y >> Z;
    if (X + Y >= Z && X + Z >= Y && Z + Y >= X)
        std::cout << "YES";
    else
        std::cout << "NO";
}

int main() {
    task2();
    return 0;
}