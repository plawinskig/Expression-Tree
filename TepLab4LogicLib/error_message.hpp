#pragma once

#include <string>

class ErrorMessage
{
public:
	ErrorMessage(std::string message);
	
	std::string get_message() const;

private:
	std::string message_;
};