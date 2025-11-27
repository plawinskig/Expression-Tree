#include "pch.h"
#include "error.hpp"

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

ErrorInvalidArgument::ErrorInvalidArgument(std::string where, std::string what)
	: where_(where),
	what_(what)
{
}

Errors::~Errors()
{
	for (std::vector<Error *>::const_iterator it = errors_.begin(); it != errors_.end(); it++)
	{
		delete *it;
	}
}

void Errors::add(Error *err)
{
	if (err)
	{
		errors_.push_back(err);
	}
}

bool Errors::is_empty()
{
	return errors_.empty();
}

std::string Errors::get_message() const
{
	std::string messages;

	for (std::vector<Error *>::const_iterator it = errors_.begin(); it != errors_.end(); it++)
	{
		messages += (*it)->get_message();
	}

	return messages;
}

std::string ErrorInvalidArgument::get_message() const
{
	std::stringstream message;
	message << "Invalid argument '" << what_ << "' in '" << where_ << "'\n";
	return message.str();
}

ErrorInvalidCharacter::ErrorInvalidCharacter(std::string where, char what)
	: where_(where),
	what_(what)
{
}

std::string ErrorInvalidCharacter::get_message() const
{
	std::stringstream message;
	message << "Character: '";
	message << what_ << "' in '" << where_;
	message << "' is not permitted - omitting\n";

	return message.str();
}

ErrorTooManyArguments::ErrorTooManyArguments(std::string loaded, std::string remained)
	: loaded_(loaded),
	remained_(remained)
{
}

std::string ErrorTooManyArguments::get_message() const
{
	std::stringstream message;
	message << "Too many arguments in formula\n";
	message << loaded_ << remained_ << "\n";
	std::string loaded_offset(loaded_.size() + 1, ' ');
	std::string remained_offset(remained_.size() - 1, '^');
	message << loaded_offset << remained_offset << "\n";

	return message.str();
}

std::string ErrorEmptyInput::get_message() const
{
	std::stringstream message;
	message << "Empty input provided\n";

	return message.str();
}

std::string ErrorDivisionByZero::get_message() const
{
	std::stringstream message;
	message << "Cannot divide by zero\n";

	return message.str();
}
