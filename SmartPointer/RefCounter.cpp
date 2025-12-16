#include "pch.h"
#include "RefCounter.hpp"

RefCounter::RefCounter()
    : count_(REF_COUNTER_DEFAULT_COUNT)
{
}

unsigned RefCounter::add()
{
    return ++count_;
}

unsigned RefCounter::dec()
{
    return --count_;
}

unsigned RefCounter::get() const
{
    return count_;
}
