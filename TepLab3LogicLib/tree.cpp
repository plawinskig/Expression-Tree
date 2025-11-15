#include "pch.h"
#include "tree.hpp"

Tree::Tree(std::string formula)
{
    load_new_formula(formula);
}

void Tree::load_new_formula(std::string formula)
{
    std::vector<std::string> form_vec = split(formula, FORMULA_SEPARATOR);

    delete root_;
    root_ = Node::alloc(form_vec.at(0));

    int offset = 1;
    root_->load(form_vec, offset);
}

std::string Tree::get_formula() const
{
    std::string result;

    if (root_)
    {
        get_formula(root_, result);
    }
    
    return result;
}

void Tree::get_formula(Node *node, std::string &result) const
{
    if (!node)
    {
        return;
    }

    result += node->to_string();
    
    for (int i = 0; i < node->get_number_of_children(); i++)
    {
        result += FORMULA_SEPARATOR;
        get_formula(node->get_child(i), result);
    }
}

std::vector<std::string> Tree::split(std::string formula, std::string separator)
{
    std::vector<std::string> result;

    std::string::size_type next_regex_index = formula.find(separator);
    std::string::size_type regex_length = separator.length();
    std::string::size_type offset = 0;

    while (next_regex_index != std::string::npos)
    {
        if (next_regex_index > offset)
        {
            result.push_back(formula.substr(offset, next_regex_index - offset));
        }

        offset = next_regex_index + regex_length;
        next_regex_index = formula.find(separator, offset);
    }

    if (offset < formula.length())
    {
        result.push_back(formula.substr(offset));
    }

    return result;
}

