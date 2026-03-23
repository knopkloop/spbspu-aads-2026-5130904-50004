#include "stack.hpp"

namespace haliullin
{
  int priority(const std::string & oper)
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
}
