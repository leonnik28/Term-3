#include <iostream>
#include <cstring>
#include "StringClass.h"

String::String() {
    length = 0;
    str = nullptr;
}

String::String(const char* s) {
    length = strlen(s);
    str = new char[length + 1];
    strcpy(str, s);
}

String::~String() {
    delete[] str;
}

String::String(const String& other) {
    length = other.length;
    str = new char[length + 1];
    strcpy(str, other.str);
}

String& String::operator=(const String& other) {
    if (this == &other)
        return *this;

    delete[] str;

    length = other.length;
    str = new char[length + 1];
    strcpy(str, other.str);

    return *this;
}

String String::operator+(const String& other) {
    int newLength = length + other.length;
    char* newStr = new char[newLength + 1];
    strcpy(newStr, str);
    strcat(newStr, other.str);

    String result(newStr);
    delete[] newStr;

    return result;
}

bool String::operator==(const String& other) {
    return strcmp(str, other.str) == 0;
}

bool String::operator!=(const String& other) {
    return strcmp(str, other.str) != 0;
}

char& String::operator[](int index) {
    return str[index];
}

String String::operator()(int start, int end) {
    int newLength = end - start + 1;
    char* newStr = new char[newLength + 1];
    strncpy(newStr, str + start, newLength);
    newStr[newLength] = '\0';

    String result(newStr);
    delete[] newStr;
    return result;
}

int String::lengths() {
    return this->length;
}

void String::input() {
    const int BUFFER_SIZE = 100;
    char buffer[BUFFER_SIZE];
    std::cout << "Input string: ";
    std::cin.getline(buffer, BUFFER_SIZE);
    length = strlen(buffer);
    str = new char[length + 1];
    strcpy(str, buffer);
}

void String::print() {
    std::cout << str << std::endl;
}