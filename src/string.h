#pragma once
#include <iostream>
#include <cstring>

#include "vector.h"
#include "pointer.h"

class MyString: public MyVector<char> {
public:
    static MyString toMyString(const char str[])  {
        MyString temp;
        for (size_t i=0; i<strlen(str); i++) {
            temp.push_back(str[i]);
        }
        return temp;
    }

    void toRealStringIn(char*& temp) const {
        if (temp != nullptr) {
            delete[] temp;
        }

        temp = new char[currSize+1];
        for (size_t i=0; i<currSize; i++) {
            temp[i] = arr[i];
        }
        temp[currSize] = '\0';
    }

    bool operator==(char* ch) const {
        if (strlen(ch) != currSize) {
            return false;
        }

        for (size_t i=0; i<strlen(ch); i++) {
            if (ch[i] != arr[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator==(const MyVector& oth) const {
        if (currSize != oth.size()) {
            return false;
        }

        for (size_t i=0; i<currSize; i++) {
            if (arr[i] != oth[i]) {
                return false;
            }
        }
        return true;
    }

    void operator+=(char ch) {
        push_back(ch);
    }

    void operator+=(char* ch) {
        for (size_t i=0; i<strlen(ch); i++) {
            push_back(ch[i]);
        }
    }

    friend std::istream& operator>>(std::istream& in, MyString& str);
    friend std::ostream& operator<<(std::ostream& out, const MyString& str);
};
