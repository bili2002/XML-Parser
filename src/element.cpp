#include <iostream>
#include <stdlib.h>   
#include <time.h>  

#include "element.h"
#include "printing.h"

MyPointer<Element> Element::root = new Element();

Element::Element() {};
Element::Element(const MyString& tag) : tag(tag) {};

MyVector<Element*> Element::operator/(const MyString& tag)  {
    MyVector<Element*> temp;
    for (MyPointer<Element>& curr : children) {
        if (curr->tag == tag) {
            temp.push_back(curr.getPtr());
        }
    }

    return temp;
}

bool Element::hasAttribute(const Attribute& attribute) {
    for (MyPointer<Attribute>& currAttribute : attributes) {
        if (currAttribute.get() == attribute) {
            return true;
        }
    }

    return false;
}

void Element::idCheck() {
    if (id.empty()) {
        for (int i=0; i<3; i++) {
            id += rand() % 26 + 'a';
        }
    }

    MyString temp = id;
    id.clear();

    Element* oth = findElement(temp);
    id = temp;
    if (oth != nullptr) {
        oth->id += '_';
        oth->id += '1';
        oth->idCheck();

        id += '_';
        id += '2';
        idCheck();
    }
}

void Element::setId(const MyString& value) {
    id = value;
    idCheck();
}

void Element::readOpeningTag(std::istream& is) {char temp;
    is>>temp;

    if (temp != '<') {
        std::cerr<<"Error\n";
        return;
    }

    while (true) {
        is.get(temp);
        if (temp == '>' || temp == ' ') {
            break;
        }

        tag += temp;
    }

    bool readingKey = true;
    attributes.push_back(new Attribute);

    while (temp != '>') {
        is>>temp;
        if (temp == '>' || temp == '\"') {
            if (attributes.back()->key == toMyString("id")) {
                setId(attributes.pop_back()->value);
            }

            if (temp == '>' ) {
                break;
            } else {
                readingKey = true;
                attributes.push_back(new Attribute);
                continue;
            }
        }

        if (temp == '=') {
            readingKey = false;
            is>>temp;  
            continue;
        }

        if (readingKey) {
            attributes.back()->key += temp;
        } else {
            attributes.back()->value += temp;
        }
    }

    if (attributes.back()->key.empty()) {
        attributes.pop_back();
    }

    idCheck();
}

void Element::readElement(std::istream& is) {
    readOpeningTag(is);

    while (true) {
        char temp;
        is>>temp;

        if (temp == '<') {
            is>>temp;
            if (temp == '/') {
                while (temp != '>') {
                    is>>temp;
                }
                return;
            }

            is.seekg(-2, std::ios::cur);

            children.push_back(new Element());
            children.back()->parent = this;
            children.back()->readElement(is);
        } else {
            text += temp;
            continue;
        }
    }
}

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
    for (const MyPointer<Attribute>& attribute : attributes) {
        attribute->print(os);
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
        if (attributes[i]->key == attributeKey) {
            return i;
        }
    }

    return -1;
}

Attribute* Element::findAttribute(const MyString& id, const MyString& attributeKey) {
    Element* element = root->findElement(id);
    int attributeNumber = element->findAttributeIndex(attributeKey);

    if (attributeNumber < 0) {
        return nullptr;
    }

    return element->attributes[attributeNumber].getPtr();
}

void Element::input(std::istream& is) {
    root->readElement(is);
}

void Element::print(std::ostream& os) {
    root->print(os, 0);
}

void Element::printAttributeValue(std::ostream& os, const MyString& id, const MyString& attributeKey) {
    if (attributeKey == toMyString("id")) {
        os<<root->findElement(id)->id<<std::endl;
        return;
    }

    os<<findAttribute(id, attributeKey)->value<<std::endl;
}

