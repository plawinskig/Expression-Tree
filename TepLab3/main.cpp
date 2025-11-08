#include "tree.hpp"
#include <iostream>

int main() 
{
    //std::string user = readUserName(std::cin, std::cout);
    //std::cout << "Witaj, " << user << "!" << std::endl;

    Node *plus = new Node("+");
    Node *lmult = new Node("*");
    Node *rmult = new Node("*");
    Node *five = new Node("5");
    Node *sin = new Node("sin");
    Node *avg = new Node("avg");
    Node *eight = new Node("8");
    Node *x = new Node("x");
    Node *a = new Node("a");
    Node *b = new Node("b");
    Node *c = new Node("c");
    int non = 11;

    //c->set_up_node(b);
    b->set_sibling(c);
    //b->set_up_node(a);
    a->set_sibling(b);
    //a->set_up_node(avg);
    avg->set_child(a);
    avg->set_sibling(eight);
    //avg->set_up_node(rmult);
    rmult->set_child(avg);
    //rmult->set_up_node(lmult);

    //x->set_up_node(sin);
    sin->set_child(x);
    //sin->set_up_node(five);
    five->set_sibling(sin);
    //five->set_up_node(lmult);
    lmult->set_child(five);
    lmult->set_sibling(rmult);
    //lmult->set_up_node(plus);

    plus->set_child(lmult);

    Tree tree(plus, non);
    std::cout << tree.get_formula() << "\n";

    return 0;
}