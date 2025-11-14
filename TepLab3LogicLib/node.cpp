#include "pch.h"
#include "node.hpp"

#include <cctype>

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

bool Node::is_value(std::string node_type)
{
    for (std::string::iterator it = node_type.begin(); it != node_type.end(); it++)
    {
        if (*it < MIN_DIGIT || *it > MAX_DIGIT)
        {
            return false;
        }
    }

    return true;
}

bool Node::is_variable(std::string node_type)
{
    bool has_only_digits = true;

    for (std::string::iterator it = node_type.begin(); it != node_type.end(); it++)
    {
        if (!std::isalnum(*it))
        {
            return false;
        }
        
        if (!std::isdigit(*it))
        {
            has_only_digits = false;
        }
    }

    return !has_only_digits;
}

std::string Node::skip_invalid_characters(std::string node_type)
{
    for (std::string::iterator it = node_type.begin(); it != node_type.end();)
    {
        if (!std::isalnum(*it))
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
