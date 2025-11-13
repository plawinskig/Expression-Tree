#pragma once

#include <iostream>
#include <string>
#include "node.hpp"

#define ENABLE_DEBUGGING 0

#if ENABLE_DEBUGGING
#define LOG_DEBUG(message) (std::cout << message << "\n")
#else
#define LOG_DEBUG(message) ((void)0)
#endif


#define ENABLE_WARNINGS 0

#if ENABLE_WARNINGS
#define LOG_WARN(message) (std::cout << "[WARNING] " << message << "\n")
#else
#define LOG_WARN(message) ((void)0)
#endif

namespace
{
	const std::string FORMULA_REGEX = " ";

	const std::string ROOT_DATA = "[root]";
	const int ROOT_NUMBER_OF_CHILDREN = 1;

	const char MIN_DIGIT = '0';
	const char MAX_DIGIT = '9';

	const char MIN_VARIABLE_LOWER = 'a';
	const char MAX_VARIABLE_LOWER = 'z';
	const char MIN_VARIABLE_UPPER = 'A';
	const char MAX_VARIABLE_UPPER = 'Z';

	const std::string DEFAULT_VARIABLE_NAME = "X";
	const std::string DEFAULT_CONSTANT = "1";
}

class Tree
{
public:
	Tree(std::string formula);
	Tree(Node *root, int number_of_nodes);

	void load_new_formula(std::string formula);

	std::string get_formula();

private:
	Node *root_;
	int number_of_nodes_;
};
