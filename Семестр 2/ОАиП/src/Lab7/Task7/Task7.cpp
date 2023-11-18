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
    setlocale(0, "");
    begin:
    std::cout << "Укажите действие: 1 - показать условие, 2 - показать алгоритм, 3 - начать ввод данных, 4 - завершить\n";
    int action;
    std::cin >> action;
    while (!0) {
        if (action == 1) {
            std::cout << "Брюс недавно получил работу в NEERC (Numeric Expression Engineering &"
                "Research Center), где изучают и строят много различных любопытных чисел.Его"
                "первым заданием стало исследование двудесятичных чисел.Натуральное число"
                "называется двудесятичным, если его десятичное представление является"
                "суффиксом его двоичного представления; и двоичное и десятичное"
                "представление рассматривается без ведущих нулей.Например, 1010 = 10102, так"
                "что 10 двудесятичное число.Числа 101010 = 11111100102 и 4210 = 1010102 не"
                "являются двудесятичными.Сначала Брюс хочет создать список двудесятичных"
                "чисел.Помогите ему найти n - ое наименьшее двудесятичное число.\n";
            goto begin;
        }
        else if (action == 2) {
            std::cout << "Алгоритм: сложный\n";
            goto begin;
        }
        else if (action == 3) {
        input:
            int n;
            std::cin >> n;
            bfs(n);
            std::cout << "Продолжить ввод? 1 - да, 0 - нет\n";
            int temp;
            std::cin >> n;
            if (n) {
                goto input;
            }
            else {
                goto begin;
            }
        }
        else if (action == 4) {
            return 0;
        }
    }
    return 0;
}