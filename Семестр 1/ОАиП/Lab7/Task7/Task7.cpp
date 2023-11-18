#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

const int N = 1e6 + 10;
int tmp[N];
int v[N];

inline bool check(std::string s) {
    int cnt = 0;
    for (int i = 0; i < s.size(); ++i) {
        v[i] = 0;
        tmp[i] = 0;
    }
    tmp[cnt++] = 1;
    for (int _i = 0; _i < s.size(); ++_i) {
        if (s[_i] == '1') {
            for (int i = _i; i <= cnt; ++i) {
                v[i] += tmp[i];
                if (v[i] >= 2) {
                    v[i + 1] += (v[i] >> 1);
                    v[i] = v[i] & 1;
                }
            }
        }
        if ((s[_i] - '0') != v[_i]) {
            return false;
        }
        for (int i = _i, now = 0; i < cnt; ++i) {
            now += tmp[i] * 10;
            tmp[i] = (now & 1);
            now >>= 1;
            if (i == cnt - 1 && now && cnt < s.size()) {
                cnt++;
            }
        }
    }
    return true;
}

void bfs(int n) {
    std::queue<std::string> que;
    std::vector<std::string> vc;
    que.push("0");
    que.push("1");
    std::string to;
    while (n > 0) {
        vc.clear();
        while (!que.empty()) {
            vc.push_back(que.front());
            que.pop();
        }
        for (std::string now : vc) {
            if (now[now.size() - 1] != '0') {
                n--;
            }
            if (n == 0) {
                std::reverse(now.begin(), now.end());
                std::cout << now << '\n';
            }
            to = now + '0';
            if (check(to)) {
                que.push(to);
            }
        }
        for (std::string now : vc) {
            to = now + '1';
            if (check(to)) {
                que.push(to);
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    bfs(n);
    return 0;
}