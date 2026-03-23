#ifndef EVALUATE_HPP
#define EVALUATE_HPP

#include "stack.hpp"

namespace haliullin
{
  int get_priority(const std::string & oper);
  long long calculate(long long a, long long b, const std::string & oper);
}

#endif
