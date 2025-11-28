#include "pch.h"
#include "tree.hpp"
#include "string_helpers.hpp"
#include "result.hpp"
#include "result_tests.hpp"
#include <sstream>

#define ABS_ERR 1e-3

TEST(SplitTest, SplitFunctionality)
{
    std::string formula1 = "+ * a sin / 5 6 + c dup";
    std::vector<std::string> expected1 = { "+", "*", "a", "sin", "/", "5", "6", "+", "c", "dup" };
    EXPECT_EQ(split(formula1, " "), expected1);

    std::string formula2 = "a,b,c";
    std::vector<std::string> expected2 = { "a", "b", "c" };
    EXPECT_EQ(split(formula2, ","), expected2);

    std::string formula3 = "";
    std::vector<std::string> expected3 = { };
    EXPECT_EQ(split(formula3, " "), expected3);

    std::string formula4 = "hello";
    std::vector<std::string> expected4 = { "hello" };
    EXPECT_EQ(split(formula4, " "), expected4);
}

TEST(TreeTest, GetFormulaToString)
{
    Tree tree0;
    EXPECT_EQ(tree0.get_formula_to_string(), "[empty]");

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

TEST(TreeTest, JoinReturnsNewTreeAndDoesNotModifyOriginals)
{
    std::string formula1 = "+ * a sin / 5 6 + c dup";
    std::string formula2 = "+ * 5 sin x * + a b 8";
    std::string formula3 = "+ * A sin B + A A";
    
    Tree tree0;
    Tree tree1(formula1);
    Tree tree2(formula2);
    Tree tree3(formula3);

    // Test: 0 join 1
    Tree res01 = tree0.join(tree1);
    ASSERT_EQ(formula1, res01.get_formula_to_string());
    ASSERT_EQ("[empty]", tree0.get_formula_to_string());
    ASSERT_EQ(formula1, tree1.get_formula_to_string());

    // Test: 1 join 2
    Tree res12 = tree1.join(tree2);
    ASSERT_EQ("+ * a sin / 5 6 + c + * 5 sin x * + a b 8", res12.get_formula_to_string());
    ASSERT_EQ(formula1, tree1.get_formula_to_string());
    ASSERT_EQ(formula2, tree2.get_formula_to_string());

    // tree0 (empty) + tree1 -> tree1
    Tree sum1 = tree0 + tree1;
    ASSERT_EQ(formula1, sum1.get_formula_to_string());

    // tree1 + tree0 (empty) -> tree1
    Tree sum2 = tree1 + tree0;
    ASSERT_EQ(formula1, sum2.get_formula_to_string());
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

TEST(TreeTest, JoinVariables_Scenario1)
{
    std::string f1_1 = "+ a 1";
    std::string f2_1 = "+ b 1";
    Tree t1_1(f1_1);
    Tree t2_1(f2_1);

    EXPECT_EQ(t1_1.get_variables_to_string(), "a");
    EXPECT_EQ(t2_1.get_variables_to_string(), "b");

    Tree result = t1_1 + t2_1;

    EXPECT_EQ(result.get_formula_to_string(), "+ a + b 1");
    EXPECT_EQ(result.get_variables_to_string(), "a b");

    EXPECT_EQ(t1_1.get_formula_to_string(), f1_1);
    EXPECT_EQ(t1_1.get_variables_to_string(), "a");

    EXPECT_EQ(t2_1.get_formula_to_string(), f2_1);
    EXPECT_EQ(t2_1.get_variables_to_string(), "b");
}

TEST(TreeTest, JoinVariables_Scenario2)
{
    std::string f1_2 = "+ 1 a";
    std::string f2_2 = "+ b 1";
    Tree t1_2(f1_2);
    Tree t2_2(f2_2);

    EXPECT_EQ(t1_2.get_variables_to_string(), "a");
    EXPECT_EQ(t2_2.get_variables_to_string(), "b");

    Tree result = t1_2 + t2_2;

    EXPECT_EQ(result.get_formula_to_string(), "+ 1 + b 1");
    EXPECT_EQ(result.get_variables_to_string(), "b");

    EXPECT_EQ(t1_2.get_formula_to_string(), f1_2);
    EXPECT_EQ(t1_2.get_variables_to_string(), "a");
    EXPECT_EQ(t2_2.get_formula_to_string(), f2_2);
}

TEST(TreeTest, JoinVariables_Deduplication)
{
    std::string f1 = "+ 1 a";
    std::string f2 = "+ a b";
    Tree t1(f1);
    Tree t2(f2);

    EXPECT_EQ(t1.get_variables_to_string(), "a");
    EXPECT_EQ(t2.get_variables_to_string(), "a b");

    Tree result = t1.join(t2);

    EXPECT_EQ(result.get_formula_to_string(), "+ 1 + a b");
    EXPECT_EQ(result.get_variables_to_string(), "a b");

    EXPECT_EQ(t1.get_formula_to_string(), f1);
    EXPECT_EQ(t1.get_variables_to_string(), "a");
    EXPECT_EQ(t2.get_formula_to_string(), f2);
    EXPECT_EQ(t2.get_variables_to_string(), "a b");
}

TEST(ResultTest, BasicReturns)
{
    Result<double, Error> res = divide_two(10, 5);
    EXPECT_EQ("2", get_result_two_to_string(res));
    res = divide_two(10, 4);
    EXPECT_EQ("2.5", get_result_two_to_string(res));
    res = divide_two(10, 0);
    EXPECT_EQ(ErrorDivisionByZero().get_message(), get_result_two_to_string(res));

    Result<double, Error> res_st = divide_two_static(10, 5);
    EXPECT_EQ("2", get_result_two_to_string(res_st));
    res_st = divide_two_static(10, 4);
    EXPECT_EQ("2.5", get_result_two_to_string(res_st));
    res_st = divide_two_static(10, 0);
    EXPECT_EQ(ErrorDivisionByZero().get_message(), get_result_two_to_string(res_st));
}

struct TestError 
{
    std::string message;
    TestError(std::string m) : message(m) {}
    TestError(const TestError &other) : message(other.message) {}

    std::string get_message() const { return message; }
};

TEST(ResultTest, CreateSuccess) 
{
    auto res = Result<int, TestError>::ok(42);

    EXPECT_TRUE(res.is_success());
    EXPECT_EQ(42, res.get_value());
    EXPECT_TRUE(res.get_errors().empty());
}

TEST(ResultTest, CreateFailureSingle) 
{
    TestError *err = new TestError("Critical error");
    auto res = Result<int, TestError>::fail(err);

    EXPECT_FALSE(res.is_success());
    ASSERT_EQ(1, res.get_errors().size());
    EXPECT_EQ("Critical error", res.get_errors()[0]->get_message());
}

TEST(ResultTest, CreateFailureMultiple) 
{
    std::vector<TestError *> errors;
    errors.push_back(new TestError("B³¹d 1"));
    errors.push_back(new TestError("B³¹d 2"));

    auto res = Result<int, TestError>::fail(errors);

    for (auto e : errors)
    {
        delete e;
    }

    EXPECT_FALSE(res.is_success());
    ASSERT_EQ(2, res.get_errors().size());
    EXPECT_EQ("B³¹d 1", res.get_errors()[0]->get_message());
    EXPECT_EQ("B³¹d 2", res.get_errors()[1]->get_message());
}

TEST(ResultTest, CopyConstructorDeepCopyCheck) 
{
    auto original = Result<int, TestError>::fail(new TestError("Original"));

    Result<int, TestError> copy = original;

    // same values
    ASSERT_EQ(1, copy.get_errors().size());
    EXPECT_EQ("Original", copy.get_errors()[0]->get_message());

    // different addresses
    EXPECT_NE(original.get_errors()[0], copy.get_errors()[0]);
}

TEST(ResultTest, AssignmentOperatorSuccessToFail) 
{
    auto res = Result<int, TestError>::ok(100);
    auto failure = Result<int, TestError>::fail(new TestError("Awaria"));

    res = failure;

    EXPECT_FALSE(res.is_success());
    ASSERT_FALSE(res.get_errors().empty());
    EXPECT_EQ("Awaria", res.get_errors()[0]->get_message());
}

TEST(ResultTest, AssignmentOperatorFailToSuccess) 
{
    auto res = Result<int, TestError>::fail(new TestError("Z³y start"));
    auto success = Result<int, TestError>::ok(777);

    res = success;

    EXPECT_TRUE(res.is_success());
    EXPECT_TRUE(res.get_errors().empty());
    EXPECT_EQ(777, res.get_value());
}

TEST(ResultTest, SelfAssignment) 
{
    auto res = Result<int, TestError>::ok(5);
    res = res;

    EXPECT_TRUE(res.is_success());
    EXPECT_EQ(5, res.get_value());
}

TEST(ResultTest, WorksWithStrings) 
{
    auto res = Result<std::string, TestError>::ok("Hello World");
    EXPECT_EQ("Hello World", res.get_value());
}