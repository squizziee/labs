#include <iostream>
using namespace std;

void task1() {
    long long X, Y;
    try {
        cin >> X >> Y;
        if ((X == 0 && Y != 0) || (Y == 0 && X != 0))
            cout << "YES";
        else {
            if (X % Y == 0 || Y % X == 0)
                cout << "YES";
            else
                cout << "NO";
        }
    } catch(...) {
        cout << "ERROR";
    }
}

int main() {
    task1();
    return 0;
}