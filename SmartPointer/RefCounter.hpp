#pragma once

const int REF_COUNTER_DEFAULT_COUNT = 0;

class RefCounter
{
public:
	RefCounter();

	RefCounter(const RefCounter &) = delete;
	RefCounter &operator=(const RefCounter &) = delete;

	int add();
	int dec();
	int get() const;

private:
	int count_;
};
