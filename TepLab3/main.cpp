#include "error_message.hpp"
#include "result.hpp"

Result<double, ErrorMessage> divide_two(double dividend, double divisor)
{
    if (divisor == 0)
    {
        return new ErrorMessage("Cannot divide by zero.");
    }
    return dividend / divisor;
}

void print_result_two(Result<double, ErrorMessage> &res)
{
    if (res.is_success())
    {
        std::cout << res.get_value() << "\n";
    }
    else
    {
        std::vector<ErrorMessage *> errors = res.get_errors();
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

    Result<double, ErrorMessage> res = divide_two(10, 5);
    print_result_two(res);
    res = divide_two(10, 4);
    print_result_two(res);
    res = divide_two(10, 0);
    print_result_two(res);

    return 0;
}
