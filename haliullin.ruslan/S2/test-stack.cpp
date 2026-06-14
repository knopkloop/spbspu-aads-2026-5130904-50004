#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include "stack.hpp"

BOOST_AUTO_TEST_SUITE(Stack_tests)

BOOST_AUTO_TEST_CASE(push)
{
  haliullin::Stack< int > stack;
  BOOST_CHECK(stack.is_empty());
  BOOST_CHECK_EQUAL(stack.get_size(), 0);

  stack.push(10);
  BOOST_CHECK(!stack.is_empty());
  BOOST_CHECK_EQUAL(stack.get_size(), 1);
  BOOST_CHECK_EQUAL(stack.top(), 10);

  stack.push(20);
  BOOST_CHECK_EQUAL(stack.get_size(), 2);
  BOOST_CHECK_EQUAL(stack.top(), 20);
}

BOOST_AUTO_TEST_CASE(pop)
{
  haliullin::Stack< int > stack;
  stack.push(10);
  stack.push(20);

  stack.pop();
  BOOST_CHECK_EQUAL(stack.get_size(), 1);
  BOOST_CHECK_EQUAL(stack.top(), 10);

  stack.pop();
  BOOST_CHECK(stack.is_empty());
  BOOST_CHECK_EQUAL(stack.get_size(), 0);
}

BOOST_AUTO_TEST_CASE(top)
{
  haliullin::Stack< int > stack;
  stack.push(42);
  BOOST_CHECK_EQUAL(stack.top(), 42);
  stack.push(100);
  BOOST_CHECK_EQUAL(stack.top(), 100);
  stack.pop();
  BOOST_CHECK_EQUAL(stack.top(), 42);
}

BOOST_AUTO_TEST_CASE(get_size)
{
  haliullin::Stack< int > stack;
  BOOST_CHECK_EQUAL(stack.get_size(), 0);
  stack.push(1);
  stack.push(2);
  stack.push(3);
  BOOST_CHECK_EQUAL(stack.get_size(), 3);
  stack.pop();
  BOOST_CHECK_EQUAL(stack.get_size(), 2);
  stack.clear();
  BOOST_CHECK_EQUAL(stack.get_size(), 0);
}

BOOST_AUTO_TEST_CASE(clear)
{
  haliullin::Stack< int > stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);
  BOOST_CHECK(!stack.is_empty());
  stack.clear();
  BOOST_CHECK(stack.is_empty());
  BOOST_CHECK_EQUAL(stack.get_size(), 0);
}

BOOST_AUTO_TEST_CASE(exceptions)
{
  haliullin::Stack< int > stack;
  BOOST_CHECK_THROW(stack.pop(), std::runtime_error);
  BOOST_CHECK_THROW(stack.top(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(emplace)
{
  haliullin::Stack< std::string > stack;
  std::string& ref = stack.emplace(5, 'a');

  BOOST_CHECK_EQUAL(stack.get_size(), 1);
  BOOST_CHECK_EQUAL(stack.top(), "aaaaa");
  BOOST_CHECK_EQUAL(&ref, &stack.top());

  ref += "b";
  BOOST_CHECK_EQUAL(stack.top(), "aaaaab");

  stack.emplace(3, 'x');
  BOOST_CHECK_EQUAL(stack.get_size(), 2);
  BOOST_CHECK_EQUAL(stack.top(), "xxx");

  stack.pop();
  BOOST_CHECK_EQUAL(stack.top(), "aaaaab");
}

BOOST_AUTO_TEST_SUITE_END()
