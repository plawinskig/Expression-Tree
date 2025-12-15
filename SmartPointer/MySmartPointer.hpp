#pragma once

#include "RefCounter.hpp"

template <typename T>
class MySmartPointer
{
public:
	MySmartPointer(T *pointer = nullptr);

	MySmartPointer(const MySmartPointer &other);
	~MySmartPointer();
	MySmartPointer<T> &operator=(const MySmartPointer &other);

	T &operator*();
	T *operator->();

private:
	void delete_if_unused();

	RefCounter *counter_;
	T *pointer_;
};


template<typename T>
inline MySmartPointer<T>::MySmartPointer(T *pointer)
	: counter_(new RefCounter()),
	pointer_(pointer)
{
	counter_->add();
}

template<typename T>
inline MySmartPointer<T>::MySmartPointer(const MySmartPointer &other)
	: counter_(other.counter_),
	pointer_(other.pointer_)
{
	counter_->add();
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
	counter_->add();

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
inline void MySmartPointer<T>::delete_if_unused()
{
	if (counter_->dec() == 0)
	{
		delete pointer_;
		delete counter_;
	}
}
