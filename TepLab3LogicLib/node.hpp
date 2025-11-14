#pragma once

#include <string>
#include <vector>

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
	const std::string DEFAULT_CONSTANT = "1";
}

class Node
{
public:
	//Node();
	//Node(std::string data, int number_of_children);
	//~Node();

	Error load(const std::vector<std::string> &nodes, int off_start, int &off_end);
	bool is_nil() const;

	Node *get_child(int child_index) const;
	int get_number_of_children() const;

	bool set_child(Node *child, int child_index);
	bool set_child(Node *child);

	static Node *alloc(std::string node_type);

private:

	static bool is_value(std::string node_type);
	static bool is_variable(std::string node_type);
	static std::string skip_invalid_characters(std::string node_type);

	Node *parent;
	std::vector<Node *> children_;
};

class NodeOperation : public Node
{
public:

private:

};

class NodeVariable : public Node
{
public:

private:

};

class NodeValue : public Node
{
public:

private:

};

std::ostream &operator<<(std::ostream &os, const Node *node);
std::ostream &operator<<(std::ostream &os, const Node &node);
