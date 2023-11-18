#include <iostream>
#include <vector>
#include <sstream>

template<typename A, typename B>
class Pair {
public:
    A a;
    B b;
    Pair(A a, B b) {
        this->a = a;
        this->b = b;
    }

    bool operator==(const Pair<A, B>& obj) const {
        return obj.a == a && obj.b == b;
    }

    std::string toString() {
        return std::to_string(a) + " " + std::to_string(b);
    }
};

Pair<int, int> getPair(int a, int b) {
    std::vector<int> list;
    while (true) {
        list.push_back(b);
        list.push_back(a);
        if (list[list.size() - 1] == 0) {
            break;
        }
        if (list[list.size() - 1] > list[list.size() - 2]) {
            break;
        }
        list.push_back(b - a);
        int temp = b - a;
        b = a;
        a = temp;
    }
    return Pair<int, int>(list[list.size() - 1], list[list.size() - 2]);
}

int compare(Pair<int, int> o1, Pair<int, int> o2) {
    if (o1.a + o1.b <
        o2.a + o2.b) {
        return -1;
    }
    if (o1.a + o1.b >
        o2.a + o2.b) {
        return 1;
    }
    else {
        if (o1.a <
            o2.a) {
            return -1;
        }
        else if (o1.a >
            o2.a) {
            return 1;
        }
        return 0;
    }
}

int main() {
    int a, b, N;
    std::cin >> N;
    a = 1;
    b = N - a;
    Pair<int, int> minPair = getPair(a, b);
    Pair<int, int> prevPair = getPair(a, b);
    while (b != (N + 1) / 2) {
        a++;
        b--;
        auto pair = getPair(a, b);
        if (pair.a + pair.b > prevPair.a + prevPair.b) {
            break;
        }
        if (compare(pair, minPair) == -1) {
            minPair.a = pair.a;
            minPair.b = pair.b;
        }
        prevPair = pair;
    }
    std::cout << minPair.toString();
    return 0;
}