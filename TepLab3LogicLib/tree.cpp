#include "pch.h"
#include "tree.hpp"

Tree::Tree()
    :root_(nullptr)
{
}

Tree::Tree(std::string formula)
    :root_(nullptr)
{
    load_new_formula(formula);
}

Tree::~Tree()
{
    delete root_;
}

Node *Tree::get_root()
{
    return root_;
}

void Tree::load_new_formula(std::string formula)
{
    std::vector<std::string> form_vec = split(formula, FORMULA_SEPARATOR);

    delete root_;
    root_ = Node::alloc(form_vec.at(0));

    int offset = 1;
    root_->load(form_vec, offset);
}

void Tree::join(Tree &other)
{
    if (this == &other || other.is_empty())
    {
        return;
    }

    if (is_empty())
    {
        root_ = other.root_;
        other.root_ = nullptr;
        return;
    }

    Node *connector = root_->get_last_leaf();
    Node *connector_parent = connector->get_parent();
    Node *other_root = other.root_;

    other_root->set_parent(connector_parent);
    connector_parent->set_last_child(other_root);
    delete connector;
    other.root_ = nullptr;
}

bool Tree::is_empty() const
{
    return root_ == nullptr;
}

int Tree::get_depth() const
{
    return is_empty() ? 0 : root_->get_depth();
}

std::string Tree::get_formula_to_string() const
{
    std::string result;

    if (!is_empty())
    {
        get_formula_to_string(root_, result);
    }
     
    return result;
}

void Tree::get_formula_to_string(Node *node, std::string &result) const
{
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
    
    if (!is_empty())
    {
        get_level_to_string(root_, result, level);
    }

    if (!result.empty())
    {
        result.pop_back();
    }

    return result;
}

void Tree::get_level_to_string(Node *node, std::string &result, int level) const
{
    if (node->get_level() == level)
    {
        result += node->to_string() + FORMULA_SEPARATOR;
        return;
    }

    if (node->is_nil())
    {
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

    while (level < max_level)
    {
        std::cout << tree.get_level_to_string(level) << "\n";
        level++;
    }
}
