#include "tree.hpp"
#include "node.hpp"
#include <iostream>
#include <vector>

void print(Node &node)
{
    std::cout << node << " ";
    for (int i = 0; i < node.get_number_of_children(); i++)
    {
        print(*(node.get_child(i)));
    }
}

int main() 
{
    std::string formula = "+ * a sin / 5 6 + c dup";
    std::vector<std::string> form_vec = Tree::split(formula, " ");
    Node *root = Node::alloc(form_vec.at(0));
    int n = 1;
    root->load(form_vec, n);

    print(*root);

    return 0;
}


