#pragma once

#include <iostream>
#include <string>
#include "node.hpp"

namespace
{
	const std::string FORMULA_DATA_SEPARATOR = " ";

	const std::string DEFAULT_OPERATIONS_ARRAY[] = {"+", "-", "*", "/", "sin", "cos", "avg3" };
	const int SIZE_OF_OPR_ARR = sizeof(DEFAULT_OPERATIONS_ARRAY) / sizeof(std::string);

	const std::string ROOT_DATA = "[root]";
}

std::string readUserName(std::istream &input, std::ostream &output);

class Tree
{
public:
	Tree(std::string formula);
	Tree(Node *root, int number_of_nodes);

	void load_new_formula(std::string formula);
	std::string get_formula();

private:
	std::string load_formula_operation(std::string::iterator formula_iter);
	bool is_operation(std::string::iterator formula_iter, std::string operation);
	void get_formula(Node *node, std::string &formula);

	Node *root_;
	int number_of_nodes_;
};
