#ifndef EVALUATE_HPP
#define EVALUATE_HPP

#include "stack.hpp"
#include "queue.hpp"

namespace haliullin
{
  int get_priority(const std::string & oper);
  long long calculate(long long a, long long b, const std::string & oper);

  bool isOperator(const std::string & token);
  bool isNumber(const std::string & token);

}

#endif
