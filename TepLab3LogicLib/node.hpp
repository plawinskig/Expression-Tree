#pragma once

#include <string>

namespace
{
	const std::string NO_DATA_STRING = "[no data]";
}

class Node
{
public:
	Node();
	Node(std::string data);
	Node(Node *up, Node *child = nullptr, Node *sibling = nullptr);
	~Node();

	bool is_nil();

	Node *get_parent();
	Node *get_child();
	Node *get_sibling();
	std::string get_data();

	void set_up_node(Node *up);
	void set_child(Node *child);
	void set_sibling(Node *sibling);
	void set_data(std::string data);

private:
	Node *child_;
	Node *sibling_;
	std::string data_;
};