#include "fibonacci.h"
#include <iostream>

void fillInFibonacciNumbers(int* result, int length) {
    result[0] = 0;
    if (length == 1) {
        return;
    }

    result[1] = 1;

    for (int i = 2; i < length; i++) {
        result[i] = result[i-1]+result[i-2];
    }
}

void printArray(int* arr, int length) {
    for (int i = 0; i < length; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}

void createFibonacci() {
    std::cout << "How many numbers do you want generated? ";
    int length = 0;
    std::cin >> length;

    std::cout << '\n';

    int* result = new int[length];

    fillInFibonacciNumbers(result, length);

    printArray(result, length);

    delete[] result;
    result = nullptr;
}