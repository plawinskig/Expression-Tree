#pragma once

#include <iostream>
#include <string>
#include "node.hpp"

namespace
{
	std::string FORMULA_DATA_SEPARATOR = " ";
}

std::string readUserName(std::istream &input, std::ostream &output);

class Tree
{
public:
	Tree(Node *root, int number_of_nodes);

	std::string get_formula();

private:
	void get_formula(Node *node, std::string &formula);

	Node *root_;
	int number_of_nodes_;
};
