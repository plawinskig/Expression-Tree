#pragma once

#include <string>

const enum error_code
{
	INCORRECT_NUM_OF_ARGS,
	INCORRECT_ARG,

	ERROR_COUNT,
	NO_ERROR
};

const enum warning_code
{
	PASS,

	WARNING_COUNT,
	NO_WARNING
};

namespace
{
	const std::string ERROR_MESSAGES[ERROR_COUNT] =
	{
		"Error: Incorrect number of arguments",
		"Error: Incorrect argument"
	};

	const std::string WARNING_MESSAGES[WARNING_COUNT] =
	{
		"pass"
	};
}

class Error
{
public:
	Error();
	Error(error_code error_code);

	bool has_occured() const;

	std::string get_message() const;

private:
	error_code code_;
};

class Warning
{
public:
	Warning();
	Warning(warning_code warning_code);

	bool has_occured() const;

	std::string get_message() const;

private:
	warning_code code_;
};
