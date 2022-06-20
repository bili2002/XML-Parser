#pragma once
#include "attribute.h"
#include "pointer.h"

class Element {
    static MyPointer<Element> root; //the root of the tree

    MyString tag;
    MyString id;
    MyVector<MyPointer<Attribute>> attributes;
    MyString text;

    MyVector<MyPointer<Element>> children;
    Element* parent;
    
    Element();
    Element(const MyString& tag);
    void destruct();    //deconstructs the element and its children

    MyVector<Element*> operator/(const MyString& tag);      //returns a list of all children with a given tag
    bool hasAttribute(const Attribute& attribute);          //checks if an element has a given attribute

    void idCheck();                                             //checks if there is a dublicate id and fixes it
    void setId(const MyString& value);                          //sets a new id
    void readOpeningTag(std::istream& is);                      //reads the opening tag
    void readElement(std::istream& is);                         //reads the element information
    void print(std::ostream& os, int spacing) const;            //prints the element 
    void printChildren(std::ostream& os, int spacing) const;    //print the children of the element
    void printAttributes(std::ostream& os) const;               //prints the attributes of the element
    Element* findElement(const MyString& id);                   //finds an element with id
    int findAttributeIndex(const MyString& attributeKey);       //finds an attribute's index with a given key

    static Attribute* findAttribute(const MyString& id, const MyString& attributeKey);  //finds attribute's index with a given id and key

    static bool isLetter(char ch);  //checks if character is letter
    static bool isNumber(char ch);  //checks if character is number

public:
    static void destructTree();             //destructs the tree
    static void input(std::istream& is);    //reads the xml file
    static void print(std::ostream& os);    //prints the xml file
    static void printAttributeValue(std::ostream& os, const MyString& id, const MyString& attributeKey);             //prints the value of an atribute
    static void setAttributeValue(const MyString& id, const MyString& attributeKey, const MyString& attributeValue); //changes the value of an atribute
    static void printChildren(std::ostream& os, const MyString& id);                //prints the children to an element
    static void printChild(std::ostream& os, const MyString& id, int n);            //prints a child to an element 
    static void printText(std::ostream& os, const MyString& id);                    //prints the text of an element
    static void deleteAttribute(const MyString& id, const MyString& attributeKey);  //deletes a given attribute
    static void addChild(const MyString& id, const MyString& tag);                  //adds a child
    static void xpath(std::ostream& os, const MyString& path);                      //xpath
};