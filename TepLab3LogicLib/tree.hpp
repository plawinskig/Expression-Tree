#pragma once

#include <iostream>
#include <string>
#include <iostream>
#include "node.hpp"



namespace
{
	const std::string FORMULA_SEPARATOR = " ";
}

class Tree
{
public:
	Tree(std::string formula);

	void load_new_formula(std::string formula);

	std::string get_formula() const;

	static std::vector<std::string> split(std::string formula, std::string regex = FORMULA_SEPARATOR);

private:
	void get_formula(Node *node, std::string &result) const;

	Node *root_;
};
