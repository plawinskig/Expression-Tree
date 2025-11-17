#include "tree.hpp"
#include "node.hpp"
#include <iostream>
#include <vector>
#include <cctype>

namespace
{
    const char WHITE_MARK = ' ';
    const std::string COMMAND_SEPARATOR = " ";
    const std::string COMMAND_ENTER = "enter";
    const std::string COMMAND_VARS = "vars";
    const std::string COMMAND_PRINT = "print";
    const std::string COMMAND_COMP = "comp";
    const std::string COMMAND_JOIN = "join";
    const std::string COMMAND_EXIT = "exit";
}

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

void cut_white_begining(std::string &text)
{
    text.erase(0, find_text(text));
}

int main() 
{
    std::string input;
    std::string command;
    std::string arg;
    Tree tree;

    while (input != COMMAND_EXIT)
    {
        std::cout << "\n>>> ";

        std::getline(std::cin, input);

        cut_white_begining(input);
        //std::cout << input << "\n";

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
        }

        if (command == COMMAND_ENTER)
        {
            if (!arg.empty())
            {
                tree.load_new_formula(input.substr(command.size()));
                std::cout << "formula loaded\n";
            }
            else
            {
                std::cout << "Too few arguments for " << command << " command.";
            }
        }

        else if (command == COMMAND_VARS)
        {
            std::cout << tree.get_variables_to_string() << "\n";
        }

        else if (command == COMMAND_PRINT)
        {
            std::cout << tree.get_formula_to_string() << "\n";
        }

        else if (command == COMMAND_COMP)
        {
            std::vector<std::string> vars_str = Tree::split(input.substr(command.size()));
            std::vector<int> vars(vars_str.size());
            for (int i = 0; i < vars_str.size(); i++)
            {
                vars.at(i) = atoi(vars_str.at(i).c_str());
            }
            tree.set_variables(vars);
            std::cout << tree.calculate_formula() << "\n";
        }

        else if (command == COMMAND_JOIN)
        {
            Tree to_join(input.substr(command.size()));
            tree = tree + to_join;
            std::cout << "Formula joined succesfully.\n";
        }

        else if(!input.empty() && input != COMMAND_EXIT)
        {
            std::cout << "Unknown command: '" << command << "'\n";
        }
    }

    return 0;
}


