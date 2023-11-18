#include <iostream>
#include <queue>
#include "queue.cpp"

int main()
{
    custom::queue<int> a;
    custom::queue<int> b;
    b.push(1);
    b.push(2);
    b.push(3);
    b.push(4);
    b.push(5);
    b.push(6);
    b.remove_range(0, 3);
    while (!b.empty()) {
        std::cout << b.front() << " ";
        b.pop();
    }
}