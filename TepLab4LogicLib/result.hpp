#pragma once

#include <vector>
#include <iostream>
#include <string>

template <typename T, typename E>
class Result
{
public:
	Result(const T &value);
	Result(E *error);
	Result(std::vector<E *> &errors);

	Result(const Result<T, E> &other);
	~Result();
	Result<T, E> &operator=(const Result<T, E> &other);

	bool is_success() const;

	T get_value() const;
	std::vector<E *> &get_errors() const;

	static Result<T, E> ok(const T &value);
	static Result<T, E> fail(E *error);
	static Result<T, E> fail(std::vector<E *> &errors);

private:
	T *value_;
	std::vector<E *> errors_;
};

template<typename T, typename E>
inline Result<T, E>::Result(const T &value)
	: value_(&value),
	errors_(std::vector<E *>())
{
}

template<typename T, typename E>
inline Result<T, E>::Result(E *error)
	: value_(nullptr),
	errors_(std::vector<E *>(1, error))
{
}

template<typename T, typename E>
inline Result<T, E>::Result(std::vector<E *> &errors)
	: value_(nullptr),
	errors_(std::vector<E *>(errors))
{
}

template<typename T, typename E>
inline Result<T, E>::Result(const Result<T, E> &other)
	: value_(other.value_),
	errors_(other.errors_)
{
}

template<typename T, typename E>
inline Result<T, E>::~Result()
{
	delete value_;
	for (typename std::vector<E *>::const_iterator it = errors_.begin(); it != errors_.end(); it++)
	{
		delete *it;
	}
}

template<typename T, typename E>
inline Result<T, E> &Result<T, E>::operator=(const Result<T, E> &other)
{
	return Result<T, E>(other);
}

template<typename T, typename E>
inline bool Result<T, E>::is_success() const
{
	return !errors_.empty();
}

template<typename T, typename E>
inline T Result<T, E>::get_value() const
{
	return value_;
}

template<typename T, typename E>
inline std::vector<E *> &Result<T, E>::get_errors() const
{
	return errors_;
}

template<typename T, typename E>
inline Result<T, E> Result<T, E>::ok(const T &value)
{
	return Result<T, E>(value);
}

template<typename T, typename E>
inline Result<T, E> Result<T, E>::fail(E *error)
{
	return Result<T, E>(error);
}

template<typename T, typename E>
inline Result<T, E> Result<T, E>::fail(std::vector<E *> &errors)
{
	return Result<T, E>(errors);
}
