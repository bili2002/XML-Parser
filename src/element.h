#pragma once
#include "attribute.h"
#include "pointer.h"

class Element {
    static MyPointer<Element> root;

    MyString key;
    MyString id;
    MyVector<Attribute> attributes;
    MyString text;

    MyVector<MyPointer<Element>> children;
    MyPointer<Element> parent;

    MyVector<Element*> operator/(const MyString& str);      //returns a list of all
    bool operator==(const Attribute& atr);

    void printItself();
    void printAttributes();
    void printAll(int spac);
    Element* findElementWithID(const MyString& id);
    MyString& findAttributeWithKey(const MyString& attributeKey);

public:
    static void print();
    static void printAttributeValue(const MyString& id, const MyString& attributeKey);
    static void setAttributeValue(const MyString& id, const MyString& attributeKey, const MyString& attributeValue);
    static void printChildren(const MyString& id);
    static void printChild(const MyString& id, int n);
    static void printText(const MyString& id);
    static void deleteAttribute(const MyString& id, const MyString& attributeKey);
    static void addChild(const MyString& id);
    static void xpath(const MyString& id, MyString);
};