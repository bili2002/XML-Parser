#pragma once
#include "attribute.h"
#include "pointer.h"

class Element {
    public:
    //
    static MyPointer<Element> root;

    MyString tag;
    MyString id;
    MyVector<MyPointer<Attribute>> attributes;
    MyString text;

    MyVector<MyPointer<Element>> children;
    Element* parent;
    
    Element();
    Element(const MyString& tag);

    MyVector<Element*> operator/(const MyString& str);      //returns a list of all
    bool hasAttribute(const Attribute& attribute);

    void idCheck();
    void setId(const MyString& value);
    void readOpeningTag(std::istream& is);
    void readElement(std::istream& is);
    void print(std::ostream& os, int spacing) const;
    void printChildren(std::ostream& os, int spacing) const;
    void printAttributes(std::ostream& os) const;
    Element* findElement(const MyString& id);
    int findAttributeIndex(const MyString& attributeKey);

    static Attribute* findAttribute(const MyString& id, const MyString& attributeKey);

    static bool isLetter(char ch);
    static bool isNumber(char ch);

public:
    static void input(std::istream& is);
    static void print(std::ostream& os);
    static void printAttributeValue(std::ostream& os, const MyString& id, const MyString& attributeKey);
    static void setAttributeValue(const MyString& id, const MyString& attributeKey, const MyString& attributeValue);
    static void printChildren(std::ostream& os, const MyString& id);
    static void printChild(std::ostream& os, const MyString& id, int n);
    static void printText(std::ostream& os, const MyString& id);
    static void deleteAttribute(const MyString& id, const MyString& attributeKey);
    static void addChild(const MyString& id, const MyString& tag);
    static void xpath(std::ostream& os, const MyString& path);
};