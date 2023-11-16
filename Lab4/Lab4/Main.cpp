#include "Stack.h"
#include <iostream>
#include <limits>

int main() {
    Stack<int> stack;

    while (true) {
        std::cout << "Stack Menu:\n";
        std::cout << "1. Push an element\n";
        std::cout << "2. Pop an element\n";
        std::cout << "3. Get the top element\n";
        std::cout << "4. Get the size of the stack\n";
        std::cout << "5. Print the stack\n";
        std::cout << "6. Check if the stack is empty\n";
        std::cout << "7. Check if a value is in the stack\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nInvalid input. Please enter a number.\n";
        }

        switch (choice) {
        case 1: {
            int element;
            std::cout << "\nEnter the element to push: ";
            while (!(std::cin >> element)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\nInvalid input. Please enter a number.\n";
            }
            stack.push(element);
            std::cout << "\n";
            break;
        }
        case 2: {
            if (!stack.isEmpty()) {
                stack.pop();
                std::cout << "\nElement popped.\n";
            }
            else {
                std::cout << "\nStack is empty. Cannot pop.\n";
            }
            break;
        }
        case 3: {
            if (!stack.isEmpty()) {
                int top = stack.peek();
                std::cout << "\nTop element: " << top << "\n" << std::endl;
            }
            else {
                std::cout << "\nStack is empty.\n";
            }
            break;
        }
        case 4: {
            std::cout << "\nStack size: " << stack.getSize() << std::endl;
            break;
        }
        case 5: {
            std::cout << "\nStack contents: ";
            stack.print();
            std::cout << "\n";
            break;
        }
        case 6: {
            if (stack.isEmpty()) {
                std::cout << "\nThe stack is empty.\n";
            }
            else {
                std::cout << "\nThe stack is not empty.\n";
            }
            break;
        }
        case 7: {
            int value;
            std::cout << "\nEnter the value to check: ";
            while (!(std::cin >> value)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\nInvalid input. Please enter a number.\n";
            }
            if (stack.contains(value)) {
                std::cout << "\nThe stack contains " << value << ".\n";
            }
            else {
                std::cout << "\nThe stack does not contain " << value << ".\n";
            }
            break;
        }
        case 8: {
            std::cout << "\nExiting the program.\n";
            return 0;
        }
        default: {
            std::cout << "\nInvalid choice. Please enter a valid option.\n";
            break;
        }
        }
    }

    return 0;
}
