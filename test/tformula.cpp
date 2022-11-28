#include "Formula.h"
#include <gtest.h>

TEST(TFormulaTest, can_create_formula_from_string_without_prohibited_symbols)
{
  std::string str("a+b");
  ASSERT_NO_THROW(TFormula f(str));
}

TEST(TFormulaTest, cannot_create_formula_from_string_with_prohibited_symbols)
{
  std::string str("a@b");
  ASSERT_ANY_THROW(TFormula f(str));
}

TEST(TFormulaTest, formula_getinfix_returns_correct)
{
  std::string str("a+b");
  TFormula f(str);
  EXPECT_EQ(f.GetInfix(), str);
}

TEST(TFormulaTest, formula_getpostfix_returns_correct)
{
  std::string str("a+b");
  std::string strp("ab+");
  TFormula f(str);
  EXPECT_EQ(f.GetPostfix(), strp);
}

TEST(TFormulaTest, formula_getoperands_returns_correct)
{
  std::string str("a+b");
  TFormula f(str);
  std::vector<char> oprs;
  oprs.push_back('a');
  oprs.push_back('b');
  EXPECT_EQ(f.GetOperands(), oprs);
}

TEST(TFormulaTest, formula_calculate_returns_correct)
{
  std::string str("a+b");
  TFormula f(str);
  std::map<char, double> oprs = { {'a', 1}, {'b', 2} };
  EXPECT_EQ(f.Calculate(oprs), 3);
}