#ifndef MATH_OP_HPP
#define MATH_OP_HPP

#include <limits>

namespace haliullin
{
  long long sum(long long a, long long b);
  long long subtract(long long a, long long b);
  long long multiply(long long a, long long b);
  long long divide(long long a, long long b);
  long long mod(long long a, long long b);
  long long gcd(long long a, long long b);
  long long lcm(long long a, long long b);

  constexpr long long MAX = std::numeric_limits< long long >::max();
  constexpr long long MIN = std::numeric_limits< long long >::min();
}

#endif
