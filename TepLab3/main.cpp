#include "tree.hpp"
#include "node.hpp"
#include <iostream>
#include <vector>

int main() 
{
    std::string formula = "+ * a sin / 5 6 + c dup";
    std::vector<std::string> form_vec = Tree::split(formula, " ");
    Node *root = Node::alloc(form_vec.at(0));
    int n = 1;
    root->load(form_vec, n, n);


    

    return 0;
}