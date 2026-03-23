#include "math_op.hpp"

#include <stdexcept>
#include <cmath>

long long haliullin::sum(long long a, long long b)
{
  if (b > 0 && a > haliullin::MAX - b)
  {
    throw std::overflow_error("sum overflow");
  }
  else if (b < 0 && a < haliullin::MIN - b)
  {
    throw std::overflow_error("sum overflow");
  }
  return a + b;
}

long long haliullin::subtract(long long a, long long b)
{
  if (b > 0 && a < haliullin::MIN + b)
  {
    throw std::overflow_error("subtraction overflow");
  }
  else if (b < 0 && a > haliullin::MAX + b)
  {
    throw std::overflow_error("subtraction overflow");
  }
  return a - b;
}

long long haliullin::multiply(long long a, long long b)
{
  if (a == 0 || b == 0)
  {
    return 0;
  }

  if (a > 0)
  {
    if (b > 0 && a > haliullin::MAX / b)
    {
      throw std::overflow_error("multiplication overflow");
    }
    else if (b < 0 && b < haliullin::MIN / b)
    {
      throw std::overflow_error("multiplication overflow");
    }
  }
  else
  {
    if (b > 0 && a < haliullin::MIN / b)
    {
      throw std::overflow_error("multiplication overflow");
    }
    else if (b < 0 && a < haliullin::MAX / b)
    {
      throw std::overflow_error("multiplication overflow");
    }
  }
  return a * b;
}

long long haliullin::divide(long long a, long long b)
{
  if (b == 0)
  {
    throw std::logic_error("division by zero");
  }

  if (a == haliullin::MIN && b == -1)
  {
    throw std::overflow_error("division overflow");
  }
  return a / b;
}

long long haliullin::mod(long long a, long long b)
{
  if (b == 0)
  {
    throw std::logic_error("division by zero");
  }
  return (a % b + b) % b;
}

long long haliullin::gcd(long long a, long long b)
{
  a = std::abs(a);
  b = std::abs(b);
  while (b != 0)
  {
    long long tmp = b;
    b = a % b;
    a = tmp;
  }
  return a;
}

long long haliullin::lcm(long long a, long long b)
{
  if (a == 0 || b == 0)
  {
    throw std::logic_error("lcm must be non-zero");
  }

  long long g = gcd(a, b);
  a = std::abs(a);
  b = std::abs(b);

  if ((a / g) > (haliullin::MAX / b))
  {
    throw std::overflow_error("lcm overflow");
  }
  return (a / g) * b;
}
