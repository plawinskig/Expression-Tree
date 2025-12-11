#include "pch.h"
#include "tree.hpp"

#include <queue>

Tree::Tree()
    : root_(nullptr),
    variables_(std::vector<Variable *>())
{
}

Tree::Tree(std::string formula)
    : root_(nullptr),
    variables_(std::vector<Variable *>())
{
    Error *err = load_new_formula(formula);
    delete err;
}

Tree::Tree(const Tree &other)
    : root_(nullptr),
    variables_(std::vector<Variable *>())
{
    if (!other.is_empty())
    {
        copy_tree(other);
    }
}

Tree::Tree(Tree &&other) noexcept
    : root_(nullptr),
    variables_(std::vector<Variable *>())
{
    if (!other.is_empty())
    {
        move_tree(std::move(other));
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
        copy_tree(other);
    }

    return *this;
}

Tree &Tree::operator=(Tree &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    delete root_;

    if (other.is_empty())
    {
        root_ = nullptr;
        clear_variables();
    }
    else
    {
        move_tree(std::move(other));
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

Error *Tree::load_new_formula(std::string formula)
{
    Errors *errors = new Errors();

    std::vector<std::string> nodes = split(formula, FORMULA_SEPARATOR);

    if (nodes.empty())
    {
        errors->add(new ErrorEmptyInput());
        delete root_;
        root_ = nullptr;
        clear_variables();
        return errors;
    }

    std::string root_node_type = nodes.at(0);

    if (!Node::is_operation(root_node_type))
    {
        Error *err_inv_chars = Node::skip_invalid_characters(root_node_type);
        errors->add(err_inv_chars);
    }

    delete root_;
    root_ = Node::alloc(root_node_type);

    clear_variables();

    if (root_)
    {
        int offset = 1;
        Error *err_load = root_->load(nodes, offset, offset);
        errors->add(err_load);

        if (offset < nodes.size())
        {
            errors->add(new ErrorTooManyArguments(formula.substr(0, offset), formula.substr(offset)));
        }

        root_->get_variables(variables_);
    }
    
    return errors;
}

Tree Tree::join(const Tree &other) const
{
    if (other.is_empty())
    {
        return Tree(*this);
    }
    
    if (is_empty())
    {
        return Tree(other);
    }

    Tree result(*this);
    Tree other_cpy(other);

    std::vector<Variable *> candidate_vars_to_delete = other_cpy.variables_;

    Node *connector = result.root_->get_last_leaf();
    Node *connector_parent = connector->get_parent();

    other_cpy.root_->set_parent(connector_parent);

    if (connector_parent != nullptr)
    {
        connector_parent->set_last_child(other_cpy.root_);
        delete connector;
    }
    else
    {
        delete result.root_;
        result.root_ = other_cpy.root_;
    }

    other_cpy.root_ = nullptr;
    other_cpy.variables_.clear();

    result.variables_.clear();
    result.root_->get_variables(result.variables_);

    // garbage collector
    for (std::vector<Variable *>::const_iterator it_candidate = candidate_vars_to_delete.begin(); it_candidate < candidate_vars_to_delete.end(); it_candidate++)
    {
        bool still_used = false;

        for (std::vector<Variable *>::const_iterator it_variable = result.variables_.begin(); it_variable < result.variables_.end(); it_variable++)
        {
            if (*it_variable == *it_candidate)
            {
                still_used = true;
                break;
            }
        }

        if (!still_used)
        {
            delete *it_candidate;
        }
    }

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

int Tree::get_number_of_variables() const
{
    return variables_.size();
}

std::string Tree::get_formula_to_string() const
{
    std::string result;

    if (!is_empty())
    {
        get_formula_to_string(root_, result);
    }
    else
    {
        return EMPTY_FORMULA_STRING;
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

std::string Tree::get_levels_to_string() const
{
    if (is_empty())
    {
        return EMPTY_FORMULA_STRING;
    }

    std::string result;

    int level = 0;
    int max_level = get_depth();

    while (level <= max_level)
    {
        result += get_level_to_string(level) + "\n";
        level++;
    }

    return result;

    // second version
    //std::queue<Node *> queue;
    //queue.push(root_);

    //std::string result;

    //int level = 0;

    //while (!queue.empty())
    //{
    //    Node *current = queue.front();

    //    if (level != current->get_level())
    //    {
    //        result += "\n";
    //        level++;
    //    }

    //    result += current->to_string() + FORMULA_SEPARATOR;

    //    for (int i = 0; i < current->get_number_of_children(); i++)
    //    {
    //        queue.push(current->get_child(i));
    //    }

    //    queue.pop();
    //}

    //return result;
}

std::string Tree::get_variables_to_string() const
{
    if (variables_.empty())
    {
        return std::string();
    }

    std::string result = variables_.front()->get_name();

    for (int i = 1; i < variables_.size(); i++)
    {
        result += FORMULA_SEPARATOR + variables_.at(i)->get_name();
    }

    return result;
}

Error *Tree::set_variables(const std::vector<int> &variables)
{
    if (variables_.size() != variables.size())
    {
        return new ErrorIncorrectNumberOfArguments(SET_VARIABLES_COMMAND, variables_.size(), variables.size());
    }

    for (int i = 0; i < variables.size(); i++)
    {
        variables_.at(i)->set_value(variables.at(i));
    }

    return nullptr;
}

void Tree::move_tree(Tree &&other)
{
    root_ = other.root_;
    other.root_ = nullptr;

    root_->get_variables(variables_);
    other.variables_.clear();
}

void Tree::copy_tree(const Tree &other)
{
    root_ = other.root_->clone();
    root_->get_variables(variables_);
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
