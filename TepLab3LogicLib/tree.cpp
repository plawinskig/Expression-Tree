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
        
    load_new_formula_helper(formula, root_);
}

void Tree::load_new_formula_helper(std::string &formula, Node *parent_node)
{
    std::cout << "\nNew recursion for (" << formula << ") and (" << *parent_node << ")\n";

    if (parent_node->is_nil())
    {
        std::cout << "End recursion for (" << formula << ") and (" << *parent_node << "): [" << *parent_node << " is nil]\n";
        return;
    }

    for (int i = 0; i < parent_node->get_number_of_children(); i++)
    {
        int regex_idx = formula.find(FORMULA_REGEX);

        std::string formula_head;
        std::string formula_tail;

        if (regex_idx == -1)
        {
            formula_head = formula;
        }
        else
        {
            formula_head = formula.substr(0, regex_idx);
            formula_tail = formula.substr(regex_idx + FORMULA_REGEX.length());
        }

        std::cout << "\nChild: " << i << "\n";
        std::cout << "Head: (" << formula_head << ")\tTail: (" << formula_tail << ")\n";

        Node *child_node = load_formula_elem_into_node(formula_head);
        parent_node->set_child(child_node, i);

        std::cout << "Connected: " << *parent_node << " ---> " << *child_node << "\n";

        if (!formula_tail.empty())
        {
            load_new_formula_helper(formula_tail, child_node);
        }

        formula = formula_tail;
    }
}

Node *Tree::load_formula_elem_into_node(std::string formula_elem)
{
    Node *node;

    if (is_constant(formula_elem))
    {
        node = new Node(formula_elem, 0);
        std::cout << "Created node: " << node << "\n";
        return node;
    }

    operation operation = load_operation(formula_elem);

    if (operation == NOT_OPERATION)
    {
        node = new Node("X", 0);
    }
    else
    {
        node = new Node(operation.type, operation.number_of_arguments);
    }

    std::cout << "Created node: " << node << "\n";
    return node;
}

operation Tree::load_operation(std::string formula_elem)
{
    for (int i = 0; i < SIZE_OF_OPR_ARR; i++)
    {
        operation operation = DEFAULT_OPERATIONS_ARRAY[i];

        if (formula_elem == operation.type)
        {
            return operation;
        }
    }

    return NOT_OPERATION;
}

bool Tree::is_constant(std::string formula_elem)
{
    for (int i = 0; i < formula_elem.length(); i++)
    {
        if (formula_elem[i] < MIN_CONSTANT_DIGIT || formula_elem[i] > MAX_CONSTANT_DIGIT)
        {
            return false;
        }
    }
    
    return true;
}

bool Tree::is_variable(std::string formula_elem)
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
        formula += FORMULA_REGEX;
    }

    // preorder adding
    formula += node->get_data();

    int num_of_children = node->get_number_of_children();

    for (int i = 0; i < num_of_children; i++)
    {
        get_formula(node->get_child(i), formula);
    }
}
