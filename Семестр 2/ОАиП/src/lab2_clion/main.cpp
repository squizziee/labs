#include <iostream>
#include <iomanip>
#include <cmath>
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

void task2() {
    long double X, Y, Z;
    std::cin >> X >> Y >> Z;
    if (X + Y >= Z && X + Z >= Y && Z + Y >= X)
        std::cout << "YES";
    else
        std::cout << "NO";
}

void task3() {
    long long x, y;
    long double a, b, c, k;
    cin >> x >> y >> a >> b >> c >> k;
    if (x < y) {
        x = 0;
    } else if (x > y) {
        y = 0;
    } else {
        y = 0;
        x = 0;
    }
    if (a > b) {
        if (a > c) {
            a -= k;
        } else {
            c -= k;
        }
    } else if (b > a) {
        if (b > c) {
            b -= k;
        } else {
            c -= k;
        }
    }
    cout << x << " ";
    cout << y << "\n";
    cout << a << " ";
    cout << b << " ";
    cout << c;
}

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

void task6() {
    long double a, b, c, d, Z;
    cin >> a >> b >> c >> d;
    if (c >= d && a < d)
        Z = a + b / c;
    else if (c < d && a >= d)
        Z = a - b / c;
    else
        Z = 0;
    cout << Z;
}

void task7() {
    long double a, b, c, Y;
    long long N;
    cin >> a >> b >> c >> N;
    switch (N) {
        case 2:
            Y = b * c - a * a;
            break;
        case 56:
            Y = b * c;
            break;
        case 7:
            Y = a * a + c;
            break;
        case 3:
            Y = a - b * c;
            break;
        default:
            Y = powl(a + b, 3);
            break;
    }
    cout << Y;
}

void task8_1() {
    long double a, b, c;
    cin >> a >> b >> c;
    if (a == 0 && b == 0 && c == 0) {
        cout << "Any number";
        return;
    }
    if (a == 0 && b == 0) {
        cout << "No solutions found";
        return;
    }
    if (a == 0 && c == 0) {
        cout << 0;
        return;
    }
    if (a == 0) {
        if (sqrt(-c / b) > 0) {
            cout << sqrt(-c / b) << " ";
            cout << -sqrt(-c / b);
        } else
            cout << "No solutions found";
        return;
    }
    long double disc = b * b - 4 * a * c;
    bool anyRoots = false;
    if (disc > 0) {
        if (a != 0) {
            long double sq1 = (-b - sqrt(disc)) / (2 * a);
            long double sq2 = (-b + sqrt(disc)) / (2 * a);
            if (sq2 >= 0) {
                anyRoots = true;
                if (sq2 == 0) {
                    cout << 0 << " ";
                } else {
                    cout << sqrt(sq2) << " ";
                    cout << -sqrt(sq2) << " ";
                }
            }
            if (sq1 >= 0) {
                anyRoots = true;
                if (sq1 == 0) {
                    cout << 0 << " ";
                } else {
                    cout << sqrt(sq1) << " ";
                    cout << -sqrt(sq1) << " ";
                }
            }
        }
    }
    else if (disc == 0) {
        anyRoots = true;
        long double sq = -b / (2 * a);
        if (sq == 0)
            cout << 0 << " ";
        else {
            cout << sqrt(sq) << " ";
            cout << -sqrt(sq) << " ";
        }
    }
    if (!anyRoots) {
        cout << "No solutions found";
    }
}

void task8_2() {
    long double a, b, c;
    cin >> a >> b >> c;
    if (a == 0 && b == 0 && c == 0) {
        cout << "Any number";
        return;
    }
    if ((a == 0 && c == 0) || (a == 0 && b == 0)) {
        cout << 0;
        return;
    }
    if (a == 0) {
        cout << 0 << " ";
        long double cff1 = b,
                    cff2 = c,
                    cff3 = b,
                    disc = cff2 * cff2 - 4 * cff1 * cff3;
        if (disc > 0) {
            cout << (-cff2 - sqrt(disc)) / (2 * cff1) << " ";
            cout << (-cff2 + sqrt(disc)) / (2 * cff1) << " ";
        } else if (disc == 0) {
            cout << (cff2 / (2 * cff1)) << " ";
        }
        return;
    }
    long double cff1 = a,
                cff2 = b,
                cff3 = c - 2 * a,
                disc = cff2 * cff2 - 4 * cff1 * cff3;
    bool anyRoots = false;
    if (disc > 0) {
        if (cff1 != 0) {
            long double ans1 = (-cff2 - sqrt(disc)) / (2 * cff1),
                    ans2 = (-cff2 + sqrt(disc)) / (2 * cff1),
                    locDisc1 = powl(ans1, 2.0) - 4.0;
            if (locDisc1 > 0) {
                anyRoots = true;
                cout << (ans1 - sqrt(locDisc1)) / 2 << " ";
                cout << (ans1 + sqrt(locDisc1)) / 2 << " ";
            } else if (locDisc1 == 0) {
                anyRoots = true;
                cout << ans1 / 2 << " ";
            }
            long double locDisc2 = ans2 * ans2 - 4;
            if (locDisc2 > 0) {
                anyRoots = true;
                cout << (ans2 - sqrt(locDisc2)) / 2 << " ";
                cout << (ans2 + sqrt(locDisc2)) / 2 << " ";
            } else if (locDisc2 == 0) {
                anyRoots = true;
                cout << ans2 / 2 << " ";
            }
        }
    }
    else if (disc == 0) {
        long double ans = -cff2 / (2 * cff1),
                    locDisc = ans * ans - 4.0;
        if (locDisc > 0) {
            anyRoots = true;
            cout << (ans - sqrt(locDisc)) / 2 << " ";
            cout << (ans + sqrt(locDisc)) / 2 << " ";
        } else if (locDisc == 0) {
            anyRoots = true;
            cout << (-ans) / 2;
        }
    }
    if (!anyRoots) {
        cout << "No solutions found";
    }
}

