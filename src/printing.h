#include <iostream>
#include "string.h"

class Print {
public:
    static void printSpaces(std::ostream& os, int spacing);
    static void beginKey(std::ostream& os, const MyString& key);
    static void endTag(std::ostream& os, const MyString& key);
};