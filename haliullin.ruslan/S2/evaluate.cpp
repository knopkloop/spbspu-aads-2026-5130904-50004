#include <string>
#include <stdexcept>
#include "evaluate.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "math_op.hpp"

bool haliullin::comparePriority(const std::string& cur_op, const std::string& stack_top_op)
{
  auto get_p = [](const std::string& op) -> int
  {
    if (op == "lcm")
    {
      return 3;
    }
    if (op == "*" || op == "/" || op == "%")
    {
      return 2;
    }
    if (op == "+" || op == "-")
    {
      return 1;
    }
    return 0;
  };
  return get_p(stack_top_op) >= get_p(cur_op);
}

long long haliullin::calculate(long long a, long long b, const std::string& oper)
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
  else
  {
    throw std::logic_error("Invalid operator");
  }
}

bool haliullin::isOperator(const std::string& tok)
{
  if (tok.length() == 1)
  {
    return tok[0] == '+' || tok[0] == '-' || tok[0] == '*' || tok[0] == '/' || tok[0] == '%';
  }
  return tok == "lcm";
}

void haliullin::processToken(const std::string& token, Queue< std::string >& output, Stack< std::string >& opStack)
{
  if (token.empty())
  {
    return;
  }
  size_t pos = 0;
  try
  {
    std::stoll(token, &pos);
    if (pos != token.length())
    {
      throw std::invalid_argument("Partial number");
    }
    output.push(token);
    return;
  }
  catch (const std::invalid_argument&)
  {
    if (isOperator(token))
    {
      while (!opStack.is_empty() && opStack.top() != "(" && comparePriority(token, opStack.top()))
      {
        output.push(opStack.top());
        opStack.pop();
      }
      opStack.push(token);
    }
    else
    {
      throw std::logic_error("Invalid token: " + token);
    }
  }
}

haliullin::Queue< std::string > haliullin::infixToPostfix(const std::string& expression)
{
  Queue< std::string > output;
  Stack< std::string > opStack;
  std::string token;

  for (size_t i = 0; i < expression.length(); ++i)
  {
    char c = expression[i];
    if (c == ' ')
    {
      processToken(token, output, opStack);
      token.clear();
    }
    else if (c == '(' || c == ')')
    {
      processToken(token, output, opStack);
      token.clear();
      if (c == '(')
      {
        opStack.push("(");
      }
      else
      {
        while (!opStack.is_empty() && opStack.top() != "(")
        {
          output.push(opStack.top());
          opStack.pop();
        }
        if (opStack.is_empty())
        {
          throw std::logic_error("Missing '('");
        }
        opStack.pop();
      }
    }
    else
    {
      token += c;
    }
  }
  processToken(token, output, opStack);

  while (!opStack.is_empty())
  {
    std::string op = opStack.top();
    opStack.pop();
    if (op == "(" || op == ")")
    {
      throw std::logic_error("Mismatched parentheses");
    }
    output.push(op);
  }

  return output;
}

long long haliullin::evaluate(Queue< std::string > postfix)
{
  Stack< long long > evalStack;

  while (!postfix.is_empty())
  {
    std::string token = postfix.front();
    postfix.pop();

    if (isOperator(token))
    {
      if (evalStack.get_size() < 2)
      {
        throw std::logic_error("Not enough operands in expression");
      }
      long long b = evalStack.top();
      evalStack.pop();
      long long a = evalStack.top();
      evalStack.pop();

      evalStack.push(calculate(a, b, token));
    }
    else
    {
      try
      {
        evalStack.push(std::stoll(token));
      }
      catch (const std::invalid_argument&)
      {
        throw;
      }
    }
  }

  if (evalStack.is_empty())
  {
    throw std::logic_error("No result");
  }
  if (evalStack.get_size() != 1)
  {
    throw std::logic_error("Too many operands in expression");
  }

  return evalStack.top();
}
