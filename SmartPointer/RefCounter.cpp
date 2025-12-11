#include "pch.h"
#include "RefCounter.hpp"

RefCounter::RefCounter()
    : count_(REF_COUNTER_DEFAULT_COUNT)
{
}

int RefCounter::add()
{
    return ++count_;
}

int RefCounter::dec()
{
    return --count_;
}

int RefCounter::get() const
{
    return count_;
}
