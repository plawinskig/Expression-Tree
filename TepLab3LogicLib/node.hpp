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
	virtual ~Node();

	Error load(const std::vector<std::string> nodes, int off_start, int &off_end);
	bool is_nil() const;

	virtual int get_value() = 0;
	
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
	//virtual std::string get_type() = 0;

	static NodeOperation *make_operation(std::string operation);
};

class NodeOperationAddition : public NodeOperation
{
public:
	virtual int get_value();
};

class NodeOperationSubtraction : public NodeOperation
{
public:
	virtual int get_value();
};

class NodeOperationMultiplication : public NodeOperation
{
public:
	virtual int get_value();
};

class NodeOperationDivision : public NodeOperation
{
public:
	virtual int get_value();
};

class NodeOperationSin : public NodeOperation
{
public:
	virtual int get_value();
};

class NodeOperationCos : public NodeOperation
{
public:
	virtual int get_value();
};

class NodeVariable : public Node
{
public:
	NodeVariable(std::string name, int value = DEFAULT_VALUE);

	void set_value(int value);
	
	virtual int get_value();
	std::string get_name();

private:
	std::string name_;
	int value_;
};

class NodeValue : public Node
{
public:
	NodeValue(std::string value);
	NodeValue(int value = DEFAULT_VALUE);

	virtual int get_value();

private:
	int value_;
};

std::ostream &operator<<(std::ostream &os, const Node *node);
std::ostream &operator<<(std::ostream &os, const Node &node);
