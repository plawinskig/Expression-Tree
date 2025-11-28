#include "pch.h"
#include "result_tests.hpp"

#include <sstream>

Result<double, Error> divide_two(double dividend, double divisor)
{
    if (divisor == 0)
    {
        return new ErrorDivisionByZero();
    }
    return dividend / divisor;
}

Result<double, Error> divide_two_static(double dividend, double divisor)
{
    if (divisor == 0)
    {
        return Result<double, Error>::fail(new ErrorDivisionByZero());
    }
    return Result<double, Error>::ok(dividend / divisor);;
}

std::string get_result_two_to_string(Result<double, Error> &res)
{
    std::stringstream sstr;

    if (res.is_success())
    {
        sstr << res.get_value();
    }
    else
    {
        std::vector<Error *> errors = res.get_errors();
        for (auto i : errors)
        {
            sstr << (*i).get_message();
        }
    }

    return sstr.str();
}
