#include <iostream>
using namespace std;

void task13() {
    long long shrooms;
    setlocale(0, "");
    cin >> shrooms;
    long long lastDigit = shrooms % 10;
    long long bfLastDigit = ((shrooms % 100) - (shrooms % 10)) / 10;
    string ending;
    if (bfLastDigit == 1 || lastDigit >= 5 || lastDigit == 0)
        ending = "ов";
    else if (lastDigit == 1)
        ending = "";
    else if (lastDigit >= 2)
        ending = "а";
    else
        ending = "ов";
    cout << "Мы нашли " << shrooms << " гриб" << ending << " в лесу";
}


int main() {
    task13();
    return 0;
}