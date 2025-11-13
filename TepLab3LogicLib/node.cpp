#include "pch.h"
#include "node.hpp"

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
