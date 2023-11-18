#include <iostream>
#include <Windows.h>
#include "../../Task1/task1.h"

/*bool binarySearch(int arr[], int n, int el) {
    int low = 0;
    int high = n - 1;
    int mid;
    while (low <= high) {
        mid = (high + low) / 2;
        if (el < arr[mid]) {
            high = mid - 1;
        }
        else if (el > arr[mid]) {
            low = mid + 1;
        }
        else {
            return true;
        }
    }
    return false;
}*/

void task2() {
    HINSTANCE load;
    load = LoadLibrary(L"Task2.dll");
    typedef double (*sum)(int arr[], int, int);
    sum func = (sum)GetProcAddress(load, "sum");
    int arr[] = { 9 };
    std::cout << func(arr, 0, 0);
    FreeLibrary(load);
}

int main() {
    task2(); 
    deployTask1();
    return 0;
}