#include <iostream>
using namespace std;

bool isInBounds(long double x, long double y, long double k) {
    if (k >= 0) {
        if (x <= k && y <= k && y >= 0 && x >= 0)
            return true;
    }
    else {
        if (x >= k && y >= k && y <= 0 && x <= 0)
            return true;
    }
    return false;
}

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

void task5() {
    long double x, y, k;
    cin >> k >> x >> y;
    long double result = -1;
    if (isInBounds(x, y, k)) {
        if (k < 0) {
            x = 0 - x;
            y = 0 - y;
            k = 0 - k;
        }
        long double xDist = k - x;
        long double yDist = k - y;
        long double arr[] = {x, y, xDist, yDist};
        sort(arr, 4);
        cout << arr[0];
    } else {
        if (k < 0) {
            x = 0 - x;
            y = 0 - y;
            k = 0 - k;
        }
        if (y > k && x > k) {
            result = sqrt((x - k) * (x - k) + (y - k) * (y - k));
        } else if (x < k && y >= k && x > 0) {
            result = y - k;
        } else if (x >= k && y < k && y > 0) {
            result = x - k;
        } else if (x < 0 && y < 0) {
            result = sqrt(x * x + y * y);
        } else if (x <= k && x > 0 && y < 0) {
            result = -y;
        } else if (x > k && y < 0) {
            result = sqrt(y * y + (x - k) * (x - k));
        } else if (x <= 0 && y <= k && y > 0) {
            result = -x;
        } else if (x < 0 && y > k) {
            result = sqrt(x * x + (y - k) * (y - k));
        }
        cout << setprecision(22) << result;
    }
}

int main() {
    task5();
    return 0;
}