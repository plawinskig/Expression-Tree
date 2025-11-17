#pragma once
#include "pch.h"
#include "tree.hpp"
#include <string>
#include <vector>

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

    int find_text(const std::string &text) const;
    void cut_white_beginning(std::string &text) const;

    Tree tree_;
    bool running_;
};