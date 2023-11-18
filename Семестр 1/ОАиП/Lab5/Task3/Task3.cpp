#include <iostream>
#include <vector>

template <int rows, int cols>
std::vector<int> createVector(int (& matrix)[rows][cols]) {
    std::vector<int> ans;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == j && matrix[i][j] % 2 == 0) {
                ans.push_back(matrix[i][j]);
            }
        }
    }
    return ans;
}

void printVector(std::vector<int> vect) {
    for (int el : vect) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

int multOfElements(std::vector<int> vect) {
    if (vect.empty()) {
        return 0;
    }
    int mult = 1;
    for (int el : vect) {
        mult *= el;
    }
    return mult;
}