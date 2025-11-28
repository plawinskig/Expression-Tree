#pragma once

#include <vector>
#include <iostream>
#include <string>

template <typename E>
class ResultBase
{
public:
	virtual ~ResultBase();

	bool is_success() const;
	std::vector<E *> &get_errors();

protected:
	ResultBase();
	ResultBase(E *error);
	ResultBase(std::vector<E *> &errors);

	ResultBase(const ResultBase<E> &other);
	ResultBase<E> &operator=(const ResultBase<E> &other);

	void copy_errors(const std::vector<E *> &errors);
	void clear_errors();

	std::vector<E *> errors_;
};

template <typename T, typename E>
class Result : public ResultBase<E>
{
public:
	Result(const T &value);
	Result(E *error);
	Result(std::vector<E *> &errors);

	Result(const Result<T, E> &other);
	~Result();
	Result<T, E> &operator=(const Result<T, E> &other);

	T get_value() const;

	static Result<T, E> ok(const T &value);
	static Result<T, E> fail(E *error);
	static Result<T, E> fail(std::vector<E *> &errors);

private:
	T *value_;
};

template <typename E>
class Result<void, E> : public ResultBase<E>
{
public:
	Result();
	Result(E *error);
	Result(std::vector<E *> &errors);

	Result(const Result<void, E> &other);
	~Result();
	Result<void, E> &operator=(const Result<void, E> &other);

	static Result<void, E> ok();
	static Result<void, E> fail(E *error);
	static Result<void, E> fail(std::vector<E *> &errors);
};


template<typename E>
inline ResultBase<E>::~ResultBase()
{
	clear_errors();
}

template<typename E>
inline bool ResultBase<E>::is_success() const
{
	return errors_.empty();
}

template<typename E>
inline std::vector<E *> &ResultBase<E>::get_errors()
{
	return errors_;
}

template<typename E>
inline ResultBase<E>::ResultBase()
	: errors_(std::vector<E *>())
{
}

template<typename E>
inline ResultBase<E>::ResultBase(E *error)
	: errors_(std::vector<E *>(1, error))
{
}

template<typename E>
inline ResultBase<E>::ResultBase(std::vector<E *> &errors)
	: errors_(std::vector<E *>())
{
	copy_errors(errors);
}

template<typename E>
inline ResultBase<E>::ResultBase(const ResultBase<E> &other)
	: errors_(std::vector<E *>())
{
	copy_errors(other.errors_);
}

template<typename E>
inline ResultBase<E> &ResultBase<E>::operator=(const ResultBase<E> &other)
{
	if (this == &other)
	{
		return *this;
	}

	copy_errors(other.errors_);

	return *this;
}

template<typename E>
inline void ResultBase<E>::copy_errors(const std::vector<E *> &errors)
{
	clear_errors();
	errors_.clear();

	for (typename std::vector<E *>::const_iterator it = errors.begin(); it != errors.end(); it++)
	{
		errors_.push_back(new E(*(*it)));
	}
}

template<typename E>
inline void ResultBase<E>::clear_errors()
{
	for (typename std::vector<E *>::const_iterator it = errors_.begin(); it != errors_.end(); it++)
	{
		delete *it;
	}
}


template<typename T, typename E>
inline Result<T, E>::Result(const T &value)
	: ResultBase<E>(),
	value_(new T(value))
{
}

template<typename E>
inline Result<void, E>::Result()
	: ResultBase<E>()
{
}

template<typename T, typename E>
inline Result<T, E>::Result(E *error)
	: ResultBase<E>()
{
}

template<typename E>
inline Result<void, E>::Result(E *error)
	: ResultBase<E>()
{
}

template<typename T, typename E>
inline Result<T, E>::Result(std::vector<E *> &errors)
	: ResultBase<E>(),
	value_(nullptr)
{
}

template<typename E>
inline Result<void, E>::Result(std::vector<E *> &errors)
	: ResultBase<E>()
{
}

template<typename T, typename E>
inline Result<T, E>::Result(const Result<T, E> &other)
	: ResultBase<E>(other),
	value_(nullptr)
{
	if (other.value_)
	{
		value_ = new T(*(other.value_));
	}
}

template<typename E>
inline Result<void, E>::Result(const Result<void, E> &other)
	: ResultBase<E>(other)
{
}

template<typename T, typename E>
inline Result<T, E>::~Result()
{
	delete value_;
}

template<typename E>
inline Result<void, E>::~Result()
{
}

template<typename T, typename E>
inline Result<T, E> &Result<T, E>::operator=(const Result<T, E> &other)
{
	ResultBase<E>::operator=(other);

	if (value_)
	{
		delete value_;
		value_ = nullptr;
	}

	if (other.value_)
	{
		value_ = new T(*other.value_);
	}

	return *this;
}

template<typename E>
inline Result<void, E> &Result<void, E>::operator=(const Result<void, E> &other)
{
	ResultBase<E>::operator=(other);

	return *this;
}

template<typename T, typename E>
inline T Result<T, E>::get_value() const
{
	return *value_;
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
