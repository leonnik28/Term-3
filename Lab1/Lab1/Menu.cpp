#include <iostream>
#include <cstring>
#include "MyClass.h"
#include "StringClass.h"
#include "Menu.h"

void menu() {
    int choice = 0;
    while (choice != 3) {
        std::cout << "Which class will we work with (1 - string, 2 - main, 3 - exit)";
        while (!(std::cin >> choice) || (choice < 1 && choice > 3)) {
            std::cout << "Invalid input. Please enter again: " << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1: {
            String stringFirst;
            stringFirst.input();
            String stringSecond;
            stringSecond.input();
            std::cout << "Operation: + ";
            String result = stringFirst + stringSecond;
            result.print();

            std::cout << "Enter the index to display: ";
            int index;
            while (!(std::cin >> index) || (index < 0 && index >= result.lengths())) {
                std::cout << "Invalid input. Please enter again: " << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cout << "Character at position " << index << " " << stringFirst[index] << std::endl;

            std::cout << "Enter the start: ";
            int start, end;
            std::cin >> start;
            std::cout << "Enter the end: ";
            std::cin >> end;
            result(start, end).print();

            break;
        }
        case 2: {
            WorkMainClass();
            break;
        }
        default:
            break;
        }
    }
}

void WorkMainClass() {
    int rows = CountRows();
    int cols = CountCols();

    TwoDimensionalArray arrayFirst(rows, cols);
    TwoDimensionalArray arraySecond(rows, cols);

    arrayFirst.ArrayCreate();

    int answer;

    std::cout << "Let's turn on the work of the first lab? (1 - yes, other - no) ";
    while (!(std::cin >> answer) || (answer != 1 && answer != 0)) {
        std::cout << "Invalid input. Please enter again: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if(answer == 1)
    WorkLaba1(arrayFirst);

    arraySecond.ArrayCreate();

    TwoDimensionalArray resultFirst = arrayFirst & arraySecond;
    resultFirst.print();

    TwoDimensionalArray resultSecond = arrayFirst + arraySecond;
    resultSecond.print();

}

void WorkLaba1(TwoDimensionalArray& array) {
    array.print();

    int answer;

    std::cout << "Do you want to swap elements in the array? (1 - yes, other - no) ";
    while (!(std::cin >> answer) || (answer != 1 && answer != 0)) {
        std::cout << "Invalid input. Please enter again: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (answer == 1) {
        array.nullifyRowAndColumnWithMinElement();
        array.print();
        answer = 0;
    }

    std::cout << "Do you want to swap elements in the array? (1 - yes, other - no) ";
    while (!(std::cin >> answer) || (answer != 1 && answer != 0)) {
        std::cout << "Invalid input. Please enter again: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (answer == 1) {
        array.swapFirstOddWithFirstElementInEachRow();
        array.print();
        answer = 0;
    }
}
