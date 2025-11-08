#pragma once

#include <iostream>
#include <string>
#include "node.hpp"

namespace
{
	const std::string FORMULA_DATA_SEPARATOR = " ";
	const std::string DEFAULT_FUNCTIONS_ARRAY[] = {"sin", "cos", "avg"};
}

std::string readUserName(std::istream &input, std::ostream &output);

class Tree
{
public:
	Tree(std::string formula);
	Tree(Node *root, int number_of_nodes);

	void load_formula(std::string formula);
	std::string get_formula();

private:
	void get_formula(Node *node, std::string &formula);

	Node *root_;
	int number_of_nodes_;
};
