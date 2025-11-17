#include "pch.h"
#include "node.hpp"

#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>

Node::Node(int number_of_children)
    : parent_(nullptr),
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

Errors *Node::load(const std::vector<std::string> nodes, int off_start, int &off_end)
{
    LOG_DEBUG("\nStart load recursion for " << *this << "\t"<<" "<<off_end);
    Errors *errors = new Errors();

    if (is_nil())
    {
        LOG_DEBUG("End recursion for nil: " << *this << "\t" << " " << off_end);

        return nullptr;
    }


    for (int i = 0; i < get_number_of_children(); i++)
    {
        LOG_DEBUG("Continue load recursion for " << *this << "\t" << " " << off_end);
        LOG_DEBUG("Alloc child [" << i << "/" << get_number_of_children() << "] for " << *this << "\t" << " " << off_end);

        Node *child;

        if (off_end >= nodes.size())
        {
            LOG_DEBUG("\nEnd load recursion for " << *this << "\t" << " " << off_end);
            errors->add(new ErrorIncorrectNumberOfArguments(this->to_string(), get_number_of_children(), i));
            child = new NodeValue(DEFAULT_VALUE_STRING);
        }
        else
        {
            std::string node_type = nodes.at(off_end);

            if (!is_operation(node_type))
            {
                Error *err_inv_chars = skip_invalid_characters(node_type);
                errors->add(err_inv_chars);
            }

            child = alloc(node_type);

            if (!child)
            {
                LOG_DEBUG("\nEnd load recursion for " << *this << "\t" << " " << off_end);
                errors->add(new ErrorInvalidArgument(this->to_string(), node_type));
                child = new NodeValue(DEFAULT_VALUE_STRING);
            }
        }

        set_child(child, i);
        child->set_parent(this);

        LOG_DEBUG("connected: " << *this << " ---> " << *child);

        off_end++;

        Error *err_load = child->load(nodes, off_end, off_end);
        errors->add(err_load);
    }

    LOG_DEBUG("End recursion for " << *this << "\t" << " " << off_end);

    return errors;
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

Node *Node::get_last_child() const
{
    return children_.back();
}

Node *Node::get_last_leaf()
{
    if (is_nil())
    {
        return this;
    }

    return get_last_child()->get_last_leaf();
}

int Node::get_number_of_children() const
{
    return children_.size();
}

int Node::get_level() const
{
    int level = 0;
    Node *parent = parent_;

    while (parent)
    {
        level++;
        parent = parent->get_parent();
    }

    return level;
}

int Node::get_depth() const
{
    if (is_nil())
    {
        return 0;
    }
    
    int level = 0;

    for (int i = 0; i < get_number_of_children(); i++)
    {
        level = std::max(level, 1 + get_child(i)->get_depth());
    }

    return level;
}

void Node::get_variables(std::vector<Variable *> &variables)
{    
    NodeVariable *node_var = dynamic_cast<NodeVariable *> (this);

    if (node_var)
    {
        std::vector<Variable *>::const_iterator it;
        bool found = false;

        for (it = variables.begin(); it != variables.end() && !found; it++)
        {
            if ((*it)->get_name() == node_var->get_name())
            {
                node_var->set_variable(*it);
                found = true;
            }
        }

        if (!found)
        {
            variables.push_back(node_var->get_variable());
        }
    }

    for (int i = 0; i < get_number_of_children(); i++)
    {
        get_child(i)->get_variables(variables);
    }
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

    children_.at(child_index) = child;

    return true;
}

bool Node::set_last_child(Node *child)
{
    children_.back() = child;
    return true;
}

bool Node::add_last_child(Node *child)
{
    children_.push_back(child);
    return true;
}

Node *Node::alloc(std::string node_type)
{
    if (node_type.empty())
    {
        return nullptr;
    }

    if (is_value(node_type))
    {
        return new NodeValue(node_type);
    }

    if(is_operation(node_type))
    {
        return NodeOperation::make_operation(node_type);
    }

    if (is_variable(node_type))
    {
        Variable *var = new Variable(node_type);
        return new NodeVariable(var);
    }

    return nullptr;
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

Errors *Node::skip_invalid_characters(std::string &node_type)
{
    Errors *errs_inv_char = new Errors();

    for (std::string::iterator it = node_type.begin(); it != node_type.end();)
    {
        if (!std::isalnum(*it))
        {
            errs_inv_char->add(new ErrorInvalidCharacter(node_type, *it));
            it = node_type.erase(it);
        }
        else
        {
            it++;
        }
    }

    if (errs_inv_char->is_empty())
    {
        delete errs_inv_char;
        return nullptr;
    }

    return errs_inv_char;
}

void NodeVariable::set_variable(Variable *var)
{
    if (variable_ != var)
    {
        delete variable_;
        variable_ = var;
    }
}

void NodeVariable::set_value(int value)
{
    variable_->set_value(value);
}

NodeOperation::NodeOperation(int number_of_children)
    : Node(number_of_children)
{
}

NodeOperationAddition::NodeOperationAddition(int number_of_children)
    : NodeOperation(number_of_children)
{
}

std::string NodeOperationAddition::get_type() const
{
    return OP_SYMBOLS[OP_ADDITION_INDEX];
}

NodeOperationSubtraction::NodeOperationSubtraction(int number_of_children)
    : NodeOperation(number_of_children)
{
}

std::string NodeOperationSubtraction::get_type() const
{
    return OP_SYMBOLS[OP_SUBTRACTION_INDEX];
}

NodeOperationMultiplication::NodeOperationMultiplication(int number_of_children)
    : NodeOperation(number_of_children)
{
}

std::string NodeOperationMultiplication::get_type() const
{
    return OP_SYMBOLS[OP_MULTIPLICATION_INDEX];
}

NodeOperationDivision::NodeOperationDivision(int number_of_children)
    : NodeOperation(number_of_children)
{
}

std::string NodeOperationDivision::get_type() const
{
    return OP_SYMBOLS[OP_DIVISION_INDEX];
}

NodeOperationSin::NodeOperationSin(int number_of_children)
    : NodeOperation(number_of_children)
{
}

std::string NodeOperationSin::get_type() const
{
    return OP_SYMBOLS[OP_SIN_INDEX];
}

NodeOperationCos::NodeOperationCos(int number_of_children)
    : NodeOperation(number_of_children)
{
}

std::string NodeOperationCos::get_type() const
{
    return OP_SYMBOLS[OP_COS_INDEX];
}

float NodeOperationAddition::get_value() const
{
    float result = 0;

    for (int i = 0; i < get_number_of_children(); i++)
    {
        result += get_child(i)->get_value();
    }

    return result;
}

float NodeOperationSubtraction::get_value() const
{
    float result = get_child(0)->get_value();

    for (int i = 1; i < get_number_of_children(); i++)
    {
        result -= get_child(i)->get_value();
    }

    return result;
}

float NodeOperationMultiplication::get_value() const
{
    float result = 1;

    for (int i = 0; i < get_number_of_children(); i++)
    {
        result *= get_child(i)->get_value();
    }

    return result;
}

float NodeOperationDivision::get_value() const
{
    float result = get_child(0)->get_value();

    for (int i = 1; i < get_number_of_children(); i++)
    {
        result /= get_child(i)->get_value();
    }

    return result;
}

float NodeOperationSin::get_value() const
{
    return std::sin(get_child(0)->get_value());
}

float NodeOperationCos::get_value() const
{
    return std::cos(get_child(0)->get_value());
}

NodeVariable::NodeVariable(Variable *var)
    : Node(VARIABLE_NUM_OF_CHILDREN),
    variable_(var)
{
}

Variable *NodeVariable::get_variable() const
{
    return variable_;
}

float NodeVariable::get_value() const
{
    return variable_->get_value();
}

std::string NodeOperation::to_string() const
{
    return get_type();
}

std::string NodeVariable::get_name() const
{
    return variable_->get_name();
}

std::string NodeVariable::to_string() const
{
    return get_name();
}

NodeValue::NodeValue(std::string value)
    : Node(VALUE_NUM_OF_CHILDREN),
    value_(std::atoi(value.c_str())),
    value_string_(value)
{
}

float NodeValue::get_value() const
{
    return value_;
}

std::string NodeValue::to_string() const
{
    return value_string_;
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

std::ostream &operator<<(std::ostream &os, const Node &node)
{
    return os << node.to_string();
}
