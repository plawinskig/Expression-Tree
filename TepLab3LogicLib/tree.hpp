#pragma once

#include <iostream>
#include <string>
#include "node.hpp"

std::string readUserName(std::istream &input, std::ostream &output);

class Tree
{
public:
	Tree(Node *root, int number_of_nodes);

	std::string get_formula();

private:
	Node *root_;
	int number_of_nodes_;
};
