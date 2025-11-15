#pragma once

#include <string>
#include <vector>
#include <map>

#include "error.hpp"

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
	const int DEFAULT_NUM_OF_CHILDREN = 0;
	const int VALUE_NUM_OF_CHILDREN = 0;
	const int VARIABLE_NUM_OF_CHILDREN = 0;

	const std::string NO_DATA_STRING = "[no data]";
	const std::string DEFAULT_VARIABLE_NAME = "X";
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

	Error load(const std::vector<std::string> nodes, int off_start, int &off_end);
	bool is_nil() const;

	virtual int get_value() const = 0;
	Node *get_parent() const;
	Node *get_child(int child_index) const;
	int get_number_of_children() const;

	bool set_parent(Node *parent);
	bool set_child(Node *child, int child_index);
	bool set_child(Node *child);

	static Node *alloc(std::string node_type);

private:
	static bool is_value(std::string node_type);
	static bool is_variable(std::string node_type);
	static bool is_operation(std::string node_type);
	static std::string skip_invalid_characters(std::string node_type);

	Node *parent_;
	std::vector<Node *> children_;
};

class NodeOperation : public Node
{
public:
	NodeOperation(int number_of_children);

	virtual std::string get_type() const = 0;
	virtual int get_value() const = 0;

	static NodeOperation *make_operation(std::string operation);
};

class NodeOperationAddition : public NodeOperation
{
public:
	NodeOperationAddition(int number_of_children = OP_NUM_OF_ARGS[OP_ADDITION_INDEX]);

	virtual std::string get_type() const;
	virtual int get_value() const;
};

class NodeOperationSubtraction : public NodeOperation
{
public:
	NodeOperationSubtraction(int number_of_children = OP_NUM_OF_ARGS[OP_SUBTRACTION_INDEX]);

	virtual std::string get_type() const;
	virtual int get_value() const;
};

class NodeOperationMultiplication : public NodeOperation
{
public:
	NodeOperationMultiplication(int number_of_children = OP_NUM_OF_ARGS[OP_MULTIPLICATION_INDEX]);

	virtual std::string get_type() const;
	virtual int get_value() const;
};

class NodeOperationDivision : public NodeOperation
{
public:
	NodeOperationDivision(int number_of_children = OP_NUM_OF_ARGS[OP_DIVISION_INDEX]);

	virtual std::string get_type() const;
	virtual int get_value() const;
};

class NodeOperationSin : public NodeOperation
{
public:
	NodeOperationSin(int number_of_children = OP_NUM_OF_ARGS[OP_SIN_INDEX]);

	virtual std::string get_type() const;
	virtual int get_value() const;
};

class NodeOperationCos : public NodeOperation
{
public:
	NodeOperationCos(int number_of_children = OP_NUM_OF_ARGS[OP_COS_INDEX]);

	virtual std::string get_type() const;
	virtual int get_value() const;
};

class NodeVariable : public Node
{
public:
	NodeVariable(std::string name, int value = DEFAULT_VALUE);

	void set_value(int value);
	
	virtual int get_value() const;
	std::string get_name() const;

private:
	std::string name_;
	int value_;
};

class NodeValue : public Node
{
public:
	NodeValue(std::string value);
	NodeValue(int value = DEFAULT_VALUE);

	virtual int get_value() const;

private:
	int value_;
};

std::ostream &operator<<(std::ostream &os, const NodeOperation &node);
std::ostream &operator<<(std::ostream &os, const NodeVariable &node);
std::ostream &operator<<(std::ostream &os, const NodeValue &node);
