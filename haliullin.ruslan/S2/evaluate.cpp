#include <string>
#include <cctype>
#include <stdexcept>
#include "evaluate.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "math_op.hpp"

int haliullin::get_priority(const std::string& oper)
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
    throw std::logic_error("Invalid operator");
  }
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
  else if (tok == "lcm")
  {
    return true;
  }
  return false;
}

bool haliullin::isNumber(const std::string& token)
{
  if (token.empty())
  {
    return false;
  }

  size_t st = 0;
  if (token[0] == '-')
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
      if (!token.empty())
      {
        if (isNumber(token))
        {
          output.push(token);
        }
        else if (isOperator(token))
        {
          while (!opStack.is_empty() && opStack.top() != "(" && get_priority(opStack.top()) >= get_priority(token))
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
            throw std::logic_error("Missing '('");
          }
          opStack.drop();
        }
        else
        {
          throw std::logic_error("Invalid token");
        }
        token.clear();
      }
    }
    else if (c == '(' || c == ')')
    {
      if (!token.empty())
      {
        if (isNumber(token))
        {
          output.push(token);
        }
        else
        {
          throw std::logic_error("Invalid token");
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
          throw std::logic_error("Missing '('");
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
    if (isNumber(token))
    {
      output.push(token);
    }
    else if (isOperator(token))
    {
      while (!opStack.is_empty() && opStack.top() != "(" && get_priority(opStack.top()) >= get_priority(token))
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
        throw std::logic_error("Missing '('");
      }
      opStack.drop();
    }
    else
    {
      throw std::logic_error("Invalid token");
    }
  }

  while (!opStack.is_empty())
  {
    std::string op = opStack.drop();
    if (op == "(" || op == ")")
    {
      throw std::logic_error("Mismatched parentheses");
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
        throw std::logic_error("Not enough operands in expression");
      }
      long long b = evalStack.drop();
      if (evalStack.is_empty())
      {
        throw std::logic_error("Not enough operands in expression");
      }
      long long a = evalStack.drop();

      long long res = calculate(a, b, token);
      evalStack.push(res);
    }
    else if (isNumber(token))
    {
      long long num = std::stoll(token);
      evalStack.push(num);
    }
    else
    {
      throw std::logic_error("Invalid token");
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

  return evalStack.drop();
}
