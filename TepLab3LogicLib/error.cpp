#include "pch.h"
#include "error.hpp"

Error::Error()
	:message_(std::string())
{
}

Error::Error(std::string message)
	:message_(message)
{
}

bool Error::has_occured() const
{
	return !message_.empty();
}

std::string Error::get_message() const
{
	return message_;
}
