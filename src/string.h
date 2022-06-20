#pragma once
#include <iostream>
#include <cstring>

#include "vector.h"

using MyString = MyVector<char>;

MyString toMyString(const char str[]);
MyString toRealString(const char str[]);
std::istream& operator>>(std::istream& in, MyString& str);
std::ostream& operator<<(std::ostream& out, const MyString& str);
