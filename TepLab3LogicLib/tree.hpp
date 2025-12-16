#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "node.hpp"
#include "error.hpp"
#include "formula_elements.hpp"
#include "string_helpers.hpp"
#include "result.hpp"

namespace
{
	const std::string FORMULA_SEPARATOR = " ";
	const std::string EMPTY_FORMULA_STRING = "[empty]";
	const std::string SET_VARIABLES_COMMAND = "comp";
}

class Tree
{
public:
	Tree();
	Tree(std::string formula);

	Tree(const Tree &other);
	Tree(Tree &&other) noexcept;
	~Tree();
	Tree &operator=(const Tree &other);
	Tree &operator=(Tree &&other) noexcept;

	Tree operator+(const Tree &other) const;

	Error *load_new_formula(std::string formula);
	Tree join(const Tree &other) const;
	float calculate_formula() const;

	bool is_empty() const;

	int get_depth() const;
	int get_number_of_variables() const;
	std::string get_formula_to_string() const;
	std::string get_level_to_string(int level) const;
	std::string get_levels_to_string() const;
	std::string get_variables_to_string() const;

	Error *set_variables(const std::vector<int> &variables);

	static Result<Tree *, Error> get_tree(const std::string &arg);

private:
	void move_tree(Tree &&other);
	void copy_tree(const Tree &other);

	void clear_variables();

	void get_formula_to_string(Node *node, std::string &result) const;
	void get_level_to_string(Node *node, std::string &result, int level) const;

	Node *root_;
	std::vector<Variable *> variables_;
};
