#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Stack.h"

class TFormula {
private:
  std::string infix; 
  std::string postfix; 
  std::vector<char> lexems; 
  std::map<char, int> priority;
  std::map<char, double> operands; 

  void Parse(); 
  void ToPostfix(); 
public:
  TFormula(std::string _infix);

  std::string GetInfix() const { return infix; }
  std::string GetPostfix() const;
  std::vector<char> GetOperands() const;

  double Calculate(const std::map<char, double>& _operands);
};

void TFormula::Parse()
{
  size_t i = 0;
  while (i < infix.length())
  {
    switch (infix[i])
    {
    case '@': case '#': case '&': case '$': case '!': case '%': case '|': case '~': case '?': case '>': case '<': case ':': case ';':
      throw "Unknown symbol in expression";
      break;
    case 'c':
      if (i < infix.length() - 3)
      {
        if (infix[i + 1] == 'o' && infix[i + 2] == 's')
        {
          lexems.push_back('@');
          i += 2;
        }
        else { lexems.push_back(infix[i]); }
      }
      else { lexems.push_back(infix[i]); }
      break;
    case 's':
      if (i < infix.length() - 3)
      {
        if (infix[i + 1] == 'i' && infix[i + 2] == 'n')
        {
          lexems.push_back('#');
          i += 2;
        }
        else { lexems.push_back(infix[i]); }
      }
      else { lexems.push_back(infix[i]); }
      break;
    default:
      lexems.push_back(infix[i]);
    }
    i++;
  }
}

void TFormula::ToPostfix()
{
  Parse();
  TStack<char> st;
  char stackItem;
  for (char item : lexems)
  {
    switch (item)
    {
    case '(':
      st.Push(item);
      break;
    case ')':
      stackItem = st.Pop();
      while (stackItem != '(')
      {
        postfix += stackItem;
        stackItem = st.Pop();
      }
      break;
    case '+': case '-': case '*': case '/': case '^': case '@': case '#':
      while (!st.isEmpty())
      {
        stackItem = st.Pop();
        if (priority[item] <= priority[stackItem]) { postfix += stackItem; }
        else {
          st.Push(stackItem);
          break;
        }
      }
      st.Push(item);
      break;
    default:
      operands.insert({ item, 0.0 });
      postfix += item;
    }
  }
  while (!st.isEmpty())
  {
    stackItem = st.Pop();
    postfix += stackItem;
  }
}

TFormula::TFormula(std::string _infix) : infix(_infix)
{
  priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}, {'@', 3}, {'#', 3} };
  ToPostfix();
}

std::string TFormula::GetPostfix() const
{
  std::string Result;
  for (char c : postfix)
  {
    switch (c)
    {
    case '@':
      Result += 'c';
      Result += 'o';
      Result += 's';
      break;
    case '#':
      Result += 's';
      Result += 'i';
      Result += 'n';
      break;
    default:
      Result += c;
    }
  }
  return Result;
}

std::vector<char> TFormula::GetOperands() const
{
  std::vector<char> op;
  for (const auto& item : operands) { op.push_back(item.first); }
  return op;
}

double TFormula::Calculate(const std::map<char, double>& _operands)
{
  for (auto& val : _operands)
  {
    try
    {
      operands.at(val.first) = val.second;
    }
    catch (std::out_of_range& e) {}
  }
  TStack<double> st(postfix.size());
  double l_operand, r_operand;
  for (char lexem : postfix)
  {
    switch (lexem)
    {
    case '+':
      r_operand = st.Pop();
      l_operand = st.Pop();
      st.Push(l_operand + r_operand);
      break;
    case '-':
      r_operand = st.Pop();
      l_operand = st.Pop();
      st.Push(l_operand - r_operand);
      break;
    case '*':
      r_operand = st.Pop();
      l_operand = st.Pop();
      st.Push(l_operand * r_operand);
      break;
    case '/':
      r_operand = st.Pop();
      l_operand = st.Pop();
      st.Push(l_operand / r_operand);
      break;
    case '^':
      r_operand = st.Pop();
      l_operand = st.Pop();
      st.Push(pow(l_operand, r_operand));
      break;
    case '@':
      r_operand = st.Pop();
      st.Push(cos(r_operand));
      break;
    case '#':
      r_operand = st.Pop();
      st.Push(sin(r_operand));
      break;
    default:
      st.Push(operands[lexem]);
    }
  }
  return st.Pop();
}