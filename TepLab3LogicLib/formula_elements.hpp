#pragma once

#include <string>

namespace
{
	const std::string DEFAULT_VARIABLE_NAME = "var";
	const int DEFAULT_VALUE = 1;
}

class Variable
{
public:
	Variable(std::string name = DEFAULT_VARIABLE_NAME, int value = DEFAULT_VALUE);

	std::string get_name() const;
	int get_value() const;

	void set_value(int value);

private:
	std::string name_;
	int value_;
};