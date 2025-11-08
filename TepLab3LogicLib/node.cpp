#include "pch.h"
#include "node.hpp"

Node::Node()
	:child_(nullptr),
	sibling_(nullptr),
	data_(NO_DATA_STRING)
{
}

Node::Node(std::string data)
	:child_(nullptr),
	sibling_(nullptr),
	data_(data)
{
}

Node::Node(Node *parent, Node *child, Node *sibling)
	:child_(child),
	sibling_(sibling),
	data_(NO_DATA_STRING)
{
}

Node::~Node()
{

}

bool Node::is_nil()
{
	return child_ == nullptr && sibling_ == nullptr;
}

Node *Node::get_child()
{
	return child_;
}

Node *Node::get_sibling()
{
	return sibling_;
}

std::string Node::get_data()
{
	return data_;
}

void Node::set_child(Node *child)
{
	child_ = child;
}

void Node::set_sibling(Node *sibling)
{
	sibling_ = sibling;
}

void Node::set_data(std::string data)
{
	data_ = data;
}

