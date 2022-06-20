#include "string.h"


std::istream& operator>>(std::istream& in, MyString& str) {
    str.clear();
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

std::ostream& operator<<(std::ostream& out, const MyString& str) {
    for (auto ch : str) {
        out<<ch;
    }

    return out;
}

