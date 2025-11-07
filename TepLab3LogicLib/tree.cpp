#include "pch.h"
#include "tree.hpp"

std::string readUserName(std::istream &input, std::ostream &output) 
{
    std::string name;
    output << "Podaj nazwe: ";
    input >> name;
    return name;
}

Tree::Tree(Node *root, int number_of_nodes)
{
    root_ = root;
    number_of_nodes_ = number_of_nodes;
}

std::string Tree::get_formula()
{
    return std::string();
}
