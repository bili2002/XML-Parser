#include "element.h"
#include "printing.h"

MyPointer<Element> Element::root = new Element;

void Element::print(std::ostream& os, int spacing) const {
    Print::printSpaces(os, spacing);

    os<<'<'<<tag<<" id=\""<<id<<'\"';
    if (!attributes.empty()) {
        printAttributes(os);
    }
    os<<'>';

    if (!children.empty()) {
        os<<"\n";

        printChildren(os, spacing+1);
        if (!text.empty()) {
            Print::printSpaces(os, spacing+1);
            os<<text<<'\n';
        }
        
        Print::printSpaces(os, spacing);
    } else if (!text.empty()) {
        os<<text;
    }

    Print::endTag(os, tag);
}

void Element::printChildren(std::ostream& os, int spacing) const {
    for (const MyPointer<Element>& curr : children) {
        curr->print(os, spacing);
    }
} 

void Element::printAttributes(std::ostream& os) const {
    for (const Attribute& attribute : attributes) {
        attribute.print(os);
    }
}

Element* Element::findElement(const MyString& id) { 
    if (this->id == id) {
        return this;
    }

    for (MyPointer<Element>& curr : children) {
        Element* currPointer = curr->findElement(id);
        if (currPointer != nullptr) {
            return currPointer;
        }
    }

    return nullptr;
}

int Element::findAttributeIndex(const MyString& attributeKey) {
    for (int i=0; i<attributes.size(); i++) {
        if (attributes[i].key == attributeKey) {
            return i;
        }
    }

    return -1;
}

Attribute* Element::findAttribute(const MyString& id, const MyString& attributeKey) {
    Element* element = root->findElement(id);
    int attributeNumber = element->findAttributeIndex(attributeKey);

    return &element->attributes[attributeNumber];
}

void Element::print(std::ostream& os) {
    root->print(os, 0);
}

void Element::printAttributeValue(std::ostream& os, const MyString& id, const MyString& attributeKey) {
    os<<findAttribute(id, attributeKey)->value<<std::endl;
}

void Element::setAttributeValue(const MyString& id, const MyString& attributeKey, const MyString& attributeValue) {
    findAttribute(id, attributeKey)->value = attributeValue;
}   

void Element::printChildren(std::ostream& os, const MyString& id) {
    root->findElement(id)->printChildren(os, 0);
}

void Element::printChild(std::ostream& os, const MyString& id, int n) {
    root->findElement(id)->children[n]->print(os, 0);
}

void Element::printText(std::ostream& os, const MyString& id) {
    os<<root->findElement(id)->text<<std::endl;
}

void Element::deleteAttribute(const MyString& id, const MyString& attributeKey) {
    Element* element = root->findElement(id);
    int attributeNumber = element->findAttributeIndex(attributeKey);
    
    element->attributes.erase(attributeNumber);
}
