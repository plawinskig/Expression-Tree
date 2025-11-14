#include "pch.h"
#include "tree.hpp"

std::vector<std::string> Tree::split(std::string formula, std::string separator)
{
    std::vector<std::string> result;

    std::string::size_type regex_index = formula.find(separator);
    std::string::size_type regex_length = separator.length();
    std::string::size_type offset = 0;

    while (regex_index != std::string::npos)
    {
        result.push_back(formula.substr(offset, regex_index - offset));
        offset = regex_index + regex_length;
        regex_index = formula.find(separator, offset);
    }

    result.push_back(formula.substr(offset));

    return result;
}
