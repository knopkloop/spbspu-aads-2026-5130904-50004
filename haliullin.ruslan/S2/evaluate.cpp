#include "evaluate.hpp"
#include "math_op.hpp"

int haliullin::get_priority(const std::string & oper)
{
  if (oper == "lcm")
  {
    return 3;
  }
  else if (oper == "*" || oper == "/" || oper == "%")
  {
    return 2;
  }
  else if (oper == "+" || oper == "-")
  {
    return 1;
  }
  else
  {
    throw std::logic_error("invalid operator");
  }
}

long long haliullin::calculate(long long a, long long b, const std::string & oper)
{
  if (oper == "+")
  {
    return sum(a, b);
  }
  else if (oper == "-")
  {
    return subtract(a, b);
  }
  else if (oper == "*")
  {
    return multiply(a, b);
  }
  else if (oper == "/")
  {
    return divide(a, b);
  }
  else if (oper == "%")
  {
    return mod(a, b);
  }
  else if (oper == "lcm")
  {
    return lcm(a, b);
  }

  throw std::logic_error("invalid operator");
}

bool haliullin::isOperator(const std::string & token)
{
  if (token.empty())
  {
    return false;
  }

  if (token.length() == 1 && ((token[0] == '-') || (token[0] == '+') || (token[0] == '/') || (token[0] == '*') || (token[0] == '%')))
  {
    return true;
  }
  else if (token.length() == 3)
  {
    std::string tz = "lcm";

    if (token == tz)
    {
      return true;
    }
  }
  return false;
}

bool isNumber(const std::string & token)
{
  if (token.empty())
  {
    return false;
  }

  size_t st = 0;
  if (token[st] == '-')
  {
    if (token.length() == 1)
    {
      return false;
    }
    ++st;
  }

  for (size_t i = st; i < token.length(); ++i)
  {
    if (!std::isdigit(static_cast<unsigned char>(token[i])))
    {
      return false;
    }
  }
  return true;
}
