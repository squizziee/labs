#include <iostream>
#include <cmath>
using namespace std;

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

int main() {
    task8_1();
    return 0;
}