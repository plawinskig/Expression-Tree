#pragma once

#include "RefCounter.hpp"

template <typename T>
class MySmartPointer
{
public:
	MySmartPointer(T *pointer);

	MySmartPointer(const MySmartPointer &other);
	~MySmartPointer();

	T &operator*();
	T *operator->();

private:
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
	if (counter_->dec() == 0)
	{
		delete pointer_;
		delete counter_;
	}
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
