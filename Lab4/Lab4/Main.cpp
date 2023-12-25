#include <iostream>
#include "Stack.h"

int main() {
    Stack<int> stack;

    for (int i = 0; i < 10; ++i) {
        stack.push(i);
    }

    for (auto it = stack.begin(); it != stack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    auto search_it = search(stack.begin(), stack.end(), 5);
    if (search_it != stack.end()) {
        std::cout << "Item found: " << *search_it << std::endl;
    }
    else {
        std::cout << "Item not found" << std::endl;
    }

    return 0;
}