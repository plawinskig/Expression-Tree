#include "pch.h"
#include "error.hpp"

Error::Error()
	: code_(code::NO_ERROR)
{
}

Error::Error(code code)
	: code_(code)
{
}

bool Error::has_occured() const
{
	return code_ != code::NO_ERROR;
}

std::string Error::get_message() const
{
	return MESSAGES.at(code_);
}
