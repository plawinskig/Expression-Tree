#include "pch.h"
#include "tree.hpp"

std::string readUserName(std::istream &input, std::ostream &output) {
    std::string name;
    output << "Podaj nazwe: ";
    input >> name;
    return name;
}
