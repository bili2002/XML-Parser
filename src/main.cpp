#include <iostream>
#include <fstream>
#include <vector>

#include "XML_UI.h"
#include "element.h"

using namespace std;

int main() {
    srand (time(NULL));
    XML_UI UI;
    UI.run();

    return 0;
}