#pragma once

#include <vector>

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

	bool is_success();

	T get_value();
	std::vector<E *> &get_errors();

	static Result<T, E> ok(const T &value);
	static Result<T, E> fail(E *error);
	static Result<T, E> fail(std::vector<E *> &errors);

private:
	T *value_;
	std::vector<E *> errors_;
};

template<typename T, typename E>
inline Result<T, E>::Result(const T &value)
{
}

template<typename T, typename E>
inline Result<T, E>::Result(E *error)
{
}

template<typename T, typename E>
inline Result<T, E>::Result(std::vector<E *> &errors)
{
}

template<typename T, typename E>
inline Result<T, E>::Result(const Result<T, E> &other)
{
}

template<typename T, typename E>
inline Result<T, E>::~Result()
{
}

template<typename T, typename E>
inline Result<T, E> &Result<T, E>::operator=(const Result<T, E> &other)
{
	// TODO: insert return statement here
}

template<typename T, typename E>
inline bool Result<T, E>::is_success()
{
	return false;
}

template<typename T, typename E>
inline T Result<T, E>::get_value()
{
	return T();
}

template<typename T, typename E>
inline std::vector<E *> &Result<T, E>::get_errors()
{
	// TODO: insert return statement here
}

template<typename T, typename E>
inline Result<T, E> Result<T, E>::ok(const T &value)
{
	return Result<T, E>();
}

template<typename T, typename E>
inline Result<T, E> Result<T, E>::fail(E *error)
{
	return Result<T, E>();
}

template<typename T, typename E>
inline Result<T, E> Result<T, E>::fail(std::vector<E *> &errors)
{
	return Result<T, E>();
}
