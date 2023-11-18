#include "pch.h"

double findMult(int arr[], int low, int high) {
    if (low == high) {
        return arr[low] / (1.0 + low);
    }
    else {
        int mid = (low + high) / 2;
        return findMult(arr, low, mid) + findMult(arr, mid + 1, high);
    }
}

extern "C" __declspec(dllexport) double sum(int arr[], int low, int high) {
    if (low == high) {
        return arr[low] / (1.0 + low);
    }
    int mid = (low + high) / 2;
    return findMult(arr, low, mid) + findMult(arr, mid + 1, high);
}