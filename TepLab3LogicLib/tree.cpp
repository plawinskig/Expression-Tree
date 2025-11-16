#include "pch.h"
#include "tree.hpp"

Tree::Tree()
    :root_(nullptr)
{
}

Tree::Tree(std::string formula)
{
    load_new_formula(formula);
}

Tree::~Tree()
{
    delete root_;
}

void Tree::load_new_formula(std::string formula)
{
    std::vector<std::string> form_vec = split(formula, FORMULA_SEPARATOR);

    delete root_;
    root_ = Node::alloc(form_vec.at(0));

    int offset = 1;
    root_->load(form_vec, offset);
}

int Tree::get_depth()
{
    return root_->get_depth();
}

std::string Tree::get_formula_to_string() const
{
    std::string result;
    get_formula_to_string(root_, result);
    return result;
}

void Tree::get_formula_to_string(Node *node, std::string &result) const
{
    if (!node)
    {
        return;
    }

    result += node->to_string();
    
    for (int i = 0; i < node->get_number_of_children(); i++)
    {
        result += FORMULA_SEPARATOR;
        get_formula_to_string(node->get_child(i), result);
    }
}

std::string Tree::get_level_to_string(int level) const
{
    std::string result;
    get_level_to_string(root_, result, level);
    result.pop_back();
    return result;
}

void Tree::get_level_to_string(Node *node, std::string &result, int level) const
{
    if (node->is_nil())
    {
        return;
    }

    if (node->get_level() == level)
    {
        result += node->to_string() + " ";
        return;
    }

    for (int i = 0; i < node->get_number_of_children(); i++)
    {
        get_level_to_string(node->get_child(i), result, level);
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

void print_tree_by_levels(Tree &tree)
{
    int level = 0;
    int max_level = tree.get_depth();

    while (level < 10)
    {
        std::cout << tree.get_level_to_string(level) << "\n";
        level++;
    }
}
