#include "tree.hpp"
#include <iostream>

int main() 
{
    //std::string user = readUserName(std::cin, std::cout);
    //std::cout << "Witaj, " << user << "!" << std::endl;

    Node plus("+");
    Node lmult("*");
    Node rmult("*");
    Node five("5");
    Node sin("sin");
    Node fun("fun");
    Node eight("8");
    Node x("x");
    Node a("a");
    Node b("b");
    Node c("c");
    int non = 11;

    c.set_up_node(&b);
    b.set_sibling(&c);
    b.set_up_node(&a);
    a.set_sibling(&b);
    a.set_up_node(&fun);
    fun.set_child(&a);
    fun.set_sibling(&eight);
    fun.set_up_node(&rmult);
    rmult.set_child(&fun);
    rmult.set_up_node(&lmult);

    x.set_up_node(&sin);
    sin.set_child(&x);
    sin.set_up_node(&five);
    five.set_sibling(&sin);
    five.set_up_node(&lmult);
    lmult.set_child(&five);
    lmult.set_sibling(&rmult);
    lmult.set_up_node(&plus);

    plus.set_child(&lmult);

    Tree tree(&plus, non);
    std::cout << tree.get_formula() << "\n";

    return 0;
}