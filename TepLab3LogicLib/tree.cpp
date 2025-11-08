#include "pch.h"
#include "tree.hpp"

std::string readUserName(std::istream &input, std::ostream &output) 
{
    std::string name;
    output << "Podaj nazwe: ";
    input >> name;
    return name;
}

Tree::Tree(std::string formula)
{
    load_new_formula(formula);
}

Tree::Tree(Node *root, int number_of_nodes)
    :root_(root),
    number_of_nodes_(number_of_nodes)
{
}

void Tree::load_new_formula(std::string formula)
{
    if (root_ != nullptr)
    {
        delete root_;
    }

    root_ = new Node(ROOT_DATA, ROOT_NUMBER_OF_CHILDREN);
        
    std::string::iterator formula_iter = formula.begin();

    while (formula_iter != formula.end())
    {
        std::string operation = load_formula_operation(formula_iter);

        root_->set_child(new Node(operation, 1), 0); // TODO

        formula_iter += operation.length();
    }

}

std::string Tree::load_formula_operation(std::string::iterator formula_iter)
{
    for (int i = 0; i < SIZE_OF_OPR_ARR; i++)
    {
        std::string operation = DEFAULT_OPERATIONS_ARRAY[i];

        if (is_operation(formula_iter, operation))
        {
            return operation;
        }
    }
}

bool Tree::is_operation(std::string::iterator formula_iter, std::string operation)
{
    int operation_length = operation.length();

    for (int i = 0; i < operation_length; i++, formula_iter++)
    {
        if (*formula_iter != operation[i])
        {
            return false;
        }
    }

    return true;
}

std::string Tree::get_formula()
{
    std::string formula;
    get_formula(root_, formula);
    return formula;
}

void Tree::get_formula(Node *node, std::string &formula)
{
    if (node == nullptr)
    {
        return;
    }

    if (!formula.empty())
    {
        formula += FORMULA_DATA_SEPARATOR;
    }

    // preorder adding
    formula += node->get_data();

    int num_of_children = node->get_number_of_children();

    for (int i = 0; i < num_of_children; i++)
    {
        get_formula(node->get_child(i), formula);
    }
}
