#include <iostream>
#include <vector>
#include <string>

struct MatrixElement {
    private: 
        double value;
        int row, column;
    public:
        MatrixElement(double value, int row, int column) {
            this->value = value;
            this->row = row;
            this->column = column;
        }

        double getValue() {
            return value;
        }

        int getRow() {
            return row;
        }

        int getColumn() {
            return column;
        }

        std::string toString() {
            return "{value: " + std::to_string(this->getValue()) +
                ", row: " + std::to_string(this->getRow()) +
                ", column: " + std::to_string(this->getColumn()) + "}";
        }
};


std::vector<MatrixElement> getPositions(double** matrix, int rows, int columns) {
    std::vector<MatrixElement> picked;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] == 0) {
                picked.push_back(MatrixElement(matrix[i][j], i, j));
            }
        }
    }
    return picked;
}

template<typename T>
void printMatrix(T* matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%7.2f", matrix[i][j]);
        }
        std::cout << "\n";
    }
}

void reverseArray(double* arr, int n) {
    for (int i = 0; i < n / 2; i++) {
        double temp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }
}

void reverseMatrix(double** matrix, int rows, int columns) {
    for (int i = 0; i < rows / 2; i++) {
        double* temp = matrix[i];
        matrix[i] = matrix[rows - i - 1];
        matrix[rows - i - 1] = temp;
    }
    for (int i = 0; i < rows; i++) {
        reverseArray(matrix[i], columns);
    }
}

const int ROWS = 2,
          COLUMNS = 4;
int main() {
    double** matrix = new double* [ROWS];
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = new double[COLUMNS];
    }
    std::vector<double> elements = { 1, 2, 0, 4, 5, 0, 7, 8, 9 };
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            matrix[i][j] = elements.back();
            elements.pop_back();
        }
    }
    std::vector<MatrixElement> picked = getPositions(matrix, ROWS, COLUMNS);
    for (MatrixElement el : picked) {
        std::cout << el.toString() << "\n";
    }
    printMatrix(matrix, ROWS, COLUMNS);
    std::cout << "\n";
    reverseMatrix(matrix, ROWS, COLUMNS);
    printMatrix(matrix, ROWS, COLUMNS);
    return 0;
}