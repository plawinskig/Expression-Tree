#include "pch.h"
#include "MySmartPointer.hpp"

const int REF_COUNTER_DEFAULT_COUNT = 0;

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

int RefCounter::get()
{
    return count_;
}
