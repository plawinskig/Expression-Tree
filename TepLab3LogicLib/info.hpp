#pragma once

#include <string>

class Info
{
public:
	virtual std::string get_message() const = 0;
};

class Error : public Info
{
};

class Warning : public Info
{
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