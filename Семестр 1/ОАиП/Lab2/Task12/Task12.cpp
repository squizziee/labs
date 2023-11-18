#include <iostream>
using namespace std;

void swapd(long double *a, long double *b) {
    long double temp = *a;
    *a = *b;
    *b = temp;
}

void sort(long double base[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (base[j] < base[minIndex])
                minIndex = j;
        }
        if (minIndex != i) {
            swapd(&base[minIndex], &base[i]);
        }
    }
}

void task12() {
    long double a, b, c, x, y;
    cin >> a >> b >> c >> x >> y;
    long double brickDims[] = {a, b, c};
    long double holeDims[] = {x, y};
    sort(brickDims, 3);
    sort(holeDims, 2);
    if (x <= 0 || y <= 0 || a <= 0 || b <= 0 || c <= 0) {
        cout << "Incorrect input";
    } else if (brickDims[0] <= holeDims[0] && brickDims[1] <= holeDims[1])
        cout << "YES";
    else
        cout << "NO";
}

int main() {
    task12();
    return 0;
}