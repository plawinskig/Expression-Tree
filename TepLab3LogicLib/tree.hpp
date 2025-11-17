#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "node.hpp"
#include "error.hpp"
#include "formula_elements.hpp"
#include "string_helpers.hpp"

namespace
{
	const std::string FORMULA_SEPARATOR = " ";
}

class Tree
{
public:
	Tree();
	Tree(std::string formula);

	Tree(const Tree &other);
	~Tree();
	Tree &operator=(const Tree &other);

	Tree operator+(const Tree &other) const;

	// TO DELETE
	Node *get_root();
	// 

	Error *load_new_formula(std::string formula);
	Tree join(const Tree &other) const;
	float calculate_formula() const;

	bool is_empty() const;

	int get_depth() const;
	std::string get_formula_to_string() const;
	std::string get_level_to_string(int level) const;
	std::string get_variables_to_string() const;

	bool set_variables(const std::vector<int> &variables);

private:
	void clear_variables();

	void get_formula_to_string(Node *node, std::string &result) const;
	void get_level_to_string(Node *node, std::string &result, int level) const;

	Node *root_;
	std::vector<Variable *> variables_;
};

void print_tree_by_levels(Tree &tree);
