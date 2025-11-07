#include "pch.h"
#include "node.hpp"

Node *Node::get_parent()
{
	return parent_;
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
