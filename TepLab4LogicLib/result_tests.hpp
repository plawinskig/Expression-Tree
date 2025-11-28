#pragma once

#include "error.hpp"
#include "result.hpp"

Result<double, Error> divide_two(double dividend, double divisor);
Result<double, Error> divide_two_static(double dividend, double divisor);
Result<void, Error> inverse_value(double &value);
Result<void, Error> inverse_value_static(double &value);
std::string get_result_two_to_string(Result<double, Error> &res);
