#pragma once

const int REF_COUNTER_DEFAULT_COUNT = 0;

class RefCounter
{
public:
	RefCounter();

	int add();
	int dec();
	int get() const;

private:
	int count_;
};
