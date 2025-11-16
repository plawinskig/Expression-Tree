#include "tree.hpp"
#include "node.hpp"
#include <iostream>
#include <vector>

int main() 
{
    //std::string formula1 = "+ * a sin / 5 6 + c dup";
    //std::string formula2 = "+ * 5 sin x * + a b 8";
    //std::string formula3 = "+ * A sin B + A A";

    //Tree tree0;
    //Tree tree1(formula1);
    //Tree tree2(formula2);
    //Tree tree3(formula3);

    //std::cout << "-----------------------------\n";

    //std::cout << "Tree0: " << tree0.get_formula_to_string() << "\n";
    //std::cout << "Tree1: " << tree1.get_formula_to_string() << "\n";
    //std::cout << "Tree2: " << tree2.get_formula_to_string() << "\n";
    //std::cout << "Tree3: " << tree3.get_formula_to_string() << "\n";

    //std::cout << "-----------------------------\n";

    //std::cout << std::sin(5.0 / 6) << "\n";
    //std::cout << tree1.calculate_formula() << "\n";

    //std::vector<int> vars = {1, 2, 3};
    //std::cout << tree1.get_variables_to_string() << "\n";
    //tree1.set_variables(vars);
    //std::cout << tree1.calculate_formula() << "\n";

    //std::vector<int> vars3 = { 7, 0 };
    //std::cout << tree3.get_variables_to_string() << "\n";
    //tree3.set_variables(vars3);
    //std::cout << tree3.calculate_formula() << "\n";


    std::cout << "-----------------------------\n";

    std::string f1_1 = "+ a 1";
    std::string f2_1 = "+ b 1";
    Tree t1_1(f1_1);
    Tree t2_1(f2_1);

    std::cout << t1_1.get_formula_to_string() << "\n";
    std::cout << t2_1.get_formula_to_string() << "\n";

    std::cout << t1_1.get_variables_to_string() << "\n";
    std::cout << t2_1.get_variables_to_string() << "\n";

    t1_1.join(t2_1);

    std::cout << t1_1.get_formula_to_string() << "\n";
    std::cout << t2_1.get_formula_to_string() << "\n";

    std::cout << t1_1.get_variables_to_string() << "\n";
    std::cout << t2_1.get_variables_to_string() << "\n";

    std::cout << "-----------------------------\n";

    std::string f1_2 = "+ 1 a";
    std::string f2_2 = "+ b 1";
    Tree t1_2(f1_2);
    Tree t2_2(f2_2);

    std::cout << t1_2.get_formula_to_string() << "\n";
    std::cout << t2_2.get_formula_to_string() << "\n";

    std::cout << t1_2.get_variables_to_string() << "\n";
    std::cout << t2_2.get_variables_to_string() << "\n";

    t1_2.join(t2_2);

    std::cout << t1_2.get_formula_to_string() << "\n";
    std::cout << t2_2.get_formula_to_string() << "\n";

    std::cout << t1_2.get_variables_to_string() << "\n";
    std::cout << t2_2.get_variables_to_string() << "\n";

    std::cout << "-----------------------------\n";

    std::string f1 = "+ 1 a";
    std::string f2 = "+ a b";
    Tree t1(f1);
    Tree t2(f2);

    std::cout << t1.get_formula_to_string() << "\n";
    std::cout << t2.get_formula_to_string() << "\n";

    std::cout << t1.get_variables_to_string() << "\n";
    std::cout << t2.get_variables_to_string() << "\n";

    t1.join(t2);

    std::cout << t1.get_formula_to_string() << "\n";
    std::cout << t2.get_formula_to_string() << "\n";

    std::cout << t1.get_variables_to_string() << "\n";
    std::cout << t2.get_variables_to_string() << "\n";

    return 0;
}


