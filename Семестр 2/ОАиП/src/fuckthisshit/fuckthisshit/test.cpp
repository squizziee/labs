#include "pch.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"
#include <vector>

TEST(task3test, multTest1) {
    std::vector<int> v = { 1, 10, 5 };
    EXPECT_EQ(multOfElements(v), 50);
}

TEST(task3test, multTest2) {
    std::vector<int> v = { 2, 15, 45, 90 };
    EXPECT_EQ(multOfElements(v), 121500);
}

TEST(task3test, multTest3) {
    std::vector<int> v = { 1, 0, 10000 };
    EXPECT_EQ(multOfElements(v), 0);
}

TEST(task3test, multTest4) {
    std::vector<int> v = {};
    EXPECT_EQ(multOfElements(v), 0);
}

TEST(task3test, vectTest1) {
    int** arr = new int* [3];
    for (int i = 0; i < 3; i++) {
        arr[i] = new int[3];
    }
    std::vector<int> elements = { 0, 8, 7, 6, 2, 4, 3, 2, 1 };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            arr[i][j] = elements.back();
            elements.pop_back();
        }
    }
    std::vector<int> v = createVector(arr, 3, 3);
    std::vector<int> expected = {2, 0};
    EXPECT_EQ(v, expected);
}

TEST(task3test, vectTest2) {
    int** arr = new int* [3];
    for (int i = 0; i < 3; i++) {
        arr[i] = new int[3];
    }
    std::vector<int> elements = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            arr[i][j] = elements.back();
            elements.pop_back();
        }
    }
    std::vector<int> v = createVector(arr, 3, 3);
    std::vector<int> expected = {};
    EXPECT_EQ(v, expected);
}

TEST(task3test, vectTest3) {
    int** arr = new int* [3];
    for (int i = 0; i < 3; i++) {
        arr[i] = new int[4];
    }
    std::vector<int> elements = { 45, 8, 8, 7, 10, 6, 2, 4, 5, 3, 2, 6 };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            arr[i][j] = elements.back();
            elements.pop_back();
        }
    }
    std::vector<int> v = createVector(arr, 3, 4);
    std::vector<int> expected = { 6, 2, 8 };
    EXPECT_EQ(v, expected);
}

long long hash(double** arr, int n, int m) {
    long long temp = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            temp += ((long long) arr[i][j]) << 5;
        }       
    }
    return temp;
}

TEST(task4test, reverseTest1) {
    int n = 3, m = 4;
    double **arr = new double* [n];
    double** expected = new double* [n];
    for (int i = 0; i < n; i++) {
        arr[i] = new double[m];
        expected[i] = new double[m];
    }
    std::vector<double> elements = { 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    std::vector<double> elementsExpected = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i][j] = elements.back();
            elements.pop_back();
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            expected[i][j] = elementsExpected.back();
            elementsExpected.pop_back();
        }
    }
    reverseMatrix(arr, n, m);
    EXPECT_EQ(hash(arr, n, m), hash(expected, n, m));
}

TEST(task4test, reverseTest2) {
    int n = 1, m = 1;
    double** arr = new double* [n];
    double** expected = new double* [n];
    for (int i = 0; i < n; i++) {
        arr[i] = new double[m];
        expected[i] = new double[m];
    }
    std::vector<double> elements = { 1 };
    std::vector<double> elementsExpected = { 1 };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i][j] = elements.back();
            elements.pop_back();
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            expected[i][j] = elementsExpected.back();
            elementsExpected.pop_back();
        }
    }
    reverseMatrix(arr, n, m);
    EXPECT_EQ(hash(arr, n, m), hash(expected, n, m));
}

TEST(task4test, reverseTest3) {
    int n = 0, m = 0;
    double** arr = new double* [n];
    double** expected = new double* [n];
    for (int i = 0; i < n; i++) {
        arr[i] = new double[m];
        expected[i] = new double[m];
    }
    std::vector<double> elements = {};
    std::vector<double> elementsExpected = {};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i][j] = elements.back();
            elements.pop_back();
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            expected[i][j] = elementsExpected.back();
            elementsExpected.pop_back();
        }
    }
    reverseMatrix(arr, n, m);
    EXPECT_EQ(hash(arr, n, m), hash(expected, n, m));
}

TEST(task5test, valueTest1) {
    std::vector<double> elements = { 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    double val = countAverageValue(elements);
    EXPECT_DOUBLE_EQ(val, 6.5);
}

TEST(task5test, valueTest2) {
    std::vector<double> elements = { 1, 0.1, 0.2 };
    double val = countAverageValue(elements);
    EXPECT_DOUBLE_EQ(val, (1 + 0.2 + 0.1) / 3);
}

TEST(task5test, valueTest3) {
    std::vector<double> elements = {};
    double val = countAverageValue(elements);
    EXPECT_DOUBLE_EQ(val, 0);
}