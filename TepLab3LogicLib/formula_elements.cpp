#include "pch.h"
#include "formula_elements.hpp"

Variable::Variable(std::string name, int value)
	:name_(name),
	value_(value)
{
}

std::string Variable::get_name() const
{
	return name_;
}

int Variable::get_value() const
{
	return value_;
}

void Variable::set_value(int value)
{
	value_ = value;
}
