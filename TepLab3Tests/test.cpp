#include "pch.h"
#include "tree.hpp"
#include <sstream>

TEST(ReadUserTest, CorrectlyReadsName) {
    std::stringstream fake_input("TestUser\n");
    std::stringstream fake_output;
    std::string name = readUserName(fake_input, fake_output);
    EXPECT_EQ("TestUser", name);
    EXPECT_EQ("Podaj nazwe: ", fake_output.str());
}
