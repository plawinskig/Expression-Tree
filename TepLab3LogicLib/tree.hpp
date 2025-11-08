#pragma once

#include <iostream>
#include <string>
#include <map>
#include "node.hpp"

namespace
{
	const std::string FORMULA_DATA_SEPARATOR = " ";

	const struct operation
	{
		std::string type;
		int number_of_arguments;
	};

	const operation DEFAULT_OPERATIONS_ARRAY[] = 
	{
		{"+", 2},
		{"-", 2},
		{"*", 2},
		{"/", 2},
		{"sin", 1},
		{"cos", 1},
		{"avg3", 3}
	};
	const int SIZE_OF_OPR_ARR = sizeof(DEFAULT_OPERATIONS_ARRAY) / sizeof(*DEFAULT_OPERATIONS_ARRAY);

	const std::string ROOT_DATA = "[root]";
	const int ROOT_NUMBER_OF_CHILDREN = 1;
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
	operation load_formula_operation(std::string::iterator formula_iter);
	bool is_operation(std::string::iterator formula_iter, operation &operation);
	void get_formula(Node *node, std::string &formula);

	Node *root_;
	int number_of_nodes_;
};
