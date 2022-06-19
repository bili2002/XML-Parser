#include "XML_UI.h"
#include "element.h"


#include <iostream>
#include <vector>

using namespace std;

int main() {
    /*XML_UI UI;
    UI.run();*/

    Attribute at;
    at.key = toMyString("name");
    at.value = toMyString("ivan");

    Attribute at2;
    at2.key = toMyString("age");
    at2.value = toMyString("13");

    Element& el2 = *Element::root;
    el2.tag = toMyString("people");
    el2.id = toMyString("-");

    el2.children.push_back(new Element());
    Element& el = *el2.children[0];
    el.tag = toMyString("person");
    el.id = toMyString("1");
    el.attributes.push_back(at);
    el.text = toMyString("1");

    el2.children.push_back(new Element());
    Element& el3 = *el2.children[1];
    el3.tag = toMyString("person");
    el3.id = toMyString("2");
    el3.attributes.push_back(at2);
    el3.text = toMyString("Maria");

    Element::xpath(std::cout, toMyString("person(name='ivan')(@name)"));

    return 0;
}