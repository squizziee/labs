#include <iostream>
#include <bitset>

void invert(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] ^= 1;
    }
}

int main() {
    const int SIZE = 8; 
    int num1[SIZE]{ 0, 1, 1, 0, 1, 1, 0, 1 }; //109
    int num2[SIZE]{ 0, 1, 0, 1, 0, 1, 0, 0 }; //84
    int sum[SIZE]{}; //193
    int carry = 0;
    //invert(num1, SIZE);
    //invert(num2, SIZE);
    for (int i = SIZE - 1; i >= 0; i--) {
        sum[i] = num1[i] ^ num2[i] ^ carry;
        carry = (num1[i] & num2[i]) | (num1[i] & carry) | (num2[i] & carry);
    }
    //invert(sum, SIZE);
    for (int i = 0; i < SIZE; i++) {
        std::cout << sum[i] << " ";
    }
}