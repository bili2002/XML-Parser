#pragma once
#include <iostream>
#include "vector.h"
#include "string.h"
#include "element.h"

class Attribute {
public:
    MyString key;
    MyString value;

public:
    bool operator==(const Attribute& oth) const;    //checks if 2 attributes have the same key and value
    void print(std::ostream& os) const;             //prints the attribute in the right format (key="value")
};