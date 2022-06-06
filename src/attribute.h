#pragma once
#include "vector.h"
#include "string.h"

class Attribute {
    MyString key;
    MyString value;

public:
    bool operator==(const Attribute& oth);
    void print();
};