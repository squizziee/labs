#include <iostream>
using namespace std;

void task4() {
    long double X, Y;
    std::cin >> X >> Y;
    long double biggest = X > Y ?
            X : (X == Y ? X : Y);
    bool xBiggerThanY = X > Y;
    bool xEqualsY = X == Y;
    long double biggestButLonger = xBiggerThanY ? X : (xEqualsY ? X : Y);
    cout << "No logic variable : " << biggest << "\n";
    std::cout << "With logic variable : " << biggestButLonger << "\n";
}

int main() {
    task4();
    return 0;
}