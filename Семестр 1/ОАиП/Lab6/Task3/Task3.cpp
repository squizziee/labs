#include <iostream>

void sort(char str[], int n) {
    for (int i = 0; i < n; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n - 1; j++) {
            if (str[j] < str[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            char temp = str[i];
            str[i] = str[minIndex];
            str[minIndex] = temp;
        }
    }
}

bool compareArrays(char str1[], char str2[], int n1, int n2) {
    if (n1 != n2) {
        return false;
    }
    for (int i = 0; i < n1; i++) {
        if (str1[i] != str2[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    char str1[] = "book";
    char str2[] = "koob";
    sort(str1, sizeof(str1));
    sort(str2, sizeof(str2));
    std::cout << compareArrays(str1, str2, sizeof(str1), sizeof(str2));
}