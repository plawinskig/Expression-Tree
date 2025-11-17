#include "pch.h"
#include "error.hpp"

Error::Error()
	: code_(error_code::NO_ERROR)
{
}

Error::Error(error_code error_code)
	: code_(error_code)
{
}

Warning::Warning()
	: code_(warning_code::NO_WARNING)
{
}

Warning::Warning(warning_code warning_code)
	: code_(warning_code)
{
}

bool Error::has_occured() const
{
	return code_ != error_code::NO_ERROR;
}

bool Warning::has_occured() const
{
	return code_ != warning_code::NO_WARNING;
}

std::string Error::get_message() const
{
	return ERROR_MESSAGES[code_];
}

std::string Warning::get_message() const
{
	return WARNING_MESSAGES[code_];
}
