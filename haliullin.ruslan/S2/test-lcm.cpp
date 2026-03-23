#include <boost/test/unit_test.hpp>
#include "evaluate.hpp"
#include "math_op.hpp"
#include <stdexcept>

BOOST_AUTO_TEST_SUITE(LcmTests)

BOOST_AUTO_TEST_CASE(Basic)
{
  BOOST_CHECK_EQUAL(haliullin::lcm(4, 6), 12);
  BOOST_CHECK_EQUAL(haliullin::lcm(3, 5), 15);
  BOOST_CHECK_EQUAL(haliullin::lcm(10, 15), 30);
}

BOOST_AUTO_TEST_CASE(InExpression)
{
  BOOST_CHECK_EQUAL(haliullin::evaluate(haliullin::infixToPostfix("4 lcm 6")), 12);
  BOOST_CHECK_EQUAL(haliullin::evaluate(haliullin::infixToPostfix("7 lcm 12 - 24")), 60);
}

BOOST_AUTO_TEST_CASE(Exceptions)
{
  BOOST_CHECK_THROW(haliullin::lcm(0, 5), std::logic_error);
  BOOST_CHECK_THROW(haliullin::lcm(5, 0), std::logic_error);
  BOOST_CHECK_THROW(haliullin::lcm(haliullin::MAX, 2), std::overflow_error);
}

BOOST_AUTO_TEST_SUITE_END()
