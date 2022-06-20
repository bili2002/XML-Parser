#include "printing.h"

void Print::printSpaces(std::ostream& os, int spacing) {
    for (int i=0; i<2*spacing; i++) {
        os<<' ';
    }
}

void Print::endTag(std::ostream& os, const MyString& key) {
    os<<"<\\"<<key<<">\n";
}