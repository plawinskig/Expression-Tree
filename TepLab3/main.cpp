#include "tree.hpp"
#include "node.hpp"
#include <iostream>
#include <vector>

int main() 
{
    std::string formula1 = "+ * a sin / 5 6 + c dup";
    std::string formula2 = "+ * 5 sin x * + a b 8";
    std::string formula3 = "+ * A sin B + A A";

    Tree tree0;
    Tree tree1(formula1);
    Tree tree2(formula2);
    Tree tree3(formula3);

    std::cout << "-----------------------------\n";

    std::cout << "Tree0: " << tree0.get_formula_to_string() << "\n";
    std::cout << "Tree1: " << tree1.get_formula_to_string() << "\n";
    std::cout << "Tree2: " << tree2.get_formula_to_string() << "\n";
    std::cout << "Tree3: " << tree3.get_formula_to_string() << "\n";

    std::cout << "-----------------------------\n";

    std::cout << std::sin(5.0 / 6) << "\n";
    std::cout << tree1.calculate_formula() << "\n";

    return 0;
}


