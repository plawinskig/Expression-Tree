#include "pch.h"
#include "error.hpp"

#include <sstream>

Error::Error(std::string message)
{
	set_message(message);
}

std::string Error::get_message() const
{
	return message_;
}

void Error::set_message(std::string message)
{
	message_ = message;
}

ErrorIncorrectNumberOfArguments::ErrorIncorrectNumberOfArguments(std::string where, int required, int given)
	: Error(std::string()),
	where_(where),
	required_(required),
	given_(given)
{
	std::stringstream message;
	message << "Incorrect number of arguments in '" << where_ << "'\n";
	message << "Required: " << required_ << "\n";
	message << "Given: " << given_ << "\n";

	set_message(message.str());
}

ErrorInvalidArgument::ErrorInvalidArgument(std::string where, std::string what)
	: Error(std::string()),
	where_(where),
	what_(what)
{
	std::stringstream message;
	message << "Invalid argument '" << what_ << "' in '" << where_ << "'\n";

	set_message(message.str());
}

Errors::Errors()
	: Error(std::string()),
	errors_(std::vector<Error *>())
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

ErrorInvalidCharacter::ErrorInvalidCharacter(std::string where, char what)
	: Error(std::string()),
	where_(where),
	what_(what)
{
	std::stringstream message;
	message << "Character: '";
	message << what_ << "' in '" << where_;
	message << "' is not permitted - omitting\n";

	set_message(message.str());
}

ErrorTooManyArguments::ErrorTooManyArguments(std::string loaded, std::string remained)
	: Error(std::string()),
	loaded_(loaded),
	remained_(remained)
{
	std::stringstream message;
	message << "Too many arguments in formula\n";
	message << loaded_ << remained_ << "\n";
	std::string loaded_offset(loaded_.size() + 1, ' ');
	std::string remained_offset(remained_.size() - 1, '^');
	message << loaded_offset << remained_offset << "\n";

	set_message(message.str());
}

ErrorEmptyInput::ErrorEmptyInput()
	: Error(std::string())
{
	std::stringstream message;
	message << "Empty input provided\n";

	set_message(message.str());
}

ErrorDivisionByZero::ErrorDivisionByZero()
	: Error(std::string())
{
	std::stringstream message;
	message << "Cannot divide by zero\n";

	set_message(message.str());
}