void task8_3() {
    long double p, q;
    cin >> p >> q;
    if (p != 0 && q != 0) {
        if (((q * q) / 4.0) + ((p * p * p) / 27.0) < 0 ) {
            cout << 2 * sqrtl(-p / 3) * cos((acos(-(q / 2) * powl(3 / -p, 1.5))) / 3) << " ";
            cout << 2 * sqrtl(-p / 3) * cos((acos(-(q / 2) * powl(3 / -p, 1.5))) / 3 + 2 * acos(-1) / 3) << " ";
            cout << 2 * sqrtl(-p / 3) * cos((acos(-(q / 2) * powl(3 / -p, 1.5))) / 3 - 2 * acos(-1) / 3) << " ";
        } else {
            cout << cbrt((((-1.0) * q) / 2.0) - sqrt(((q*q) / 4.0) + ((p * p * p) / 27.0))) +
                    cbrt((((-1.0) * q) / 2.0) + sqrt(((q*q) / 4.0) + ((p * p * p) / 27.0)));
        }
    } else if (p == 0 && q != 0) {
            cout << cbrt(-1 * q);
    } else if (p != 0 && q == 0) {
        if (p < 0) {
            cout << sqrt(-p);
        } else {
            cout << 0;
        }
    } else if (p == 0 && q == 0) {
            cout << 0;
    } else {
        cout << "Any number";
    }

}

void task9() {
    // number 8
    short funcID;
    long double x, a, c, z;
    long double function = -1;
    cin >> funcID >> a >> c >> z;
    if (z >= 0) {
        x = 2 * z + 1;
    } else {
        x = log(z * z - z);
    }
    switch (funcID) {
        case 1:
            function = 2 * x;
            break;
        case 2:
            function = x * x * x;
            break;
        case 3:
            function = x / 3;
            break;
        default:
            cout << "Incorrect input (funcId)";
            break;
    }
    long double y = powl(sin(function), 2.0) + a * powl(cos(x * x * x),  5.0)
            + c * log(powl(x, 0.4));
    cout << y << "\n";
}

void task10() {
    long double x1, y1, r, x2, y2, R;
    cin >> x1 >> y1 >> r >> x2 >> y2 >> R;
    long double dist = sqrt(powl(x2 - x1, 2) + powl(y2 - y1, 2));
    long double radiusSum = R + r;
    if (radiusSum >= dist && dist < R - r && r < R) {
        cout << "Yes";
    } else if (radiusSum >= dist && dist < r - R && r > R) {
        cout << "Yes, but the other way around";
    } else if (radiusSum < dist) {
        cout << "None of the conditions are true";
    } else if (radiusSum >= dist) {
        cout << "Circles intersect";
    }
}

void task11() {
    long double R, P, Q;
    cin >> R >> P >> Q;
    long double radians = Q * (3.141592 / 180);
    long double r = P * sin(radians) / 2;
    if (R <= r)
        cout << "YES";
    else
        cout << "NO";
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

void task14() {
    long double W, H, x1, y1, x2, y2, w, h;
    cin >> W >> H >> x1 >> y1 >> x2 >> y2 >> w >> h;
    long double baseTableWidth = fabs(x1 - x2),
                baseTableHeight = fabs(y1 - y2),
                rightDist = W - x2,
                leftDist = x2 - baseTableWidth,
                upperDist = H - y2,
                lowerDist = y2 - baseTableHeight,
                widthDiff = fabs(baseTableWidth - w),
                heightDiff = fabs(baseTableHeight - h);
    if (W <= 0 || w <= 0 || H <= 0 || h <= 0 ||x1 < 0 ||
        x2 < 0 || y1 < 0 || y2 < 0 || w > W || h > H) {
        cout << -1;
        return;
    }
    if (rightDist >= w || leftDist >= w ||
            upperDist >= h || lowerDist >= h) {
        cout << 0;
    } else if (rightDist + leftDist < w &&
               upperDist + lowerDist < h) {
        cout << -1;
    } else if ((widthDiff <= rightDist || widthDiff <= leftDist > 0) && widthDiff > 0) {
        cout << widthDiff;
    } else if ((heightDiff <= upperDist || heightDiff <= lowerDist) && heightDiff > 0) {
        cout << heightDiff;
    }
}

int main() {
    task8_3();
    return 0;
}
