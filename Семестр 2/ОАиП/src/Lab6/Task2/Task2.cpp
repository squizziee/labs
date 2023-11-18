#include <iostream>
#include <vector>

int main() {
    char str[] = "dungeon master ass slaves";
    std::vector<std::vector<char>> vect;
    std::vector<char> word;
    for (int i = 0; i < sizeof(str); i++) {
        if (str[i] == ' ') {
            vect.push_back(word);
            word.clear();
        }
        else if (i == sizeof(str) - 1) {
            vect.push_back(word);
            word.clear();
        }
        else {
            word.push_back(str[i]);
        }
    }
    for (std::vector<char> word : vect) {
        char begin = word.at(0);
        char end = word.at(word.size() - 1);
        if (begin == end) {
            for (char c : word) {
                std::cout << c;
            }
            std::cout << " ";
        }
    }
}