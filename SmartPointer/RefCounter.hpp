#pragma once

const unsigned REF_COUNTER_DEFAULT_COUNT = 0;

class RefCounter
{
public:
	RefCounter();

	RefCounter(const RefCounter &) = delete;
	RefCounter &operator=(const RefCounter &) = delete;

	unsigned add();
	unsigned dec();
	unsigned get() const;

private:
	unsigned count_;
};
