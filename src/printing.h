#include <iostream>
#include "string.h"

class Print {
public:
    static void printSpaces(std::ostream& os, int spacing);
    static void endTag(std::ostream& os, const MyString& key);
};