#include <iostream>
#include <queue>

std::string runTask4(int number) {
    std::string result;
    int M = number / 1000;
    int MRemainder = number % 1000;
    int D = MRemainder / 500;
    int DRemainder = MRemainder % 500;
    int C = DRemainder / 100;
    int CRemainder = DRemainder % 100;

    bool nineHundred = 0;

    for (int i = 0; i < M; i++) {
        result.append("M");
    }
    if ((C == 4) && D) {
        result.append("CM");
        nineHundred = 1;
    }
    else if (D > 0) {
        result.append("D");
    }
    if (!nineHundred) {
        if (C == 4) {
            result.append("CD");
        }
        else {
            for (int i = 0; i < C; i++) {
                result.append("C");
            }
        }
    }
    int L = CRemainder / 50;
    int LRemainder = CRemainder % 50;
    int X = LRemainder / 10;
    int XRemainder = LRemainder % 10;

    bool ninety = 0;

    if (X == 4 && L) {
        result.append("XC");
        ninety = 1;
    }
    else if (L > 0) {
        result.append("L");
    }
    if (!ninety) {
        if (X == 4) {
            result.append("XL");
        }
        else {
            for (int i = 0; i < X; i++) {
                result.append("X");
            }
        }
    }

    int V = XRemainder / 5;
    int VRemainder = XRemainder % 5;
    int I = VRemainder % 5;

    bool nine = 0;

    if (I == 4 && V) {
        result.append("IX");
        nine = 1;
    }
    else if (V > 0) {
        result.append("V");
    }
    if (!nine) {
        if (I == 4) {
            result.append("IV");
        }
        else {
            for (int i = 0; i < I; i++) {
                result.append("I");
            }
        }
    }
    return result;
}

int runTask5(int number) {
    return (number + 1) / 10;
}

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

void runTask7(int n) {
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

char getDigit(int remainder) {
    return remainder + 48;
}

void replaceAll(std::string& str, std::string toReplace, std::string replacement) {
    int occurence = str.find(toReplace);
    while (occurence != std::string::npos) {
        str.replace(occurence, 2, replacement);
        occurence = str.find(toReplace);
    }
}

std::string runTask8(long long n) {
    std::string ans;
    while (n >= 3) {
        ans.push_back(getDigit(n % 3));
        n /= 3;
    }
    ans.push_back(getDigit(n));
    reverse(ans.begin(), ans.end());
    replaceAll(ans, "10", "03");
    replaceAll(ans, "20", "13");
    replaceAll(ans, "30", "23");
    return (ans[0] == '0') ? ans.substr(1) : ans;
}