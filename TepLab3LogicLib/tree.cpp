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
    if(DEBUG_LOAD_NEW_FORMULA) std::cout << "\nNew recursion for (" << formula << ") and (" << *parent_node << ")\n";

    if (parent_node->is_nil())
    {
        if (DEBUG_LOAD_NEW_FORMULA) std::cout << "End recursion for (" << formula << ") and (" << *parent_node << "): [" << *parent_node << " is nil]\n";
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

        if (DEBUG_LOAD_NEW_FORMULA) std::cout << "\nChild: " << i << "\n";
        if (DEBUG_LOAD_NEW_FORMULA) std::cout << "Head: (" << formula_head << ")\tTail: (" << formula_tail << ")\n";

        Node *child_node = load_formula_elem_into_node(formula_head);

        // invalid formula element
        if (child_node == nullptr)
        {
            child_node = new Node(DEFAULT_VARIABLE_NAME, 0);
        }
        
        parent_node->set_child(child_node, i);
        if (DEBUG_LOAD_NEW_FORMULA) std::cout << "Connected: " << *parent_node << " ---> " << *child_node << "\n";

        if (!formula_tail.empty())
        {
            load_new_formula_helper(formula_tail, child_node);
        }

        formula = formula_tail;
    }
}

Node *Tree::load_formula_elem_into_node(std::string formula_elem)
{
    Node *node = nullptr;

    // constant
    if (is_constant(formula_elem))
    {
        node = new Node(formula_elem, 0);
        if (DEBUG_LOAD_NEW_FORMULA) std::cout << "Created node: " << node << "\n";
        return node;
    }

    operation operation = load_operation(formula_elem);

    // variable
    if (operation == NOT_OPERATION)
    {
        std::string variable = load_variable(formula_elem);
        if (!variable.empty())
        {
            node = new Node(variable, 0);
        }
    }
    // operation
    else
    {
        node = new Node(operation.type, operation.number_of_arguments);
    }

    if (node != nullptr)
    {
        if (DEBUG_LOAD_NEW_FORMULA) std::cout << "Created node: " << node << "\n";
    }
    
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

std::string Tree::load_variable(std::string formula_elem)
{
    for (int i = 0; i < formula_elem.length(); i++)
    {
        if (!is_variable_character(formula_elem[i]))
        {
            if (ENABLE_WARNINGS)
            {
                std::cout << "[WARNING] Character '" << formula_elem[i] << "' is not permitted in variable names. Omitting.\n";
            }

            formula_elem = formula_elem.erase(i, 1);
        }
    }

    return formula_elem;
}

bool Tree::is_constant(std::string formula_elem)
{
    for (int i = 0; i < formula_elem.length(); i++)
    {
        if (formula_elem[i] < MIN_DIGIT || formula_elem[i] > MAX_DIGIT)
        {
            return false;
        }
    }
    
    return true;
}

std::string Tree::get_formula()
{
    std::string formula;
    get_formula(root_->get_child(0), formula);
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

bool Tree::is_variable_character(char chr)
{
    bool is_lower_case_letter = MIN_VARIABLE_LOWER <= chr && chr <= MAX_VARIABLE_LOWER;
    bool is_upper_case_letter = MIN_VARIABLE_UPPER <= chr && chr <= MAX_VARIABLE_UPPER;
    bool is_digit = MIN_DIGIT <= chr && chr <= MAX_DIGIT;

    return is_lower_case_letter || is_upper_case_letter || is_digit;
}
