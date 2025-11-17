#include "pch.h"
#include "info.hpp"

#include <sstream>

ErrorIncorrectNumberOfArguments::ErrorIncorrectNumberOfArguments(std::string where, int required, int given)
	: where_(where),
	required_(required),
	given_(given)
{
}

std::string ErrorIncorrectNumberOfArguments::get_message() const
{
	std::stringstream message;
	message << "Incorrect number of arguments in '" << where_ << "'\n";
	message << "Required: " << required_ << "\n";
	message << "Given: " << given_ << "\n";
	return message.str();
}