#include "pch.h"
#include "node.hpp"

#include <cctype>
#include <cmath>
#include <iostream>

Node::Node(int number_of_children)
    :parent_(nullptr),
    children_(number_of_children, nullptr)
{
}

Node::~Node()
{
    for (std::vector<Node *>::iterator it = children_.begin(); it != children_.end(); it++)
    {
        delete *it;
    }
}

Error Node::load(const std::vector<std::string> nodes, int off_start, int &off_end)
{
    if (is_nil())
    {
        return Error();
    }

    for (int i = 0; i < get_number_of_children(); i++)
    {
        Node *child = alloc(nodes.at(off_start + i));

        if (child == nullptr)
        {
            return Error("eeeeeeeeeeeeeeeeee"); // TODO
        }

        off_end++;

        child->load(nodes, off_end, off_end);
    }

    return Error();
}

bool Node::is_nil() const
{
    return children_.empty();
}

Node *Node::get_parent() const
{
    return parent_;
}

Node *Node::get_child(int child_index) const
{
    return children_.at(child_index);
}

int Node::get_number_of_children() const
{
    return children_.size();
}

bool Node::set_parent(Node *parent)
{
    parent_ = parent;
    return true;
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
    Node *node = nullptr;

    if (is_value(node_type))
    {
        node = new NodeValue(node_type);
    }
    else if (is_variable(node_type))
    {
        node = new NodeVariable(node_type);
    }
    else if(is_operation(node_type))
    {
        node = NodeOperation::make_operation(node_type);
    }

    return node;
}

bool Node::is_value(std::string node_type)
{
    for (std::string::iterator it = node_type.begin(); it != node_type.end(); it++)
    {
        if (!std::isdigit(*it))
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

bool Node::is_operation(std::string node_type)
{
    for (int i = 0; i < OP_COUNT; i++)
    {
        if (node_type == OP_SYMBOLS[i])
        {
            return true;
        }
    }

    return false;
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

NodeVariable::NodeVariable(std::string name, int value)
    :Node(VARIABLE_NUM_OF_CHILDREN),
    name_(name),
    value_(value)
{
}

void NodeVariable::set_value(int value)
{
    value_ = value;
}

NodeOperation::NodeOperation(int number_of_children)
    :Node(number_of_children)
{
}

NodeOperationAddition::NodeOperationAddition(int number_of_children)
    :NodeOperation(number_of_children)
{
}

std::string NodeOperationAddition::get_type() const
{
    return OP_SYMBOLS[OP_ADDITION_INDEX];
}

NodeOperationSubtraction::NodeOperationSubtraction(int number_of_children)
    :NodeOperation(number_of_children)
{
}

std::string NodeOperationSubtraction::get_type() const
{
    return OP_SYMBOLS[OP_SUBTRACTION_INDEX];
}

NodeOperationMultiplication::NodeOperationMultiplication(int number_of_children)
    :NodeOperation(number_of_children)
{
}

std::string NodeOperationMultiplication::get_type() const
{
    return OP_SYMBOLS[OP_MULTIPLICATION_INDEX];
}

NodeOperationDivision::NodeOperationDivision(int number_of_children)
    :NodeOperation(number_of_children)
{
}

std::string NodeOperationDivision::get_type() const
{
    return OP_SYMBOLS[OP_DIVISION_INDEX];
}

NodeOperationSin::NodeOperationSin(int number_of_children)
    :NodeOperation(number_of_children)
{
}

std::string NodeOperationSin::get_type() const
{
    return OP_SYMBOLS[OP_SIN_INDEX];
}

NodeOperationCos::NodeOperationCos(int number_of_children)
    :NodeOperation(number_of_children)
{
}

std::string NodeOperationCos::get_type() const
{
    return OP_SYMBOLS[OP_COS_INDEX];
}

int NodeOperationAddition::get_value() const
{
    int result = 0;

    for (int i = 0; i < get_number_of_children(); i++)
    {
        result += get_child(i)->get_value();
    }

    return result;
}

int NodeOperationSubtraction::get_value() const
{
    int result = get_child(0)->get_value();

    for (int i = 1; i < get_number_of_children(); i++)
    {
        result -= get_child(i)->get_value();
    }

    return result;
}

int NodeOperationMultiplication::get_value() const
{
    int result = 1;

    for (int i = 0; i < get_number_of_children(); i++)
    {
        result *= get_child(i)->get_value();
    }

    return result;
}

int NodeOperationDivision::get_value() const
{
    int result = get_child(0)->get_value();

    for (int i = 1; i < get_number_of_children(); i++)
    {
        result /= get_child(i)->get_value();
    }

    return result;
}

int NodeOperationSin::get_value() const
{
    return std::sin(get_child(0)->get_value());
}

int NodeOperationCos::get_value() const
{
    return std::cos(get_child(0)->get_value());
}

int NodeVariable::get_value() const
{
    return value_;
}

std::string NodeVariable::get_name() const
{
    return name_;
}

NodeValue::NodeValue(std::string value)
    :Node(VALUE_NUM_OF_CHILDREN),
    value_(std::atoi(value.c_str()))
{
}

NodeValue::NodeValue(int value)
    :Node(VALUE_NUM_OF_CHILDREN),
    value_(value)
{
}

int NodeValue::get_value() const
{
    return value_;
}

NodeOperation *NodeOperation::make_operation(std::string operation)
{
    if (operation == OP_SYMBOLS[OP_ADDITION_INDEX])
    {
        NodeOperation *node = new NodeOperationAddition();
        return node;
    }

    else if (operation == OP_SYMBOLS[OP_SUBTRACTION_INDEX])
    {
        return new NodeOperationSubtraction();
    }

    else if (operation == OP_SYMBOLS[OP_MULTIPLICATION_INDEX])
    {
        return new NodeOperationMultiplication();
    }

    else if (operation == OP_SYMBOLS[OP_DIVISION_INDEX])
    {
        return new NodeOperationDivision();
    }

    else if (operation == OP_SYMBOLS[OP_SIN_INDEX])
    {
        return new NodeOperationSin();
    }

    else if (operation == OP_SYMBOLS[OP_COS_INDEX])
    {
        return new NodeOperationCos();
    }

    return nullptr;
}

std::ostream &operator<<(std::ostream &os, const NodeOperation &node)
{
    return os << node.get_type();
}

std::ostream &operator<<(std::ostream &os, const NodeVariable &node)
{
    return os << node.get_name();
}

std::ostream &operator<<(std::ostream &os, const NodeValue &node)
{
    return os << node.get_value();
}
