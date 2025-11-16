#include "pch.h"
#include "tree.hpp"
#include <sstream>

#define ABS_ERR 1e-3

TEST(ReadUserTest, CorrectlyReadsName) 
{
    //std::stringstream fake_input("TestUser\n");
    //std::stringstream fake_output;
    //std::string name = readUserName(fake_input, fake_output);
    //EXPECT_EQ("TestUser", name);
    //EXPECT_EQ("Podaj nazwe: ", fake_output.str());
}

TEST(SplitTest, SplitFunctionality)
{
    std::string formula1 = "+ * a sin / 5 6 + c dup";
    std::vector<std::string> expected1 = { "+", "*", "a", "sin", "/", "5", "6", "+", "c", "dup" };
    EXPECT_EQ(Tree::split(formula1, " "), expected1);

    std::string formula2 = "a,b,c";
    std::vector<std::string> expected2 = { "a", "b", "c" };
    EXPECT_EQ(Tree::split(formula2, ","), expected2);

    std::string formula3 = "";
    std::vector<std::string> expected3 = { };
    EXPECT_EQ(Tree::split(formula3, " "), expected3);

    std::string formula4 = "hello";
    std::vector<std::string> expected4 = { "hello" };
    EXPECT_EQ(Tree::split(formula4, " "), expected4);
}

TEST(TreeTest, GetFormulaToString)
{
    Tree tree0;
    EXPECT_EQ(tree0.get_formula_to_string(), "");

    std::string formula1 = "+ * a sin / 5 6 + c dup";
    Tree tree1(formula1);
    EXPECT_EQ(tree1.get_formula_to_string(), formula1);

    std::string formula2 = "+ * 5 sin x * + a b 8";
    Tree tree2(formula2);
    EXPECT_EQ(tree2.get_formula_to_string(), formula2);

    std::string formula3 = "+ * A sin B + A A";
    Tree tree3(formula3);
    EXPECT_EQ(tree3.get_formula_to_string(), formula3);
}

TEST(TreeTest, GetDepth)
{
    std::string formula1 = "+ * a sin / 5 6 + c dup";
    Tree tree1(formula1);
    EXPECT_EQ(tree1.get_depth(), 4);

    std::string formula2 = "+ * 5 sin x * + a b 8";
    Tree tree2(formula2);
    EXPECT_EQ(tree2.get_depth(), 3);

    std::string formula3 = "+ * A sin B + A A";
    Tree tree3(formula3);
    EXPECT_EQ(tree3.get_depth(), 3);

    Tree tree_empty;
    Tree tree_leaf("a");
    Tree tree_simple_op("+ 1 2");

    EXPECT_EQ(tree_empty.get_depth(), 0);
    EXPECT_EQ(tree_leaf.get_depth(), 0);
    EXPECT_EQ(tree_simple_op.get_depth(), 1);
}

TEST(TreeTest, GetLevelToString)
{
    std::string formula1 = "+ * a sin / 5 6 + c dup";
    Tree tree1(formula1);
    EXPECT_EQ(tree1.get_level_to_string(0), "+");
    EXPECT_EQ(tree1.get_level_to_string(1), "* +");

    EXPECT_EQ(tree1.get_level_to_string(2), "a sin c dup");
    EXPECT_EQ(tree1.get_level_to_string(3), "/");
    EXPECT_EQ(tree1.get_level_to_string(4), "5 6");
    EXPECT_EQ(tree1.get_level_to_string(5), "");

    std::string formula2 = "+ * 5 sin x * + a b 8";
    Tree tree2(formula2);
    EXPECT_EQ(tree2.get_level_to_string(0), "+");
    EXPECT_EQ(tree2.get_level_to_string(1), "* *");
    EXPECT_EQ(tree2.get_level_to_string(2), "5 sin + 8");
    EXPECT_EQ(tree2.get_level_to_string(3), "x a b");
    EXPECT_EQ(tree2.get_level_to_string(4), "");

    std::string formula3 = "+ * A sin B + A A";
    Tree tree3(formula3);
    EXPECT_EQ(tree3.get_level_to_string(0), "+");
    EXPECT_EQ(tree3.get_level_to_string(1), "* +");
    EXPECT_EQ(tree3.get_level_to_string(2), "A sin A A");
    EXPECT_EQ(tree3.get_level_to_string(3), "B");
    EXPECT_EQ(tree3.get_level_to_string(4), "");

    Tree tree_empty;
    Tree tree_leaf("a");
    Tree tree_simple_op("+ 1 2");

    EXPECT_EQ(tree_empty.get_level_to_string(0), "");
    EXPECT_EQ(tree_leaf.get_level_to_string(0), "a");
    EXPECT_EQ(tree_leaf.get_level_to_string(1), "");
    EXPECT_EQ(tree_simple_op.get_level_to_string(0), "+");
    EXPECT_EQ(tree_simple_op.get_level_to_string(1), "1 2");
    EXPECT_EQ(tree_simple_op.get_level_to_string(2), "");
}

