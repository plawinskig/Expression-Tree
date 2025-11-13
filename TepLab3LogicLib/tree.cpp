#include "pch.h"
#include "tree.hpp"

std::vector<std::string> Tree::split(std::string formula, std::string separator)
{
    std::vector<std::string> result;

    int regex_index = formula.find(separator);
    int regex_length = separator.length();
    int offset = 0;

    while (regex_index != -1)
    {
        result.push_back(formula.substr(offset, regex_index - offset));
        offset = regex_index + regex_length;
        regex_index = formula.find(separator, offset);
    }

    result.push_back(formula.substr(offset));

    return result;
}
