#include "attribute.h"

bool Attribute::operator==(const Attribute &oth) const {
    return key == oth.key && value == oth.value; 
}

void Attribute::print(std::ostream& os) const {
    os<<' '<<key<<"=\""<<value<<'\"';
}

