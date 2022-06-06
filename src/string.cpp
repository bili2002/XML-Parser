#include "string.h"

MyString toMyString(const char str[]) {
    MyString temp;
    for (size_t i=0; i<strlen(str); i++) {
        temp.push_back(i);
    }
    return temp;
}

std::istream& operator>>(std::istream& in, MyVector<char>& str) {
    char temp = ' ';

    while (isspace(temp) && in.good()) {
        in.get(temp);
    };

    while (!isspace(temp) && in.good()) {
        str.push_back(temp);
        in.get(temp);
    };

    return in;
}

std::ostream& operator<<(std::ostream& out, const MyVector<char>& str) {
    for (auto ch : str) {
        out<<ch;
    }

    return out;
}
