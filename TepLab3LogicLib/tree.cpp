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
    load_new_formula(formula_iter, root_);
}

void Tree::load_new_formula(std::string::iterator &formula_iter, Node *parent_node)
{
    std::cout << "Current iter: " << *formula_iter << "\tParent node: " << parent_node << "\n";

    int num_of_children = parent_node->get_number_of_children();

    if (num_of_children == 0)
    {
        std::cout << "Current iter has no children\n";
        return;
    }

    for (int i = 0; i < num_of_children; i++)
    {
        std::cout << "Current iter: " << *formula_iter << "\tChild no. " << i << "\n";
        
        if (is_whitespace(formula_iter))
        {
            std::cout << "Not connected\n";
            formula_iter++;
            i--;
        }
        else if (is_constant(formula_iter))
        {

        }
        else if (is_variable(formula_iter))
        {

        }
        else
        {
            operation operation = load_formula_operation(formula_iter);

            Node *child_node = new Node(operation.type, operation.number_of_arguments);
            parent_node->set_child(child_node, i);

            std::cout << "Connected: " << parent_node << " ---> " << child_node << "\n";

            formula_iter += operation.type.length();
            load_new_formula(formula_iter, child_node);
        }
    }
}

operation Tree::load_formula_operation(std::string::iterator formula_iter)
{
    for (int i = 0; i < SIZE_OF_OPR_ARR; i++)
    {
        operation operation = DEFAULT_OPERATIONS_ARRAY[i];

        if (is_operation(formula_iter, operation))
        {
            return operation;
        }
    }

    return NOT_OPERATION;
}

bool Tree::is_operation(std::string::iterator formula_iter, operation &operation)
{
    int operation_length = operation.type.length();

    for (int i = 0; i < operation_length; i++, formula_iter++)
    {
        if (*formula_iter != operation.type[i])
        {
            return false;
        }
    }

    return true;
}

bool Tree::is_whitespace(std::string::iterator formula_iter)
{
    for (int i = 0; i < SIZE_OF_WHITESPACE_CHARS; i++)
    {
        if (*formula_iter == WHITESPACE_CHARS[i])
        {
            return true;
        }
    }

    return false;
}

bool Tree::is_constant(std::string::iterator formula_iter)
{
    if ('0' <= *formula_iter <= '9')
    {
        return true;
    }

    return false;
}

bool Tree::is_variable(std::string::iterator formula_iter)
{
    return false;
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
