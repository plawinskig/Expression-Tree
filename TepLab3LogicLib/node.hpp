#pragma once

#include <string>

namespace
{
	const std::string NO_DATA_STRING = "[no data]";
}

class Node
{
public:
	Node(Node *parent, Node *child = nullptr, Node *sibling = nullptr);

	Node *get_parent();
	Node *get_child();
	Node *get_sibling();
	std::string get_data();

	void set_parent(Node *parent);
	void set_child(Node *child);
	void set_sibling(Node *sibling);
	void set_data(std::string data);

private:
	Node *parent_;
	Node *child_;
	Node *sibling_;
	std::string data_;
};