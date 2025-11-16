#pragma once

#include <string>
#include <vector>
#include <map>

#include "error.hpp"

#define ENABLE_DEBUGGING 1

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
	const int DEFAULT_NUM_OF_CHILDREN = 0;
	const int VALUE_NUM_OF_CHILDREN = 0;
	const int VARIABLE_NUM_OF_CHILDREN = 0;

	const int INT_BUFFER_SIZE = 20;

	const std::string NO_DATA_STRING = "[no data]";
	const std::string DEFAULT_VARIABLE_NAME = "X";
	const std::string DEFAULT_VALUE_STRING = "1";
	const int DEFAULT_VALUE = 1;
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
	virtual ~Node();

	Error load(const std::vector<std::string> nodes, int &off_end);
	bool is_nil() const;

	virtual float get_value() const = 0;
	Node *get_parent() const;
	Node *get_child(int child_index) const;
	Node *get_last_child() const;
	Node *get_last_leaf();
	int get_number_of_children() const;
	int get_level() const;
	int get_depth() const;
	std::vector<NodeVariable *> get_variables();

	bool set_parent(Node *parent);
	bool set_child(Node *child, int child_index);
	bool set_last_child(Node *child);
	bool add_last_child(Node *child);
	
	virtual std::string to_string() const = 0;

	static Node *alloc(std::string node_type);

private:
	static bool is_value(std::string node_type);
	static bool is_variable(std::string node_type);
	static bool is_operation(std::string node_type);
	static std::string skip_invalid_characters(std::string node_type);

	Node *parent_;
	std::vector<Node *> children_;
};

class NodeVariable : public Node
{
public:
	NodeVariable(std::string name, int value = DEFAULT_VALUE);

	void set_value(int value);

	virtual float get_value() const;
	std::string get_name() const;

	virtual std::string to_string() const;

private:
	std::string name_;
	int value_;
};

class NodeValue : public Node
{
public:
	NodeValue(std::string value = DEFAULT_VALUE_STRING);

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

	virtual std::string get_type() const = 0;
	virtual float get_value() const = 0;

	virtual std::string to_string() const;

	static NodeOperation *make_operation(std::string operation);
};

class NodeOperationAddition : public NodeOperation
{
public:
	NodeOperationAddition(int number_of_children = OP_NUM_OF_ARGS[OP_ADDITION_INDEX]);

	virtual std::string get_type() const;
	virtual float get_value() const;
};

class NodeOperationSubtraction : public NodeOperation
{
public:
	NodeOperationSubtraction(int number_of_children = OP_NUM_OF_ARGS[OP_SUBTRACTION_INDEX]);

	virtual std::string get_type() const;
	virtual float get_value() const;
};

class NodeOperationMultiplication : public NodeOperation
{
public:
	NodeOperationMultiplication(int number_of_children = OP_NUM_OF_ARGS[OP_MULTIPLICATION_INDEX]);

	virtual std::string get_type() const;
	virtual float get_value() const;
};

class NodeOperationDivision : public NodeOperation
{
public:
	NodeOperationDivision(int number_of_children = OP_NUM_OF_ARGS[OP_DIVISION_INDEX]);

	virtual std::string get_type() const;
	virtual float get_value() const;
};

class NodeOperationSin : public NodeOperation
{
public:
	NodeOperationSin(int number_of_children = OP_NUM_OF_ARGS[OP_SIN_INDEX]);

	virtual std::string get_type() const;
	virtual float get_value() const;
};

class NodeOperationCos : public NodeOperation
{
public:
	NodeOperationCos(int number_of_children = OP_NUM_OF_ARGS[OP_COS_INDEX]);

	virtual std::string get_type() const;
	virtual float get_value() const;
};

std::ostream &operator<<(std::ostream &os, const Node &node);
