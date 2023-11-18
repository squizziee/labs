#include <iostream>
#include <vector>

bool contains(char toFind, std::vector<char> elements) {
    for (char el : elements) {
        if (el == toFind)
            return true;
    }
    return false;
}

int main() {
    std::vector<char> braces = { '[', ']', '{', '}', '(', ')' };
    char str[] = "bitches be crazy(((((((";
    int count = 0;
    for (char c : str) {
        if (contains(c, braces)) {
            count++;
        }
    }
    std::cout << count;
}