#pragma once

#include "RefCounter.hpp"

template <typename T>
class MySmartPointer
{
public:
	MySmartPointer(T *pointer = nullptr, bool points_to_stack = false);

	MySmartPointer(const MySmartPointer &other);
	~MySmartPointer();
	MySmartPointer<T> &operator=(const MySmartPointer &other);

	T &operator*();
	T *operator->();

	bool is_null();

private:
	void delete_if_unused();

	RefCounter *counter_;
	T *pointer_;
	bool points_to_stack_;
};


template<typename T>
inline MySmartPointer<T>::MySmartPointer(T *pointer, bool points_to_stack)
	: counter_(nullptr),
	pointer_(pointer),
	points_to_stack_(points_to_stack)
{
	if (pointer_)
	{
		counter_ = new RefCounter();
		counter_->add();
	}
}

template<typename T>
inline MySmartPointer<T>::MySmartPointer(const MySmartPointer &other)
	: counter_(other.counter_),
	pointer_(other.pointer_),
	points_to_stack_(other.points_to_stack_)
{
	if (counter_)
	{
		counter_->add();
	}
}

template<typename T>
inline MySmartPointer<T>::~MySmartPointer()
{
	delete_if_unused();
}

template<typename T>
inline MySmartPointer<T> &MySmartPointer<T>::operator=(const MySmartPointer &other)
{
	if (pointer_ == other.pointer_)
	{
		return *this;
	}

	delete_if_unused();

	pointer_ = other.pointer_;
	counter_ = other.counter_;
	points_to_stack_ = other.points_to_stack_;

	if (counter_)
	{
		counter_->add();
	}

	return *this;
}

template<typename T>
inline T &MySmartPointer<T>::operator*()
{
	return *pointer_;
}

template<typename T>
inline T *MySmartPointer<T>::operator->()
{
	return pointer_;
}

template<typename T>
inline bool MySmartPointer<T>::is_null()
{
	return pointer_;
}

template<typename T>
inline void MySmartPointer<T>::delete_if_unused()
{
	if (counter_ && counter_->dec() == 0)
	{
		if (!points_to_stack_)
		{
			delete pointer_;
		}
		
		delete counter_;
	}
}
