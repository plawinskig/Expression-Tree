#pragma once

#include <string>
#include <vector>

namespace
{
	//std::string 
}

class Error
{
public:
	Error(std::string message);

	virtual std::string get_message() const;
	void set_message(std::string message);

private:
	std::string message_;
};

class Errors : public Error
{
public:
	Errors();
	~Errors();

	void add(Error *err);
	bool is_empty();

	virtual std::string get_message() const;

private:
	std::vector<Error *> errors_;
};

class ErrorIncorrectNumberOfArguments : public Error
{
public:
	ErrorIncorrectNumberOfArguments(std::string where, int required, int given);

private:
	std::string where_; 
	int required_; 
	int given_;
};

class ErrorInvalidArgument : public Error
{
public:
	ErrorInvalidArgument(std::string where, std::string what);

private:
	std::string where_;
	std::string what_;
};

class ErrorInvalidCharacter : public Error
{
public:
	ErrorInvalidCharacter(std::string where, char what);

private:
	std::string where_;
	char what_;
};

class ErrorTooManyArguments : public Error
{
public:
	ErrorTooManyArguments(std::string loaded, std::string remained);

private:
	std::string loaded_;
	std::string remained_;
};

class ErrorEmptyInput : public Error
{
public:
	ErrorEmptyInput();
};

class ErrorDivisionByZero : public Error
{
public:
	ErrorDivisionByZero();
};