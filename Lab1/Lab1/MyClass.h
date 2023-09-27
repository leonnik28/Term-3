#ifndef MAINCLASS
#define MAINCLASS

class TwoDimensionalArray {
private:
    int** array;
    int rows;
    int cols;

public:
    TwoDimensionalArray(int row, int col);
    ~TwoDimensionalArray();
    TwoDimensionalArray operator&(const TwoDimensionalArray& other);
    TwoDimensionalArray operator+(const TwoDimensionalArray& other);
    void ArrayCreate();
    void print();
    void print(int row, int col);
    void nullifyRowAndColumnWithMinElement();
    void swapFirstOddWithFirstElementInEachRow();
};

int CountRows();
int CountCols();
#endif