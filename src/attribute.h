#pragma once
#include <iostream>
#include "vector.h"
#include "string.h"

class Attribute {
    public:
    //
    MyString key;
    MyString value;

public:
    bool operator==(const Attribute& oth) const;
    void print(std::ostream& os) const;
};