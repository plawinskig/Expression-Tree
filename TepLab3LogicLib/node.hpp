#pragma once

#include <string>
#include <vector>

namespace
{
	const std::string NO_DATA_STRING = "[no data]";
}

class Node
{
public:
	//Node();
	//Node(std::string data, int number_of_children);
	//~Node();

	bool is_nil() const;

	Node *get_child(int child_index) const;
	int get_number_of_children() const;

	bool set_child(Node *child, int child_index);
	bool set_child(Node *child);

private:
	Node *parent;
	std::vector<Node *> children_;
};

std::ostream &operator<<(std::ostream &os, const Node *node);
std::ostream &operator<<(std::ostream &os, const Node &node);
