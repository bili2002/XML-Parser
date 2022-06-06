#pragma once
#include "vector.h"
#include "string.h"

enum {
    OPEN = 0,
    CLOSE,
    SAVE,
    SAVEAS,
    HELP,
    EXIT
};

const MyVector<char> stringOfCommand[] = {
    toMyString("open"),
    toMyString("close"),
    toMyString("save"),
    toMyString("saveas"),
    toMyString("help"),
    toMyString("exit")
};