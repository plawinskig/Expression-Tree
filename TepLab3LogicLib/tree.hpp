#pragma once

#include <iostream>
#include <string>
#include "node.hpp"



namespace
{
	const std::string FORMULA_SEPARATOR = " ";
}

class Tree
{
public:
	Tree(std::string formula);
	Tree(Node *root, int number_of_nodes);

	void load_new_formula(std::string formula);

	std::string get_formula();

	static std::vector<std::string> split(std::string formula, std::string regex = FORMULA_SEPARATOR);

private:
	Node *root_;
	int number_of_nodes_;
};
