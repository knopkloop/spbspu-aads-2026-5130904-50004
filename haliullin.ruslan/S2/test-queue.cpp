#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include "queue.hpp"

BOOST_AUTO_TEST_SUITE(QueueTests)

BOOST_AUTO_TEST_CASE(push)
{
  haliullin::Queue< int > queue;
  BOOST_CHECK(queue.is_empty());
  BOOST_CHECK_EQUAL(queue.get_size(), 0);

  queue.push(10);
  BOOST_CHECK(!queue.is_empty());
  BOOST_CHECK_EQUAL(queue.get_size(), 1);
  BOOST_CHECK_EQUAL(queue.front(), 10);

  queue.push(20);
  BOOST_CHECK_EQUAL(queue.get_size(), 2);
  BOOST_CHECK_EQUAL(queue.front(), 10);
}

BOOST_AUTO_TEST_CASE(pop)
{
  haliullin::Queue< int > queue;
  queue.push(10);
  queue.push(20);

  queue.pop();
  BOOST_CHECK_EQUAL(queue.get_size(), 1);
  BOOST_CHECK_EQUAL(queue.front(), 20);

  queue.pop();
  BOOST_CHECK(queue.is_empty());
  BOOST_CHECK_EQUAL(queue.get_size(), 0);
}

BOOST_AUTO_TEST_CASE(front)
{
  haliullin::Queue< int > queue;
  queue.push(42);
  BOOST_CHECK_EQUAL(queue.front(), 42);
  queue.push(100);
  BOOST_CHECK_EQUAL(queue.front(), 42);
  queue.pop();
  BOOST_CHECK_EQUAL(queue.front(), 100);
}

BOOST_AUTO_TEST_CASE(get_size)
{
  haliullin::Queue< int > queue;
  BOOST_CHECK_EQUAL(queue.get_size(), 0);
  queue.push(1);
  queue.push(2);
  queue.push(3);
  BOOST_CHECK_EQUAL(queue.get_size(), 3);
  queue.pop();
  BOOST_CHECK_EQUAL(queue.get_size(), 2);
  queue.clear();
  BOOST_CHECK_EQUAL(queue.get_size(), 0);
}

BOOST_AUTO_TEST_CASE(clear)
{
  haliullin::Queue< int > queue;
  queue.push(1);
  queue.push(2);
  queue.push(3);
  BOOST_CHECK(!queue.is_empty());
  queue.clear();
  BOOST_CHECK(queue.is_empty());
  BOOST_CHECK_EQUAL(queue.get_size(), 0);
}

BOOST_AUTO_TEST_CASE(exceptions)
{
  haliullin::Queue< int > queue;
  BOOST_CHECK_THROW(queue.pop(), std::runtime_error);
  BOOST_CHECK_THROW(queue.front(), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()
