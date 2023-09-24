#include <iostream>
#include "MyClass.h"

TwoDimensionalArray::TwoDimensionalArray(int row, int col) {
    rows = row;
    cols = col;
    array = new int* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        array[i] = new int[this->cols];
    }
}

TwoDimensionalArray::~TwoDimensionalArray() {
    for (int i = 0; i < rows; i++) {
        delete[] array[i];
    }
    delete[] array;
}

TwoDimensionalArray TwoDimensionalArray::operator&(const TwoDimensionalArray& other) {
    TwoDimensionalArray result(rows,cols);

    result.array = new int* [rows];
    for (int i = 0; i < rows; i++) {
        result.array[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            result.array[i][j] = array[i][j] & other.array[i][j];
        }
    }

    return result;
}

TwoDimensionalArray TwoDimensionalArray::operator+(const TwoDimensionalArray& other) {
    TwoDimensionalArray result(rows, cols);

    result.array = new int* [rows];
    for (int i = 0; i < rows; i++) {
        result.array[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            result.array[i][j] = array[i][j] + other.array[i][j];
        }
    }

    return result;
}

void TwoDimensionalArray::ArrayCreate() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << "array[" << i << "][" << j << "]: ";
            while (!(std::cin >> array[i][j])) {
                std::cout << "Invalid input. Please enter again: " << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
}

void TwoDimensionalArray::print() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void TwoDimensionalArray::nullifyRowAndColumnWithMinElement() {
    int minElement = array[0][0];
    int minElementRow = 0;
    int minElementCol = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (array[i][j] < minElement) {
                minElement = array[i][j];
                minElementRow = i;
                minElementCol = j;
            }
        }
    }

    for (int j = 0; j < cols; j++) {
        array[minElementRow][j] = 0;
    }

    for (int i = 0; i < rows; i++) {
        array[i][minElementCol] = 0;
    }
}

void TwoDimensionalArray::swapFirstOddWithFirstElementInEachRow() {
    for (int i = 0; i < rows; i++) {
        int firstOdd = -1;
        int firstElement = array[i][0];
        int index = -1;

        for (int j = 0; j < cols; j++) {
            if (array[i][j] % 2 != 0) {
                index = j;
                firstOdd = array[i][j];
                break;
            }
        }

        if (firstOdd != -1) {
            array[i][0] = firstOdd;
            array[i][index] = firstElement;
        }
    }
}


int CountRows() {
    std::cout << "Print count rows array:" << std::endl;
    int rows;
    while (!(std::cin >> rows) || rows <= 0) {
        std::cout << "Count rows should be a positive number. Please enter again: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return rows;
}

int CountCols() {
    std::cout << "Print count cols array:" << std::endl;
    int cols;
    while (!(std::cin >> cols) || cols <= 0) {
        std::cout << "Count cols should be a positive number. Please enter again: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }   
    return cols;
}