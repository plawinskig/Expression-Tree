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
	Node(std::string data, int number_of_children);
	~Node();

	bool is_nil() const;

	Node **get_children() const;
	Node *get_child(int child_index) const;
	int get_number_of_children() const;
	std::string get_data() const;

	bool set_child(Node *child, int child_index);
	bool set_data(std::string data);

private:
	int number_of_children_;
	Node **children_array_;
	std::string data_;
};

std::ostream &operator<<(std::ostream &os, const Node *node);
std::ostream &operator<<(std::ostream &os, const Node &node);
