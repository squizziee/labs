#include <iostream>
#include "descriptions.h"

void descriptions::task1() {
    std::cout << "Algorithm: sorting an array, then figuring out\n";
    std::cout << "if there are multiple max or min elements, then\n";
    std::cout << "calculating right and left offset, and finally\n";
    std::cout << "putting remaining elements into new array\n\n";
}

void descriptions::task2() {
    std::cout << "Algorithm: let`s say that matrix has m columns\n";
    std::cout << "and n rows. Take i < n and j < m. If j > i, then\n";
    std::cout << "the element is above main diagonal. Then find\n";
    std::cout << "the smallest value amongst elements above the\n";
    std::cout << "main diagonal\n\n";
}

void descriptions::task3() {
    std::cout << "Algorithm: do all possible row multiplications\n";
    std::cout << "and row squares (two \"for\" cycles). If requirements\n";
    std::cout << "aren`t satisfied, terminate the program\n\n";
}

void descriptions::task9() {
    std::cout << "Algorithm: count sum of elements of indexes [i][i][i],\n";
    std::cout << "[i][n - i - 1][i], [i][n - i - 1][n - i - 1], [i][i][n - i - 1], \n";
    std::cout << "then put `em into array, sort, and output the last value\n\n";
}

void descriptions::task11() {
    std::cout << "Reading a matrix of '*' and '.' symbols, then parsing it: \n";
    std::cout << "if the symbol is '.', count '*' symbols around it and put the\n";
    std::cout << " number instead of '.' symbol. If the number is 0, then nothing changes\n\n";
}

void descriptions::task13() {
    std::cout << "Algorithm: integer input number n, then creating magic square\n";
    std::cout << "of n * n size. Three cases: singly even, doubly even, odd.\n";
    std::cout << "calculating using three different theorems, one for each case\n\n";
}