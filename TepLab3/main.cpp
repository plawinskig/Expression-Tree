#include "tree.hpp"
#include <iostream>

int main() 
{
    //std::string user = readUserName(std::cin, std::cout);
    //std::cout << "Witaj, " << user << "!" << std::endl;

    //return 0;

    Node *plus = new Node("+", 2);
    Node *lmult = new Node("*", 2);
    Node *rmult = new Node("*", 2);
    Node *five = new Node("5", 0);
    Node *sin = new Node("sin", 1);
    Node *avg = new Node("avg", 3);
    Node *eight = new Node("8", 0);
    Node *x = new Node("x", 0);
    Node *a = new Node("a", 0);
    Node *b = new Node("b", 0);
    Node *c = new Node("c", 0);
    int non = 11;

    plus->set_child(lmult, 0);
    plus->set_child(rmult, 1);

    lmult->set_child(five, 0);
    lmult->set_child(sin, 1);

    sin->set_child(x, 0);

    rmult->set_child(avg, 0);
    rmult->set_child(eight, 1);

    avg->set_child(a, 0);
    avg->set_child(b, 1);
    avg->set_child(c, 2);

    //Tree tree(plus, non);
    //std::cout << tree.get_formula() << "\n";

    std::string formula_short = "+ * 1 2 a";
    std::string formula_long = "+ * 5 sin x * avg3 a b c 8";

    std::cout << formula_short << "\n";
    Tree tree_short(formula_short);
    std::cout << tree_short.get_formula() << "\n";

    //std::cout << formula_long << "\n";
    //Tree tree_long(formula_long);
    //std::cout << tree_long.get_formula() << "\n";

    return 0;
}