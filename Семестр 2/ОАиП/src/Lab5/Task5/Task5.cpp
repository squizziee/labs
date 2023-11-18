#include <iostream>
#include <vector>

double countAverageValue(std::vector<int> vect) {
    int sum = 0;
    int count = 0;
    for (int el : vect) {
        sum += el;
        count++;
    }
    return ((double)sum) / ((double)count);
}

const int ROWS = 3;
const int COLUMNS = 3;
int main() {
    int** matrix = new int* [ROWS];
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = new int[COLUMNS];
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            std::cin >> matrix[i][j];
        }
    }
    std::vector<int> picked;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j+=2) {
            if (matrix[i][j] % 2 != 0) {
                picked.push_back(matrix[i][j]);
            }
        }
    }
    std::cout << countAverageValue(picked);
}