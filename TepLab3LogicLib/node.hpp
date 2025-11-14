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

	const std::map<std::string, int> DEFAULT_OPERATIONS =
	{
		// type, number of input vars/vals
		{"+", 2},
		{"-", 2},
		{"*", 2},
		{"/", 2},
		{"sin", 1},
		{"cos", 1},
		//{"avg3", 3}
	};
}

class Node
{
public:
	virtual ~Node();

	Error load(const std::vector<std::string> &nodes, int off_start, int &off_end);
	bool is_nil() const;

	virtual int get_value() = 0;

	Node *get_child(int child_index) const;
	int get_number_of_children() const;

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
