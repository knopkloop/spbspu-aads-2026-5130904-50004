#include "evaluate.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "math_op.hpp"

#include <string>
#include <cctype>
#include <stdexcept>

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
  else
  {
    throw std::logic_error("invalid operator");
  }
}

bool haliullin::isOperator(const std::string & token)
{
  if (token.length() == 1)
  {
    char c = token[0];
    return ((c == '-') || (c == '+') || (c == '/') || (c == '*') || (c == '%'));
  }
  else if (token.length() == 3)
  {
    if (token == "lcm")
    {
      return true;
    }
  }
  return false;
}

bool haliullin::isNumber(const std::string & token)
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
    if (!std::isdigit(static_cast< unsigned char >(token[i])))
    {
      return false;
    }
  }
  return true;
}

haliullin::Queue< std::string > haliullin::infixToPostfix(const std::string & expression)
{
  haliullin::Queue< std::string > output;
  haliullin::Stack< std::string > opStack;
  std::string token;

  for (size_t i = 0; i < expression.length(); ++i)
  {
    char c = expression[i];

    if (c == ' ')
    {
      if (!token.empty())
      {
        if (haliullin::isNumber(token))
        {
          output.push(token);
        }
        else if (haliullin::isOperator(token))
        {
          while (!opStack.is_empty() && opStack.top() != "(" &&
                haliullin::get_priority(opStack.top()) >= haliullin::get_priority(token))
          {
            output.push(opStack.drop());
          }
          opStack.push(token);
        }
        else if (token == "(")
        {
          opStack.push(token);
        }
        else if (token == ")")
        {
          while (!opStack.is_empty() && opStack.top() != "(")
          {
            output.push(opStack.drop());
          }
          if (opStack.is_empty())
          {
            throw std::logic_error("missing '('");
          }
          opStack.drop();
        }
        else
        {
          throw std::logic_error("invalid token");
        }
        token.clear();
      }
    }
    else if (c == '(' || c == ')')
    {
      if (!token.empty())
      {
        if (haliullin::isNumber(token))
        {
          output.push(token);
        }
        else
        {
          throw std::logic_error("invalid token");
        }
        token.clear();
      }
      if (c == '(')
      {
        opStack.push("(");
      }
      else
      {
        while (!opStack.is_empty() && opStack.top() != "(")
        {
          output.push(opStack.drop());
        }
        if (opStack.is_empty())
        {
          throw std::logic_error("missing '('");
        }
        opStack.drop();
      }
    }
    else
    {
      token += c;
    }
  }

  if (!token.empty())
  {
    if (haliullin::isNumber(token))
    {
      output.push(token);
    }
    else if (haliullin::isOperator(token))
    {
      while (!opStack.is_empty() && opStack.top() != "(" &&
            haliullin::get_priority(opStack.top()) >= haliullin::get_priority(token))
      {
        output.push(opStack.drop());
      }
      opStack.push(token);
    }
    else if (token == "(")
    {
      opStack.push(token);
    }
    else if (token == ")")
    {
      while (!opStack.is_empty() && opStack.top() != "(")
      {
        output.push(opStack.drop());
      }
      if (opStack.is_empty())
      {
        throw std::logic_error("missing '('");
      }
      opStack.drop();
    }
    else
    {
      throw std::logic_error("invalid token");
    }
  }

  while (!opStack.is_empty())
  {
    std::string op = opStack.drop();
    if (op == "(" || op == ")")
    {
      throw std::logic_error("mismatched parentheses");
    }
    output.push(op);
  }

  return output;
}

long long haliullin::evaluate(haliullin::Queue< std::string > postfix)
{
  Stack< long long > evalStack;

  while (!postfix.is_empty())
  {
    std::string token = postfix.drop();

    if (isOperator(token))
    {
      if (evalStack.is_empty())
      {
        throw std::logic_error("not enough operands in expression");
      }
      long long b = evalStack.drop();
      if (evalStack.is_empty())
      {
        throw std::logic_error("not enough operands in expression");
      }
      long long a = evalStack.drop();

      long long res = calculate(a, b, token);
      evalStack.push(res);
    }
    else if (isNumber(token))
    {
      try
      {
        long long num = std::stoll(token);
        evalStack.push(num);
      }
      catch (...)
      {
        throw std::logic_error("invalid number");
      }
    }
    else
    {
      throw std::logic_error("invalid number");
    }
  }

  if (evalStack.is_empty())
  {
    throw std::logic_error("no result");
  }

  if (evalStack.size() != 1)
  {
    throw std::logic_error("too many operands in expression");
  }

  return evalStack.drop();
}
