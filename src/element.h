#pragma once
#include "attribute.h"
#include "pointer.h"

class Element {
    public:
    //
    static MyPointer<Element> root;

    MyString tag;
    MyString id;
    MyVector<Attribute> attributes;
    MyString text;

    MyVector<MyPointer<Element>> children;
    Element* parent;

    MyVector<Element*> operator/(const MyString& str);      //returns a list of all
    bool operator==(const Attribute& attribute);

    void print(std::ostream& os, int spacing) const;
    void printChildren(std::ostream& os, int spacing) const;
    void printAttributes(std::ostream& os) const;
    Element* findElement(const MyString& id);
    int findAttributeIndex(const MyString& attributeKey);

    static Attribute* findAttribute(const MyString& id, const MyString& attributeKey);

public:
    static void print(std::ostream& os);
    static void printAttributeValue(std::ostream& os, const MyString& id, const MyString& attributeKey);
    static void setAttributeValue(const MyString& id, const MyString& attributeKey, const MyString& attributeValue);
    static void printChildren(std::ostream& os, const MyString& id);
    static void printChild(std::ostream& os, const MyString& id, int n);
    static void printText(std::ostream& os, const MyString& id);
    static void deleteAttribute(const MyString& id, const MyString& attributeKey);
    static void addChild(const MyString& id);
    static void xpath(const MyString& id, MyString);
};