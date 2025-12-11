#pragma once

#include <string>
#include <vector>
#include <map>

#include "error.hpp"
#include "formula_elements.hpp"

namespace
{
	const int DEFAULT_NUM_OF_CHILDREN = 0;
	const int VALUE_NUM_OF_CHILDREN = 0;
	const int VARIABLE_NUM_OF_CHILDREN = 0;

	const int INT_BUFFER_SIZE = 20;

	const std::string NO_DATA_STRING = "[no data]";
	const std::string DEFAULT_VALUE_STRING = "1";
	const int VALUE_BASE = 10;

	const enum
	{
		OP_ADDITION_INDEX,
		OP_SUBTRACTION_INDEX,
		OP_MULTIPLICATION_INDEX,
		OP_DIVISION_INDEX,
		OP_SIN_INDEX,
		OP_COS_INDEX,
		OP_COUNT
	};

	static const char *OP_SYMBOLS[OP_COUNT] = { "+", "-", "*", "/", "sin", "cos" };
	static const int OP_NUM_OF_ARGS[OP_COUNT] = { 2, 2, 2, 2, 1, 1 };
}

class Node
{
public:
	Node(int number_of_children = DEFAULT_NUM_OF_CHILDREN);

	Node(const Node &) = delete;
	Node &operator=(const Node &) = delete;
	virtual ~Node();

	virtual Node *clone() const = 0;

	Errors *load(const std::vector<std::string> nodes, int off_start, int &off_end);
	bool is_nil() const;

	virtual float get_value() const = 0;
	Node *get_parent() const;
	Node *get_child(int child_index) const;
	Node *get_last_child() const;
	Node *get_last_leaf();
	int get_number_of_children() const;
	int get_level() const;
	int get_depth() const;
	void get_variables(std::vector<Variable *> &variables);

	bool set_parent(Node *parent);
	bool set_child(Node *child, int child_index);
	bool set_last_child(Node *child);
	bool add_last_child(Node *child);
	
	virtual std::string to_string() const = 0;

	static Node *alloc(std::string node_type);
	static Errors *skip_invalid_characters(std::string &node_type);
	static bool is_value(std::string node_type);
	static bool is_variable(std::string node_type);
	static bool is_operation(std::string node_type);

private:
	Node *parent_;
	std::vector<Node *> children_;
};

class NodeVariable : public Node
{
public:
	NodeVariable(Variable *var);

	virtual Node *clone() const;

	Variable *get_variable() const;
	virtual float get_value() const;
	std::string get_name() const;

	void set_variable(Variable *var);
	void set_value(int value);

	virtual std::string to_string() const;

private:
	Variable *variable_;
};

class NodeValue : public Node
{
public:
	NodeValue(std::string value = DEFAULT_VALUE_STRING);

	virtual Node *clone() const;

	virtual float get_value() const;

	virtual std::string to_string() const;

private:
	std::string value_string_;
	int value_;
};

class NodeOperation : public Node
{
public:
	NodeOperation(int number_of_children);

	virtual Node *clone() const = 0;

	virtual std::string get_type() const = 0;
	virtual float get_value() const = 0;

	virtual std::string to_string() const;

	static NodeOperation *make_operation(std::string operation);
};

class NodeOperationAddition : public NodeOperation
{
public:
	NodeOperationAddition(int number_of_children = OP_NUM_OF_ARGS[OP_ADDITION_INDEX]);

	virtual Node *clone() const;

	virtual std::string get_type() const;
	virtual float get_value() const;
};

class NodeOperationSubtraction : public NodeOperation
{
public:
	NodeOperationSubtraction(int number_of_children = OP_NUM_OF_ARGS[OP_SUBTRACTION_INDEX]);

	virtual Node *clone() const;

	virtual std::string get_type() const;
	virtual float get_value() const;
};

class NodeOperationMultiplication : public NodeOperation
{
public:
	NodeOperationMultiplication(int number_of_children = OP_NUM_OF_ARGS[OP_MULTIPLICATION_INDEX]);

	virtual Node *clone() const;

	virtual std::string get_type() const;
	virtual float get_value() const;
};

class NodeOperationDivision : public NodeOperation
{
public:
	NodeOperationDivision(int number_of_children = OP_NUM_OF_ARGS[OP_DIVISION_INDEX]);

	virtual Node *clone() const;

	virtual std::string get_type() const;
	virtual float get_value() const;
};

class NodeOperationSin : public NodeOperation
{
public:
	NodeOperationSin(int number_of_children = OP_NUM_OF_ARGS[OP_SIN_INDEX]);

	virtual Node *clone() const;

	virtual std::string get_type() const;
	virtual float get_value() const;
};

class NodeOperationCos : public NodeOperation
{
public:
	NodeOperationCos(int number_of_children = OP_NUM_OF_ARGS[OP_COS_INDEX]);

	virtual Node *clone() const;

	virtual std::string get_type() const;
	virtual float get_value() const;
};

std::ostream &operator<<(std::ostream &os, const Node &node);
