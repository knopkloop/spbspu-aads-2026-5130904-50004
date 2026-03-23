#include "math_op.hpp"

#include <stdexcept>
#include <cmath>

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

  if ((a / g) > (MAX / b))
  {
    throw std::overflow_error("lcm overflow");
  }
  return (a / g) * b;
}
