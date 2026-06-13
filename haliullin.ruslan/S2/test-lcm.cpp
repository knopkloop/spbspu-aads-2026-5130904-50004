#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <limits>
#include "evaluate.hpp"
#include "math_op.hpp"

BOOST_AUTO_TEST_SUITE(lcm_tests)

BOOST_AUTO_TEST_CASE(basic)
{
  BOOST_CHECK_EQUAL(haliullin::lcm(4, 6), 12);
  BOOST_CHECK_EQUAL(haliullin::lcm(3, 5), 15);
  BOOST_CHECK_EQUAL(haliullin::lcm(10, 15), 30);
}

BOOST_AUTO_TEST_CASE(in_expression)
{
  BOOST_CHECK_EQUAL(haliullin::evaluate(haliullin::infixToPostfix("4 lcm 6")), 12);
  BOOST_CHECK_EQUAL(haliullin::evaluate(haliullin::infixToPostfix("7 lcm 12 - 24")), 60);
}

BOOST_AUTO_TEST_CASE(exceptions)
{
  BOOST_CHECK_THROW(haliullin::lcm(0, 5), std::logic_error);
  BOOST_CHECK_THROW(haliullin::lcm(5, 0), std::logic_error);
  BOOST_CHECK_THROW(haliullin::lcm(std::numeric_limits< long long >::max(), 2), std::overflow_error);
}

BOOST_AUTO_TEST_SUITE_END()
