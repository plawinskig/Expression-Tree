#pragma once

#include <string>

class Error
{
public:
	virtual std::string get_message() const = 0;
};

class ErrorIncorrectNumberOfArguments : public Error
{
public:
	ErrorIncorrectNumberOfArguments(std::string where, int required, int given);

	virtual std::string get_message() const;

private:
	std::string where_; 
	int required_; 
	int given_;
};

class ErrorInvalidArgument : public Error
{
public:
	ErrorInvalidArgument(std::string where, std::string what);

	virtual std::string get_message() const;

private:
	std::string where_;
	std::string what_;
};