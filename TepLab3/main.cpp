#include "tree.hpp"
#include <iostream>

int main() {
    std::string user = readUserName(std::cin, std::cout);
    std::cout << "Witaj, " << user << "!" << std::endl;

    return 0;
}