#include "tree.hpp"
#include "node.hpp"
#include <iostream>
#include <vector>

int main() 
{
    std::string formula1 = "+ * a sin / 5 6 + c dup";
    std::string formula2 = "+ * 5 sin x * + a b 8";
    std::string formula3 = "+ * A sin B + A A";

    Tree tree1(formula1);
    Tree tree2(formula2);
    Tree tree3(formula3);

    std::cout << "-----------------------------\n";

    std::cout << tree1.get_formula() << "\n";
    std::cout << tree2.get_formula() << "\n";
    std::cout << tree3.get_formula() << "\n";




    return 0;
}


