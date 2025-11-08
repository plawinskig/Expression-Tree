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

	const operation NOT_OPERATION = {" ", 0};

	const char WHITESPACE_CHARS[] = {' ', '\t', '\n'};
	const int SIZE_OF_WHITESPACE_CHARS = sizeof(WHITESPACE_CHARS) / sizeof(*WHITESPACE_CHARS);

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
	void load_new_formula(std::string::iterator &formula_iter, Node *parent_node);
	operation load_formula_operation(std::string::iterator formdla_iter);
	bool is_operation(std::string::iterator formula_iter, operation &operation);
	bool is_whitespace(std::string::iterator formula_iter);
	bool is_constant(std::string::iterator formula_iter);
	bool is_variable(std::string::iterator formula_iter);
	void get_formula(Node *node, std::string &formula);

	Node *root_;
	int number_of_nodes_;
};
