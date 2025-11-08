#include "pch.h"
#include "node.hpp"

Node::Node()
	:number_of_children_(0),
	children_array_(nullptr),
	data_(NO_DATA_STRING)
{
}

Node::Node(std::string data, int number_of_children)
	:number_of_children_(number_of_children),
	children_array_(new Node * [number_of_children]),
	data_(data)
{
}

Node::~Node()
{
	delete[] children_array_;
}

bool Node::is_nil() const
{
	return children_array_ == nullptr;
}

Node **Node::get_children() const
{
	return children_array_;
}

Node *Node::get_child(int child_index) const
{
	if (child_index < 0 || child_index >= number_of_children_)
	{
		std::cerr << "Node " << data_ << " child index " << child_index << " out of bounds of " << number_of_children_ << "\n";
		return nullptr;
	}

	return children_array_[child_index];
}

int Node::get_number_of_children() const
{
	return number_of_children_;
}

std::string Node::get_data() const
{
	return data_;
}

bool Node::set_child(Node *child, int child_index)
{
	if (child_index < 0 || child_index > number_of_children_)
	{
		return false;
	}

	if (child_index == number_of_children_)
	{
		if (children_array_ == nullptr)
		{
			if (number_of_children_ != 0)
			{
				std::cerr << "Node " << data_ << " children array is nullptr and number of children is not zero\n";
				return false;
			}

			number_of_children_ = 1;
			children_array_ = new Node * [number_of_children_];
			children_array_[child_index] = child;

			return true;
		}

		Node **new_children_ = new Node * [number_of_children_ + 1];

		for (int i = 0; i < number_of_children_; i++)
		{
			new_children_[i] = children_array_[i];
		}

		new_children_[child_index] = child;
		number_of_children_++;
		
		delete[] children_array_;
		children_array_ = new_children_;

		return true;
	}

	children_array_[child_index] = child;

	return true;
}

bool Node::set_data(std::string data)
{
	data_ = data;
	return true;
}

std::ostream &operator<<(std::ostream &os, const Node *node)
{
	return os << node->get_data();
}

std::ostream &operator<<(std::ostream &os, const Node &node)
{
	return os << node.get_data();
}
