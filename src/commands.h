#pragma once
#include "vector.h"
#include "string.h"

enum Commands{
    OPEN = 0,
    CLOSE,
    SAVE,
    SAVEAS,
    HELP,
    EXIT,

    PRINT,
    SELECT,
    SET,
    CHILDREN,
    CHILD,
    TEXT,
    DELETE,
    NEWCHILD,
    XPATH
};

const MyString commandString[] = {
    MyString::toMyString("open"),
    MyString::toMyString("close"),
    MyString::toMyString("save"),
    MyString::toMyString("saveas"),
    MyString::toMyString("help"),
    MyString::toMyString("exit"),

    MyString::toMyString("print"),
    MyString::toMyString("select"),
    MyString::toMyString("set"),
    MyString::toMyString("children"),
    MyString::toMyString("child"),
    MyString::toMyString("text"),
    MyString::toMyString("delete"),
    MyString::toMyString("newchild"),
    MyString::toMyString("xpath")
};