TEST(TreeTest, Join)
{
    std::string formula1 = "+ * a sin / 5 6 + c dup";
    std::string formula2 = "+ * 5 sin x * + a b 8";
    std::string formula3 = "+ * A sin B + A A";
    
    Tree tree0;
    Tree tree1(formula1);
    Tree tree2(formula2);
    Tree tree3(formula3);

    tree0.join(tree1); // 0 <- 1
    ASSERT_EQ(formula1, tree0.get_formula_to_string());
    ASSERT_EQ("", tree1.get_formula_to_string());

    tree1.join(tree2); // 1 <- 2
    ASSERT_EQ(formula2, tree1.get_formula_to_string());
    ASSERT_EQ("", tree2.get_formula_to_string());

    tree2.join(tree3); // 2 <- 3
    ASSERT_EQ(formula3, tree2.get_formula_to_string());
    ASSERT_EQ("", tree3.get_formula_to_string());

    tree3.join(tree3); // 3 <- 3
    ASSERT_EQ("", tree3.get_formula_to_string());

    tree0.join(tree1); // 1 <- 2
    ASSERT_EQ("+ * a sin / 5 6 + c + * 5 sin x * + a b 8", tree0.get_formula_to_string());
    ASSERT_EQ("", tree1.get_formula_to_string());

    tree0.join(tree1); // 1 <- 0
    ASSERT_EQ("+ * a sin / 5 6 + c + * 5 sin x * + a b 8", tree0.get_formula_to_string());
    ASSERT_EQ("", tree1.get_formula_to_string());

    tree0.join(tree2); // 1 <- 3
    ASSERT_EQ("+ * a sin / 5 6 + c + * 5 sin x * + a b + * A sin B + A A", tree0.get_formula_to_string());
    ASSERT_EQ("", tree2.get_formula_to_string());
}

TEST(TreeTest, GetVariablesToString)
{
    std::string formula1 = "+ * a sin / 5 6 + c dup";
    Tree tree1(formula1);
    EXPECT_EQ(tree1.get_variables_to_string(), "a c dup");

    std::string formula2 = "+ * 5 sin x * + a b 8";
    Tree tree2(formula2);
    EXPECT_EQ(tree2.get_variables_to_string(), "x a b");

    std::string formula3 = "+ * A sin B + A A";
    Tree tree3(formula3);
    EXPECT_EQ(tree3.get_variables_to_string(), "A B");

    Tree tree_empty;
    EXPECT_EQ(tree_empty.get_variables_to_string(), "");

    Tree tree_no_vars("+ 1 2");
    EXPECT_EQ(tree_no_vars.get_variables_to_string(), "");

    Tree tree_single_var("sin a");
    EXPECT_EQ(tree_single_var.get_variables_to_string(), "a");
}

TEST(TreeTest, CalculateFormulaDefaultValues)
{
    std::string formula0 = "+ * a / 5 10 - c dup";
    Tree tree0(formula0);
    EXPECT_NEAR(tree0.calculate_formula(), ((1) * (5.0 / 10)) + ((1 - 1)), ABS_ERR);

    std::string formula1 = "+ * a sin / 5 6 + c dup";
    Tree tree1(formula1);
    EXPECT_NEAR(tree1.calculate_formula(), (1.0 * sin(5.0 / 6.0)) + (1.0 + 1.0), ABS_ERR);

    std::string formula2 = "+ * 5 sin x * + a b 8";
    Tree tree2(formula2);
    EXPECT_NEAR(tree2.calculate_formula(), (5.0 * sin(1.0)) + ((1.0 + 1.0) * 8.0), ABS_ERR);

    std::string formula3 = "+ * A sin B + A A";
    Tree tree3(formula3);
    EXPECT_NEAR(tree3.calculate_formula(), (1.0 * sin(1.0)) + (1.0 + 1.0), ABS_ERR);

    Tree tree_empty;
    EXPECT_NEAR(tree_empty.calculate_formula(), 0.0, ABS_ERR);

    Tree tree_literal("42");
    EXPECT_NEAR(tree_literal.calculate_formula(), 42.0, ABS_ERR);

    Tree tree_simple_op("+ 10 20");
    EXPECT_NEAR(tree_simple_op.calculate_formula(), 30.0, ABS_ERR);
}

TEST(TreeTest, CalculateFormulaSetVariables)
{
    std::string formula1 = "+ * a sin / 5 6 + c dup";
    Tree tree1(formula1);
    std::vector<int> vars1 = { 2, 3, 3 };
    tree1.set_variables(vars1);
    EXPECT_NEAR(tree1.calculate_formula(), ((2.0) * sin(5.0 / 6.0)) + (3.0 + 3.0), ABS_ERR);

    std::string formula2 = "+ * 5 sin x * + a b 8";
    Tree tree2(formula2);
    std::vector<int> vars2 = { 3, 4, 5 };
    tree2.set_variables(vars2);
    EXPECT_NEAR(tree2.calculate_formula(), (5.0 * sin(3.0)) + ((4.0 + 5.0) * 8.0), ABS_ERR);

    std::string formula3 = "+ * A sin B + A A";
    Tree tree3(formula3);
    std::vector<int> vars3 = { 2, 0 };
    tree3.set_variables(vars3);
    EXPECT_NEAR(tree3.calculate_formula(), (2.0 * sin(0.0)) + (2.0 + 2.0), ABS_ERR);
}
