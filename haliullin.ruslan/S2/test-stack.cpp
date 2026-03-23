#include <boost/test/unit_test.hpp>
#include "stack.hpp"
#include <stdexcept>

BOOST_AUTO_TEST_SUITE(StackTests)

BOOST_AUTO_TEST_CASE(PushAndDrop)
{
  haliullin::Stack< int > stack;
  BOOST_CHECK(stack.is_empty());
  stack.push(3);
  stack.push(4);
  BOOST_CHECK(!stack.is_empty());
  BOOST_CHECK_EQUAL(stack.drop(), 4);
  BOOST_CHECK_EQUAL(stack.drop(), 3);
  BOOST_CHECK(stack.is_empty());
}

BOOST_AUTO_TEST_CASE(Top)
{
  haliullin::Stack< int > stack;
  stack.push(42);
  BOOST_CHECK_EQUAL(stack.top(), 42);
  stack.drop();
  BOOST_CHECK(stack.is_empty());
}

BOOST_AUTO_TEST_CASE(Exceptions)
{
  haliullin::Stack< int > stack;
  BOOST_CHECK_THROW(stack.drop(), std::runtime_error);
  BOOST_CHECK_THROW(stack.top(), std::runtime_error);

}

BOOST_AUTO_TEST_CASE(Clear)
{
  haliullin::Stack< int > stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);
  stack.clear();
  BOOST_CHECK(stack.is_empty());
  BOOST_CHECK_EQUAL(stack.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
