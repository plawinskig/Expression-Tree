#include "pch.h"
#include "interface.hpp"
#include <iostream>
#include <cctype>
#include <cstdlib>

namespace
{
    const std::string COMMAND_SEPARATOR = " ";
    const std::string COMMAND_ENTER = "enter";
    const std::string COMMAND_VARS = "vars";
    const std::string COMMAND_PRINT = "print";
    const std::string COMMAND_COMP = "comp";
    const std::string COMMAND_JOIN = "join";
    const std::string COMMAND_EXIT = "exit";
}

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

        std::string::size_type first_sep = input.find(COMMAND_SEPARATOR);

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
        }
        else
        {
            std::cout << "formula loaded\n";
        }
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
    std::vector<std::string> vars_str = Tree::split(arg);
    std::vector<int> vars(vars_str.size());

    for (size_t i = 0; i < vars_str.size(); i++)
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
    for (size_t i = 0; i < text.size(); i++)
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