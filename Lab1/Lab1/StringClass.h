#ifndef STRINGCLASS
#define STRINGCLASS

class String {
private:
    char* str;
    int length;

public:
    String();
    String(const char* s);
    ~String();
    String(const String& other);
    String& operator=(const String& other);
    String operator+(const String& other);
    bool operator==(const String& other);
    bool operator!=(const String& other);
    char& operator[](int index);
    String operator()(int start, int end);
    void input();
    void print();
    int lengths();
};
#endif