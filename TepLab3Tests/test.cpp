#include "pch.h"
#include "tree.hpp"
#include <sstream>

TEST(ReadUserTest, CorrectlyReadsName) 
{
    //std::stringstream fake_input("TestUser\n");
    //std::stringstream fake_output;
    //std::string name = readUserName(fake_input, fake_output);
    //EXPECT_EQ("TestUser", name);
    //EXPECT_EQ("Podaj nazwe: ", fake_output.str());
}

TEST(TreeTest, DefaultConstructorShouldReturnEmptyString) {
    Tree tree0;
    std::string expected = "";

    EXPECT_EQ(tree0.get_formula_to_string(), expected);
}

TEST(TreeTest, Formula1) {
    std::string formula1 = "+ * a sin / 5 6 + c dup";
    Tree tree1(formula1);

    EXPECT_EQ(tree1.get_formula_to_string(), formula1);
}

TEST(TreeTest, Formula2) {
    std::string formula2 = "+ * 5 sin x * + a b 8";
    Tree tree2(formula2);

    EXPECT_EQ(tree2.get_formula_to_string(), formula2);
}

TEST(TreeTest, Formula3) {
    std::string formula3 = "+ * A sin B + A A";
    Tree tree3(formula3);

    EXPECT_EQ(tree3.get_formula_to_string(), formula3);
}