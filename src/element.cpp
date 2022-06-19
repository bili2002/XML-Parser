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
    for (Attribute& currAttribute : attributes) {
        if (currAttribute == attribute) {
            return true;
        }
    }

    return false;
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
            while (((path[i] >= 'a' && path[i] <= 'z') || (path[i] >= 'A' && path[i] <= 'Z')) && i < path.size()) {
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
            while (path[i] >= '0' && path[i] <= '9') {
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
                while (((path[i] >= 'a' && path[i] <= 'z') || (path[i] >= 'A' && path[i] <= 'Z')) && i < path.size()) {
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
                        os<<element->attributes[attributeNumber].value<<'\n';
                    }
                }

                break;
            }

            Attribute attribute;
            while (((path[i] >= 'a' && path[i] <= 'z') || (path[i] >= 'A' && path[i] <= 'Z')) && i < path.size()) {
                attribute.key += path[i++];
            }
            i += 2;

            while (((path[i] >= 'a' && path[i] <= 'z') || (path[i] >= 'A' && path[i] <= 'Z')) && i < path.size()) {
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
