#include <iostream>

template<typename T>
class Stack {
    struct Node {
        T data;
        Node* next;
    };

    Node* top;
    int size;

public:
    Stack() : top(nullptr), size(0) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(T value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = top;
        top = newNode;
        size++;
    }

    void pop() {
        if (!isEmpty()) {
            Node* tempNode = top;
            top = top->next;
            delete tempNode;
            size--;
        }
    }

    T peek() {
        if (!isEmpty()) {
            return top->data;
        }
        return T();
    }

    bool isEmpty() {
        return top == nullptr;
    }

    int getSize() {
        return size;
    }

    bool contains(T value) {
        Node* tempNode = top;
        while (tempNode) {
            if (tempNode->data == value) {
                return true;
            }
            tempNode = tempNode->next;
        }
        return false;
    }

    void print() {
        Node* tempNode = top;
        while (tempNode) {
            std::cout << tempNode->data << " ";
            tempNode = tempNode->next;
        }
        std::cout << std::endl;
    }
};