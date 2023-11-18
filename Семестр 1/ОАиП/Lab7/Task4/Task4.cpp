#include <iostream>

std::string convertToRomanian(int number) {
    std::string result;
    int M = number / 1000;
    int MRemainder = number % 1000;
    int D = MRemainder / 500;
    int DRemainder = MRemainder % 500;
    int C = DRemainder / 100;
    int CRemainder = DRemainder % 100;

    bool nineHundred = 0;

    for (int i = 0; i < M; i++) {
        result.append("M");
    }
    if ((C == 4) && D) {
        result.append("CM");
        nineHundred = 1;
    }
    else if (D > 0) {
        result.append("D");
    }
    if (!nineHundred) {
        if (C == 4) {
            result.append("CD");
        }
        else {
            for (int i = 0; i < C; i++) {
                result.append("C");
            }
        }
    }
    int L = CRemainder / 50;
    int LRemainder = CRemainder % 50;
    int X = LRemainder / 10;
    int XRemainder = LRemainder % 10;

    bool ninety = 0;

    if (X == 4 && L) {
        result.append("XC");
        ninety = 1;
    }
    else if (L > 0) {
        result.append("L");
    }
    if (!ninety) {
        if (X == 4) {
            result.append("XL");
        }
        else {
            for (int i = 0; i < X; i++) {
                result.append("X");
            }
        }
    }

    int V = XRemainder / 5;
    int VRemainder = XRemainder % 5;
    int I = VRemainder % 5;

    bool nine = 0;

    if (I == 4 && V) {
        result.append("IX");
        nine = 1;
    }
    else if (V > 0){
        result.append("V");
    }
    if (!nine) {
        if (I == 4) {
            result.append("IV");
        }
        else {
            for (int i = 0; i < I; i++) {
                result.append("I");
            }
        }
    }
    return result;
}

int main() {
    int number;
    std::cin >> number;
    std::cout << convertToRomanian(number);
}