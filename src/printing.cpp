#include "printing.h"

void Print::printSpaces(std::ostream& os, int spacing) {
    for (int i=0; i<spacing; i++) {
        os<<' ';
    }
}

void Print::endTag(std::ostream& os, const MyString& key) {
    os<<"<\\"<<key<<">\n";
}