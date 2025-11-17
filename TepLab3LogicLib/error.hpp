#pragma once

#include <string>

class Error
{
public:
	virtual std::string get_message() const = 0;
};

class Errors : public Error
{
public:
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

class ErrorInvalidCharacter : public Error
{
public:
	ErrorInvalidCharacter(std::string where, char what);

	virtual std::string get_message() const;

private:
	std::string where_;
	char what_;
};
