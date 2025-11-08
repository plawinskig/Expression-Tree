#pragma once

#include <iostream>
#include <string>
#include <map>
#include "node.hpp"

namespace
{
	const std::string FORMULA_REGEX = " ";

	const struct operation
	{
		std::string type;
		int number_of_arguments;

		bool operator==(operation other)
		{
			return type == other.type;
		}
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

	const operation NOT_OPERATION = {"_", 0};

	const std::string ROOT_DATA = "[root]";
	const int ROOT_NUMBER_OF_CHILDREN = 1;

	const char MIN_CONSTANT_DIGIT = '0';
	const char MAX_CONSTANT_DIGIT = '9';

	const char MIN_VARIABLE_SIGN_1 = 'a';
	const char MAX_VARIABLE_SIGN_1 = 'z';
	const char MIN_VARIABLE_SIGN_2 = 'A';
	const char MAX_VARIABLE_SIGN_2 = 'Z';
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
	void load_new_formula_helper(std::string &formula, Node *parent_node);
	Node *load_formula_elem_into_node(std::string formula_elem);
	operation load_operation(std::string formdla_elem);
	bool is_constant(std::string formula_elem);
	bool is_variable(std::string formula_elem);
	void get_formula(Node *node, std::string &formula);

	Node *root_;
	int number_of_nodes_;
};
