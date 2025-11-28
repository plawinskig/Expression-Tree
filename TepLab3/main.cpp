#include "error.hpp"
#include "result.hpp"
#include "interface.hpp"

Result<double, Error> divide_two(double dividend, double divisor)
{
    if (divisor == 0)
    {
        return new Error("Cannot divide by zero.");
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

void print_result_two(Result<double, Error> &res)
{
    if (res.is_success())
    {
        std::cout << res.get_value() << "\n";
    }
    else
    {
        std::vector<Error *> errors = res.get_errors();
        for (auto i : errors)
        {
            std::cout << (*i).get_message() << "\n";
        }
    }
}

int main()
{
    //Interface app;
    //app.run();

    Result<double, Error> res = divide_two(10, 5);
    print_result_two(res);
    res = divide_two(10, 4);
    print_result_two(res);
    res = divide_two(10, 0);
    print_result_two(res);

    return 0;
}
