#pragma once
#include "pch.h"
#include "tree.hpp"
#include <string>
#include <vector>

namespace
{
    const std::string INPUT_SEPARATOR = " ";
    const std::string COMMAND_ENTER = "enter";
    const std::string COMMAND_VARS = "vars";
    const std::string COMMAND_PRINT = "print";
    const std::string COMMAND_COMP = "comp";
    const std::string COMMAND_JOIN = "join";
    const std::string COMMAND_EXIT = "exit";
}

class Interface
{
public:
    Interface();
    void run();

private:
    void handle_enter(const std::string &arg);
    void handle_vars();
    void handle_print();
    void handle_comp(const std::string &arg);
    void handle_join(const std::string &arg);

    Tree tree_;
    bool running_;
};