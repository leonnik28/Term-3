#include <iostream>

class TwoDimensionalArray {
private:
    int** array;
    int rows;
    int cols;

public:
    TwoDimensionalArray() {
        int rows, cols;
        std::cout << "Print count rows array:" << std::endl;
        std::cin >> rows;
        std::cout << "Print count cols array:" << std::endl;
        std::cin >> cols;

        this->rows = rows;
        this->cols = cols;

        array = new int* [rows];
        for (int i = 0; i < rows; i++) {
            array[i] = new int[cols];
        }
    }

    ~TwoDimensionalArray() {
        for (int i = 0; i < rows; i++) {
            delete[] array[i];
        }
        delete[] array;
    }

    void ArrayCreate() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << "array[" << i << "][" << j << "]: ";
                std::cin >> array[i][j];
            }
        }
    }

    int* operator[](int index) {
        return array[index];
    }

    void print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << array[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void nullifyRowAndColumnWithMinElement() {
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

    void swapFirstOddWithFirstElementInEachRow() {
        for (int i = 0; i < rows; i++) {
            int firstOdd = -1;
            int firstElement = array[i][0];
            int index;

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
};

int main() {

    TwoDimensionalArray array;
    array.ArrayCreate();
    array.print();
    
    int answer;

    std::cout << "Do you want swap element in array? (1 - yes, other - no) ";
    std::cin >> answer;

    if (answer == 1) {
        array.nullifyRowAndColumnWithMinElement();
        answer = 0;
    }

    std::cout << "Do you want swap element in array? (1 - yes, other - no) ";
    std::cin >> answer;

    if(answer == 1) array.swapFirstOddWithFirstElementInEachRow();

    std::cout << std::endl << "Modified array:" << std::endl;
    array.print();

    return 0;
}