#include "pch.h"
#include "interface.hpp"
#include <iostream>
#include <cctype>
#include <cstdlib>

Interface::Interface()
    : running_(true)
{
}

void Interface::run()
{
    std::string input;
    std::string command;
    std::string arg;

    while (running_)
    {
        std::cout << "\n>>> ";
        std::getline(std::cin, input);

        cut_white_beginning(input);

        if (input == COMMAND_EXIT)
        {
            running_ = false;
            continue;
        }

        std::string::size_type first_sep = input.find(INPUT_SEPARATOR);

        if (first_sep == std::string::npos)
        {
            command = input;
            arg.clear();
        }
        else
        {
            command = input.substr(0, first_sep);
            arg = input.substr(first_sep);
            cut_white_beginning(arg);
        }

        if (command == COMMAND_ENTER)
        {
            handle_enter(arg);
        }
        else if (command == COMMAND_VARS)
        {
            handle_vars();
        }
        else if (command == COMMAND_PRINT)
        {
            handle_print();
        }
        else if (command == COMMAND_COMP)
        {
            handle_comp(arg);
        }
        else if (command == COMMAND_JOIN)
        {
            handle_join(arg);
        }
        else if (!command.empty())
        {
            std::cout << "Unknown command: '" << command << "'\n";
        }
    }
}

void Interface::handle_enter(const std::string &arg)
{
    if (!arg.empty())
    {
        Error *err = tree_.load_new_formula(arg);

        if (err)
        {
            std::cout << err->get_message() << "\n";
            delete err;
        }

        std::cout << "formula loaded\n";
    }
    else
    {
        std::cout << "Too few arguments for " << COMMAND_ENTER << " command.\n";
    }
}

void Interface::handle_vars()
{
    std::cout << tree_.get_variables_to_string() << "\n";
}

void Interface::handle_print()
{
    std::cout << tree_.get_formula_to_string() << "\n";
}

void Interface::handle_comp(const std::string &arg)
{
    std::vector<std::string> vars_str = split(arg);
    std::vector<int> vars(vars_str.size());

    for (int i = 0; i < vars_str.size(); i++)
    {
        vars.at(i) = std::atoi(vars_str.at(i).c_str());
    }

    if (tree_.set_variables(vars))
    {
        std::cout << tree_.calculate_formula() << "\n";
    }
    else
    {
        std::cout << "Error: Number of values provided does not match number of variables.\n";
    }
}

void Interface::handle_join(const std::string &arg)
{
    if (!arg.empty())
    {
        Tree to_join(arg);
        tree_ = tree_ + to_join;
        std::cout << "Formula joined succesfully.\n";
    }
    else
    {
        std::cout << "Too few arguments for " << COMMAND_JOIN << " command.\n";
    }
}

int Interface::find_text(const std::string &text) const
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

void Interface::cut_white_beginning(std::string &text) const
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

std::vector<std::string> Interface::split(std::string input)
{
    std::vector<std::string> result;

    std::string::size_type next_regex_index = input.find(INPUT_SEPARATOR);
    std::string::size_type regex_length = INPUT_SEPARATOR.length();
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
        next_regex_index = input.find(INPUT_SEPARATOR, offset);
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
