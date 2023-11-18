#include <iostream>
#include <vector>
#include "pch.h"

std::vector<int> createVector(int** matrix, int n, int m) {
    std::vector<int> ans;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
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
