#pragma once

#include <string>

class Error
{
public:
	Error();
	Error(std::string message);

	bool has_occured() const;

private:
	std::string message_;
};