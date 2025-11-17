#pragma once

#include <string>

const enum code
{
	NO_ERROR,
	INCORRECT_NUM_OF_ARGS,
	INCORRECT_ARG
};

namespace
{
	const std::map<code, std::string> MESSAGES =
	{
		{
			code::INCORRECT_NUM_OF_ARGS,
			"Incorrect number of arguments"
		},
		{
			code::INCORRECT_ARG,
			"Incorrect argument"
		},
	};
}

class Error
{
public:
	Error();
	Error(code code);

	bool has_occured() const;

	std::string get_message() const;

private:
	code code_;
};