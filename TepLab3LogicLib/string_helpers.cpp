#include "pch.h"
#include "string_helpers.hpp"

int find_text(const std::string &text)
{
    for (int i = 0; i < text.size(); i++)
    {
        if (!std::isspace(text.at(i)))
        {
            return i;
        }
    }

    return -1;
}

void cut_white_beginning(std::string &text)
{
    std::string::size_type pos = find_text(text);

    if (pos > 0)
    {
        text.erase(0, pos);
    }
    else if (pos == std::string::npos && !text.empty())
    {
        text.clear();
    }
}

std::vector<std::string> split(std::string input, std::string separator)
{
    std::vector<std::string> result;

    std::string::size_type next_regex_index = input.find(separator);
    std::string::size_type regex_length = separator.length();
    std::string::size_type offset = 0;

    std::string element;

    while (next_regex_index != std::string::npos)
    {
        if (next_regex_index > offset)
        {
            element = input.substr(offset, next_regex_index - offset);
            cut_white_beginning(element);

            if (!element.empty())
            {
                result.push_back(element);
            }
        }

        offset = next_regex_index + regex_length;
        next_regex_index = input.find(separator, offset);
    }

    if (offset < input.length())
    {
        element = input.substr(offset);
        cut_white_beginning(element);

        if (!element.empty())
        {
            result.push_back(element);
        }
    }

    return result;
}
