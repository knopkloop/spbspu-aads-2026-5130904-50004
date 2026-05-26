#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include "queue.hpp"

BOOST_AUTO_TEST_SUITE(QueueTests)

BOOST_AUTO_TEST_CASE(PushAndPop)
{
  haliullin::Queue< int > queue;
  BOOST_CHECK(queue.is_empty());
  queue.push(3);
  queue.push(4);
  BOOST_CHECK(!queue.is_empty());
  BOOST_CHECK_EQUAL(queue.pop(), 3);
  BOOST_CHECK_EQUAL(queue.pop(), 4);
  BOOST_CHECK(queue.is_empty());
}

BOOST_AUTO_TEST_CASE(Front)
{
  haliullin::Queue< int > queue;
  queue.push(42);
  BOOST_CHECK_EQUAL(queue.front(), 42);
  queue.pop();
  BOOST_CHECK(queue.is_empty());
}

BOOST_AUTO_TEST_CASE(Exceptions)
{
  haliullin::Queue< int > queue;
  BOOST_CHECK_THROW(queue.pop(), std::runtime_error);
  BOOST_CHECK_THROW(queue.front(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(Clear)
{
  haliullin::Queue< int > queue;
  queue.push(1);
  queue.push(2);
  queue.push(3);
  queue.clear();
  BOOST_CHECK(queue.is_empty());
  BOOST_CHECK_EQUAL(queue.get_size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
