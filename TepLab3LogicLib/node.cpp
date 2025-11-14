#include "pch.h"
#include "node.hpp"

Error Node::load(const std::vector<std::string> &nodes, int off_start, int &off_end)
{
    if (is_nil())
    {
        return Error();
    }

    Node *child = alloc(nodes.at(off_start));

    return Error();
}

bool Node::is_nil() const
{
    return children_.empty();
}

Node *Node::get_child(int child_index) const
{
    return children_.at(child_index);
}

int Node::get_number_of_children() const
{
    return children_.size();
}

bool Node::set_child(Node *child, int child_index)
{
    if (child_index < 0 || child_index > children_.size())
    {
        return false;
    }

    children_.insert(children_.begin() + child_index, child);

    return true;
}

bool Node::set_child(Node *child)
{
    children_.push_back(child);
    return true;
}

Node *Node::alloc(std::string node_type)
{

    return nullptr;
}

bool Node::is_constant(std::string node_type)
{
    for (std::string::size_type i = 0; i < node_type.length(); i++)
    {
        if (node_type[i] < MIN_DIGIT || node_type[i] > MAX_DIGIT)
        {
            return false;
        }
    }

    return true;
}

bool Node::is_variable(std::string node_type)
{
    return false;
}

std::string Node::skip_invalid_characters(std::string node_type)
{
    for (std::string::iterator it = node_type.begin(); it != node_type.end();)
    {
        if (!is_variable_character(*it))
        {
            LOG_WARN("Character '" << *it << "' is not permitted in variable names. Omitting.");

            it = node_type.erase(it);
        }
        else
        {
            it++;
        }
    }

    return node_type;
}

bool Node::is_variable_character(char chr, bool is_first)
{
    bool is_lower_case_letter = MIN_VARIABLE_LOWER <= chr && chr <= MAX_VARIABLE_LOWER;
    bool is_upper_case_letter = MIN_VARIABLE_UPPER <= chr && chr <= MAX_VARIABLE_UPPER;
    bool is_digit = MIN_DIGIT <= chr && chr <= MAX_DIGIT;

    return is_lower_case_letter || is_upper_case_letter || (is_digit && !is_first);
}
