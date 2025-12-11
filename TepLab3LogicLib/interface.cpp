#include "pch.h"
#include "interface.hpp"
#include "result_file_handler.hpp"
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
            input = std::string();
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
        else if (command == COMMAND_GET)
        {
            handle_get(arg);
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
        else if (command == COMMAND_LEVELS)
        {
            handle_levels();
        }
        else if (!command.empty())
        {
            std::cout << "Unknown command: '" << command << "'\n";
        }
    }
}

void Interface::handle_get(const std::string &arg)
{
    Result<Tree *, Error> result = Tree::get_tree(arg);

    if (result.is_success())
    {
        std::cout << "Got formula: " << result.get_value()->get_formula_to_string() << "\n";
        tree_ = *result.get_value();
    }
    else
    {
        std::vector<Error *> errs = result.get_errors();

        for (std::vector<Error *>::iterator it = errs.begin(); it != errs.end(); it++)
        {
            std::cout << (*it)->get_message() << "\n";
        }
    }

    ResultFileHandler<Tree *> handler;
    handler.write(result, TREE_SAVING_FILE_PATH);
}

void Interface::handle_enter(const std::string &arg)
{
    Error *err_load = tree_.load_new_formula(arg);

    std::cout << err_load->get_message() << "\n";
    delete err_load;

    std::cout << "Loaded formula: " << tree_.get_formula_to_string() << "\n";
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
    std::vector<std::string> vars_str = split(arg, INPUT_SEPARATOR);
    std::vector<int> vars(vars_str.size());

    for (int i = 0; i < vars_str.size(); i++)
    {
        vars.at(i) = std::atoi(vars_str.at(i).c_str());
    }

    Error *err_set = tree_.set_variables(vars);

    if (err_set)
    {
        std::cout << err_set->get_message() << "\n";
        delete err_set;
    }
    else
    {
        std::cout << tree_.calculate_formula() << "\n";
    }
}

void Interface::handle_join(const std::string &arg)
{
    Tree to_join;
    Error *err_load = to_join.load_new_formula(arg);

    std::cout << err_load->get_message() << "\n";
    delete err_load;

    tree_ = tree_ + to_join;
    std::cout << "Formula joined succesfully\n";
    std::cout << "New formula: " << tree_.get_formula_to_string() << "\n";
}

void Interface::handle_levels()
{
    std::cout << tree_.get_levels_to_string() << "\n";
}
