#pragma once

#include <vector>
#include <iostream>
#include <string>

template<typename E>
void delete_errors(const std::vector<E *> &errors)
{
	for (typename std::vector<E *>::const_iterator it = errors.begin(); it != errors.end(); it++)
	{
		delete *it;
	}
}

template<typename E>
void copy_errors(const std::vector<E *> &from_errors, std::vector<E *> &to_errors)
{
	delete_errors(to_errors);

	to_errors.clear();

	for (typename std::vector<E *>::const_iterator it = from_errors.begin(); it != from_errors.end(); it++)
	{
		to_errors.push_back(new E(*(*it)));
	}
}

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
	std::vector<E *> &get_errors();

	static Result<T, E> ok(const T &value);
	static Result<T, E> fail(E *error);
	static Result<T, E> fail(std::vector<E *> &errors);

private:
	T *value_;
	std::vector<E *> errors_;
};

template <typename E>
class Result<void, E>
{
public:
	Result();
	Result(E *error);
	Result(std::vector<E *> &errors);

	Result(const Result<void, E> &other);
	~Result();
	Result<void, E> &operator=(const Result<void, E> &other);

	bool is_success() const;

	std::vector<E *> &get_errors();

	static Result<void, E> ok();
	static Result<void, E> fail(E *error);
	static Result<void, E> fail(std::vector<E *> &errors);

private:
	std::vector<E *> errors_;
};


template<typename T, typename E>
inline Result<T, E>::Result(const T &value)
	: value_(new T(value)),
	errors_(std::vector<E *>())
{
}

template<typename E>
inline Result<void, E>::Result()
	: errors_(std::vector<E *>())
{
}

template<typename T, typename E>
inline Result<T, E>::Result(E *error)
	: value_(nullptr),
	errors_(std::vector<E *>(1, error))
{
}

template<typename E>
inline Result<void, E>::Result(E *error)
	: errors_(std::vector<E *>(1, error))
{
}

template<typename T, typename E>
inline Result<T, E>::Result(std::vector<E *> &errors)
	: value_(nullptr),
	errors_(std::vector<E *>())
{
	copy_errors(errors, errors_);
}

template<typename E>
inline Result<void, E>::Result(std::vector<E *> &errors)
	: errors_(std::vector<E *>())
{
	copy_errors(errors, errors_);
}

template<typename T, typename E>
inline Result<T, E>::Result(const Result<T, E> &other)
	: value_(nullptr),
	errors_(std::vector<E *>())
{
	if (other.value_)
	{
		value_ = new T(*(other.value_));
	}
	copy_errors(other.errors_, errors_);
}

template<typename E>
inline Result<void, E>::Result(const Result<void, E> &other)
	: errors_(std::vector<E *>())
{
	copy_errors(other.errors_, errors_);
}

template<typename T, typename E>
inline Result<T, E>::~Result()
{
	delete value_;
	delete_errors(errors_);
}

template<typename E>
inline Result<void, E>::~Result()
{
	delete_errors(errors_);
}

template<typename T, typename E>
inline Result<T, E> &Result<T, E>::operator=(const Result<T, E> &other)
{
	if (this == &other)
	{
		return *this;
	}

	if (value_)
	{
		delete value_;
		value_ = nullptr;
	}

	if (other.value_)
	{
		value_ = new T(*other.value_);
	}

	copy_errors(other.errors_, errors_);

	return *this;
}

template<typename E>
inline Result<void, E> &Result<void, E>::operator=(const Result<void, E> &other)
{
	if (this == &other)
	{
		return *this;
	}

	copy_errors(other.errors_, errors_);

	return *this;
}

template<typename T, typename E>
inline bool Result<T, E>::is_success() const
{
	return errors_.empty();
}

template<typename E>
inline bool Result<void, E>::is_success() const
{
	return errors_.empty();
}

template<typename T, typename E>
inline T Result<T, E>::get_value() const
{
	return *value_;
}

template<typename T, typename E>
inline std::vector<E *> &Result<T, E>::get_errors()
{
	return errors_;
}

template<typename E>
inline std::vector<E *> &Result<void, E>::get_errors()
{
	return errors_;
}

template<typename T, typename E>
inline Result<T, E> Result<T, E>::ok(const T &value)
{
	return Result<T, E>(value);
}

template<typename E>
inline Result<void, E> Result<void, E>::ok()
{
	return Result<void, E>();
}

template<typename T, typename E>
inline Result<T, E> Result<T, E>::fail(E *error)
{
	return Result<T, E>(error);
}

template<typename E>
inline Result<void, E> Result<void, E>::fail(E *error)
{
	return Result<void, E>(error);
}

template<typename T, typename E>
inline Result<T, E> Result<T, E>::fail(std::vector<E *> &errors)
{
	return Result<T, E>(errors);
}

template<typename E>
inline Result<void, E> Result<void, E>::fail(std::vector<E *> &errors)
{
	return Result<void, E>(errors);
}