void Element::setAttributeValue(const MyString& id, const MyString& attributeKey, const MyString& attributeValue) {    
    if (attributeKey == toMyString("id")) {
        root->findElement(id)->setId(attributeValue);
        return;
    }

    Attribute* attribute = findAttribute(id, attributeKey);
    if (attribute == nullptr) {
        std::cerr<<"Error: There is not attribute with this key.\n";
        return;
    }

    attribute->value = attributeValue;
}   

void Element::printChildren(std::ostream& os, const MyString& id) {
    Element* element = root->findElement(id);
    if (element->children.empty()) {
        std::cerr<<"Error: There are no children.\n";
        return;
    }

    element->printChildren(os, 0);
}

void Element::printChild(std::ostream& os, const MyString& id, int n) {
    MyVector<MyPointer<Element>>& children = root->findElement(id)->children;
    if (children.size() <= n) {
        std::cerr<<"Error: N is too big.\n";
        return;
    }

    children[n]->print(os, 0);
}

void Element::printText(std::ostream& os, const MyString& id) {
    MyString& text = root->findElement(id)->text;
    if (text.empty()) {
        std::cerr<<"Error: There is no text.\n";
        return;
    }

    os<<text<<std::endl;
}

void Element::deleteAttribute(const MyString& id, const MyString& attributeKey) {
    if (attributeKey == toMyString("id")) {
        std::cerr<<"Error: Can't delete ID.\n";
        return;
    }

    Element* element = root->findElement(id);
    int attributeNumber = element->findAttributeIndex(attributeKey);

    if (attributeNumber < 0) {
        std::cerr<<"Error: No such attribute.\n";
        return;
    }
    
    element->attributes.erase(attributeNumber);
}

void Element::addChild(const MyString& id, const MyString& tag) {
    root->findElement(id)->children.push_back(new Element(tag));
}

void Element::xpath(std::ostream& os, const MyString& path) {
    MyVector<Element*> currentElements;

    bool printed = false;
    currentElements.push_back(root.getPtr());

    for (int i=0; i<path.size(); ) {
        if (path[i] == '/' || i == 0) {
            if (path[i] == '/') {
                i++;
            }

            MyString tag;
            while (i < path.size() && isLetter(path[i])) {
                tag += path[i++];
            }

            MyVector<Element*> temp;
            for (Element* element : currentElements) {
                temp.append(*element/tag);
            }

            std::swap(temp, currentElements);
            continue;
        }
         
        if (path[i] == '[') {
            i++;
            printed = true;

            int num = 0;    
            while (isNumber(path[i])) {
                num = num*10 + path[i++] - '0';
            }

            if (num > currentElements.size()) {
                os<<"Error number is too big!\n";
            } else {
                os<<currentElements[num]->text<<'\n';
            }
            break;
        }

        if (path[i] == '(') {
            i++;

            if (path[i] == '@') {
                i++;
                printed = true;

                MyString key;
                while (i < path.size() && isLetter(path[i])) {
                    key += path[i++];
                }

                if (key == toMyString("id")) {
                    for (Element* element : currentElements) {
                        os<<element->id<<'\n';
                    }
                }

                for (Element* element : currentElements) {
                    int attributeNumber = element->findAttributeIndex(key);

                    if (attributeNumber != -1) {
                        os<<element->attributes[attributeNumber]->value<<'\n';
                    }
                }

                break;
            }

            Attribute attribute;
            while (i < path.size() && isLetter(path[i])) {
                attribute.key += path[i++];
            }
            i += 2;

            while (i < path.size() && isLetter(path[i])) {
                attribute.value += path[i++];
            }
            i += 2;

            MyVector<Element*> temp;
            for (Element* element : currentElements) {
                if (element->hasAttribute(attribute)) {
                    temp.push_back(element);
                }
            }

            std::swap(temp, currentElements);
            continue;
        }

        i++;
    }

    if (!printed) {
        for (Element* element : currentElements) {
            os<<element->text<<'\n';
        }
    }
}

bool Element::isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool Element::isNumber(char ch) {
    return ch >= '0' && ch <= '9';
}