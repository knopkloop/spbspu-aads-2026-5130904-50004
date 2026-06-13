#ifndef EVALUATE_HPP
#define EVALUATE_HPP

#include "stack.hpp"
#include "queue.hpp"

namespace haliullin
{
  bool comparePriority(const std::string& cur_op, const std::string& stack_top_op);
  long long calculate(long long a, long long b, const std::string& oper);
  bool isOperator(const std::string& token);
  void processToken(const std::string& token, Queue< std::string >& output, Stack< std::string >& opStack);
  Queue< std::string > infixToPostfix(const std::string& expression);
  long long evaluate(Queue< std::string > postfix);
}

#endif
