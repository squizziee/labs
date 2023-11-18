#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define fore(i, l, r) for(int i = int(l); i < int(r); i++)
#define sz(a) int((a).size())

typedef long long li;

int n;
li x, y;
vector<li> a;

inline bool read() {
    if (!(cin >> n >> x >> y))
        return false;
    a.resize(n);
    fore(i, 0, n) {
        cin >> a[i];
    }
    return true;
}

li ceil(li a, li b) {
    return (a + b - 1) / b;
}

inline void solve() {
    sort(a.begin(), a.end());

    vector<li> t(n), b(n);
    fore(i, 0, n) {
        if (i > 0 && b[i - 1] >= a[i]) {
            t[i] = t[i - 1];
            b[i] = b[i - 1] + 1;
        }
        else {
            t[i] = a[i] - i;
            b[i] = a[i] + 1;
        }
    }

    li ans = 0;
    while (x < y) {
        int pos = int(upper_bound(t.begin(), t.end(), x) - t.begin());

        li p = pos, m = n - pos;
        if (x + p >= y) {
            cout << ans + (y - x) << endl;
            return;
        }
        if (p <= m) {
            cout << -1 << endl;
            return;
        }

        li k = ceil(y - x - p, p - m);
        if (pos < n) {
            k = min(k, ceil(t[pos] - x, p - m));
        }
        ans += k * n;
        x += k * (p - m);
    }
}

int main() {
    int t; cin >> t;
    while (t--) {
        read();
        solve();
    }
    return 0;
}