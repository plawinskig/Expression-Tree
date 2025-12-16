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

	bool is_null();

	std::vector<MySmartPointer<T> *> get_all_this_sp();

private:
	void delete_if_unused();

	RefCounter *counter_;
	T *pointer_;
	std::vector<MySmartPointer<T> *> *all_this_sp_;
};


template<typename T>
inline MySmartPointer<T>::MySmartPointer(T *pointer)
	: counter_(nullptr),
	pointer_(pointer),
	all_this_sp_(new std::vector<MySmartPointer<T> *>(1, this))
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
	all_this_sp_(other.all_this_sp_)
{
	if (counter_)
	{
		counter_->add();
	}

	all_this_sp_->push_back(this);
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
	all_this_sp_ = other.all_this_sp_;

	if (counter_)
	{
		counter_->add();
	}

	all_this_sp_->push_back(this);

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
inline std::vector<MySmartPointer<T> *> MySmartPointer<T>::get_all_this_sp()
{
	return *all_this_sp_;
}

template<typename T>
inline void MySmartPointer<T>::delete_if_unused()
{
	for (size_t i = 0; i < all_this_sp_->size(); ++i)
	{
		if (all_this_sp_->at(i) == this)
		{
			all_this_sp_->erase(all_this_sp_->begin() + i, all_this_sp_->begin() + i + 1);
			i = all_this_sp_->size();
		}
	}
	
	if (counter_ && counter_->dec() == 0)
	{
		delete pointer_;
		delete counter_;
		delete all_this_sp_;
	}
}
