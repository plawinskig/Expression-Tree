#pragma once

#include <string>

class Node
{
public:
	Node *get_parent();
	Node *get_child();
	Node *get_sibling();
	std::string get_data();

private:
	Node *parent_;
	Node *child_;
	Node *sibling_;
	std::string data_;
};