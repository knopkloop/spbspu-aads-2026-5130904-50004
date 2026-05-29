#include <boost/test/unit_test.hpp>
#include <string>
#include <stdexcept>
#include "BSTree.hpp"

using Tree = haliullin::BSTree< int, std::string >;

BOOST_AUTO_TEST_SUITE(BSTreeTests)

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
  Tree t;
  BOOST_CHECK(t.isEmpty());
  BOOST_CHECK_EQUAL(t.getSize(), 0);
  BOOST_CHECK_EQUAL(t.height(), 0);
}

BOOST_AUTO_TEST_CASE(PushAndGet)
{
  Tree t;
  t.push(1, "one");
  BOOST_CHECK(!t.isEmpty());
  BOOST_CHECK_EQUAL(t.getSize(), 1);
  BOOST_CHECK_EQUAL(t.get(1), "one");

  t.push(1, "ONE");
  BOOST_CHECK_EQUAL(t.getSize(), 1);
  BOOST_CHECK_EQUAL(t.get(1), "ONE");

  t.push(2, "two");
  BOOST_CHECK_EQUAL(t.getSize(), 2);
  BOOST_CHECK_EQUAL(t.get(2), "two");
}

BOOST_AUTO_TEST_CASE(GetNonexistent)
{
  Tree t;
  BOOST_CHECK_THROW(t.get(42), std::out_of_range);

  const Tree& ct = t;
  BOOST_CHECK_THROW(ct.get(42), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(Erase)
{
  Tree t;
  t.push(1, "one");
  t.push(2, "two");

  t.erase(1);
  BOOST_CHECK_EQUAL(t.getSize(), 1);
  BOOST_CHECK_THROW(t.get(1), std::out_of_range);

  t.erase(2);
  BOOST_CHECK(t.isEmpty());
}

BOOST_AUTO_TEST_CASE(EraseNonexistent)
{
  Tree t;
  BOOST_CHECK_THROW(t.erase(10), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(Clear)
{
  Tree t;
  t.push(5, "five");
  t.push(3, "three");
  t.clear();
  BOOST_CHECK(t.isEmpty());
  BOOST_CHECK_EQUAL(t.getSize(), 0);
  BOOST_CHECK_EQUAL(t.height(), 0);
}

BOOST_AUTO_TEST_CASE(CopyConstructor)
{
  Tree t1;
  t1.push(1, "one");
  t1.push(2, "two");

  Tree t2(t1);
  BOOST_CHECK_EQUAL(t2.getSize(), 2);
  BOOST_CHECK_EQUAL(t2.get(1), "one");

  t2.push(3, "three");
  BOOST_CHECK_EQUAL(t1.getSize(), 2);
}

BOOST_AUTO_TEST_CASE(MoveConstructor)
{
  Tree t1;
  t1.push(1, "one");

  Tree t2(std::move(t1));
  BOOST_CHECK(t1.isEmpty());
  BOOST_CHECK_EQUAL(t2.getSize(), 1);
  BOOST_CHECK_EQUAL(t2.get(1), "one");
}

BOOST_AUTO_TEST_CASE(CopyAssignment)
{
  Tree t1, t2;
  t1.push(1, "one");
  t2 = t1;
  BOOST_CHECK_EQUAL(t2.getSize(), 1);
  t1.push(2, "two");
  BOOST_CHECK_EQUAL(t2.getSize(), 1);
}

BOOST_AUTO_TEST_CASE(MoveAssignment)
{
  Tree t1, t2;
  t1.push(1, "one");
  t2 = std::move(t1);
  BOOST_CHECK(t1.isEmpty());
  BOOST_CHECK_EQUAL(t2.get(1), "one");
}

BOOST_AUTO_TEST_CASE(Swap)
{
  Tree t1, t2;
  t1.push(1, "one");
  t2.push(2, "two");

  t1.swap(t2);
  BOOST_CHECK_EQUAL(t1.get(2), "two");
  BOOST_CHECK_EQUAL(t2.get(1), "one");
}

BOOST_AUTO_TEST_CASE(HeightEmpty)
{
  Tree t;
  BOOST_CHECK_EQUAL(t.height(), 0);
}

BOOST_AUTO_TEST_CASE(HeightSimple)
{
  Tree t;
  t.push(2, "two");
  BOOST_CHECK_EQUAL(t.height(), 1);

  t.push(1, "one");
  t.push(3, "three");
  BOOST_CHECK_EQUAL(t.height(), 2);

  t.push(0, "zero");
  BOOST_CHECK_EQUAL(t.height(), 3);
}

BOOST_AUTO_TEST_CASE(HeightOfSubtree)
{
  Tree t;
  t.push(5, "five");
  t.push(3, "three");
  t.push(7, "seven");
  t.push(2, "two");

  auto it = t.find(3);
  size_t h = t.height(it);
  BOOST_CHECK_EQUAL(h, 2);
}

BOOST_AUTO_TEST_CASE(RotateLeftBasic)
{
  Tree t;
  t.push(10, "10");
  t.push(20, "20");
  t.push(30, "30");
  BOOST_CHECK_EQUAL(t.height(), 3);

  auto it = t.find(20);
  t.rotateLeft(it);
  BOOST_CHECK_EQUAL(t.height(), 2);
  BOOST_CHECK_EQUAL(t.get(10), "10");
  BOOST_CHECK_EQUAL(t.get(20), "20");
  BOOST_CHECK_EQUAL(t.get(30), "30");
}

BOOST_AUTO_TEST_CASE(RotateRightBasic)
{
  Tree t;
  t.push(30, "30");
  t.push(20, "20");
  t.push(10, "10");
  BOOST_CHECK_EQUAL(t.height(), 3);

  auto it = t.find(20);
  t.rotateRight(it);
  BOOST_CHECK_EQUAL(t.height(), 2);
  BOOST_CHECK_EQUAL(t.get(10), "10");
  BOOST_CHECK_EQUAL(t.get(20), "20");
  BOOST_CHECK_EQUAL(t.get(30), "30");
}

BOOST_AUTO_TEST_CASE(RotateLargeLeft)
{
  Tree t;
  t.push(10, "10");
  t.push(30, "30");
  t.push(20, "20");

  auto it = t.find(20);
  t.rotateLargeLeft(it);
  BOOST_CHECK_EQUAL(t.height(), 2);
  BOOST_CHECK_EQUAL(t.get(10), "10");
  BOOST_CHECK_EQUAL(t.get(20), "20");
  BOOST_CHECK_EQUAL(t.get(30), "30");
}

BOOST_AUTO_TEST_CASE(RotateLargeRight)
{
  Tree t;
  t.push(30, "30");
  t.push(10, "10");
  t.push(20, "20");

  auto it = t.find(20);
  t.rotateLargeRight(it);
  BOOST_CHECK_EQUAL(t.height(), 2);
  BOOST_CHECK_EQUAL(t.get(10), "10");
  BOOST_CHECK_EQUAL(t.get(20), "20");
  BOOST_CHECK_EQUAL(t.get(30), "30");
}

BOOST_AUTO_TEST_CASE(RotateInvalidIterator)
{
  Tree t;
  t.push(1, "one");

  auto endIt = t.end();
  BOOST_CHECK_THROW(t.rotateLeft(endIt), std::logic_error);
  BOOST_CHECK_THROW(t.rotateRight(endIt), std::logic_error);

  auto rootIt = t.find(1);
  BOOST_CHECK_THROW(t.rotateLeft(rootIt), std::logic_error);
  BOOST_CHECK_THROW(t.rotateRight(rootIt), std::logic_error);
}

BOOST_AUTO_TEST_CASE(Find)
{
  Tree t;
  t.push(5, "five");

  auto it = t.find(5);
  BOOST_CHECK(it != t.end());
  BOOST_CHECK_EQUAL(it->second, "five");

  auto it2 = t.find(100);
  BOOST_CHECK(it2 == t.end());
}

BOOST_AUTO_TEST_SUITE_END()
