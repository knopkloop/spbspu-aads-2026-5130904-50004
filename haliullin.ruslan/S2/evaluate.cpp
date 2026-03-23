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
  if (oper == "+") return sum(a, b);
  else if (oper == "-") return subtract(a, b);
  else if (oper == "*") return multiply(a, b);
  else if (oper == "/") return divide(a, b);
  else if (oper == "%") return mod(a, b);
  else if (oper == "lcm") return lcm(a, b);
  throw std::logic_error("invalid operator");
}

