#include "pch.h"
#include "tree.hpp"

Tree::Tree()
    : root_(nullptr),
    variables_(std::vector<Variable *>())
{
}

Tree::Tree(std::string formula)
    : root_(nullptr),
    variables_(std::vector<Variable *>())
{
    load_new_formula(formula);
}

Tree::Tree(const Tree &other)
    : root_(nullptr),
    variables_(std::vector<Variable *>())
{
    if (!other.is_empty())
    {
        load_new_formula(other.get_formula_to_string());
    }
}

Tree &Tree::operator=(const Tree &other)
{
    if (this == &other)
    {
        return *this;
    }

    if (other.is_empty())
    {
        delete root_;
        root_ = nullptr;
        clear_variables();
    }
    else
    {
        load_new_formula(other.get_formula_to_string());
    }

    return *this;
}

Tree::~Tree()
{
    delete root_;
    clear_variables();
}

Tree Tree::operator+(const Tree &other) const
{
    return this->join(other);
}

Node *Tree::get_root()
{
    return root_;
}

Error *Tree::load_new_formula(std::string formula)
{
    Errors *errors = new Errors();

    std::vector<std::string> nodes = split(formula, FORMULA_SEPARATOR);

    std::string root_node_type = nodes.at(0);

    Errors *err_invalid_characters = Node::skip_invalid_characters(root_node_type);
    errors->add(err_invalid_characters);

    delete root_;
    root_ = Node::alloc(nodes.at(0));

    int offset = 1;
    Error *err_load = root_->load(nodes, offset, offset);
    errors->add(err_load);
    
    clear_variables();
    root_->get_variables(variables_);

    return errors;
}

Tree Tree::join(const Tree &other) const
{
    if (other.is_empty())
    {
        return *this;
    }
    
    if (is_empty())
    {
        return other;
    }

    Tree result(*this);
    Tree other_cpy(other);

    Node *connector = result.root_->get_last_leaf();
    Node *connector_parent = connector->get_parent();

    other_cpy.root_->set_parent(connector_parent);
    connector_parent->set_last_child(other_cpy.root_);

    delete connector;

    other_cpy.root_ = nullptr;
    other_cpy.variables_.clear();

    result.variables_.clear();
    result.root_->get_variables(result.variables_);

    return result;
}

float Tree::calculate_formula() const
{
    if (is_empty())
    {
        return 0.0f;
    }

    return root_->get_value();
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

void Tree::clear_variables()
{
    for (std::vector<Variable *>::iterator it = variables_.begin(); it != variables_.end(); it++)
    {
        delete *it;
    }

    variables_.clear();
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

std::string Tree::get_variables_to_string() const
{
    if (variables_.empty())
    {
        return std::string();
    }

    std::string result = variables_.front()->get_name();

    for (size_t i = 1; i < variables_.size(); i++)
    {
        result += FORMULA_SEPARATOR + variables_.at(i)->get_name();
    }

    return result;
}

bool Tree::set_variables(const std::vector<int> &variables)
{
    if (variables_.size() != variables.size())
    {
        return false;
    }

    for (size_t i = 0; i < variables.size(); i++)
    {
        variables_.at(i)->set_value(variables.at(i));
    }

    return true;
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
