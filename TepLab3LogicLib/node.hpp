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

	bool is_nil();

	Node **get_children();
	Node *get_child(int child_index);
	int get_number_of_children();
	std::string get_data();

	bool set_child(Node *child, int child_index);
	bool set_data(std::string data);

private:
	int number_of_children_;
	Node **children_array_;
	std::string data_;
};