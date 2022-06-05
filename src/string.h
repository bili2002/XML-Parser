#pragma once
#include <iostream>

#include "vector.h"

std::istream& operator>>(std::istream& in, MyVector<char>& str);
std::ostream& operator<<(std::ostream& out, const MyVector<char>& str);