#include <boost/test/unit_test.hpp>
#include <string>
#include <functional>
#include <stdexcept>
#include "RobinHashTable.hpp"
#include "MurMurHash.hpp"

BOOST_AUTO_TEST_SUITE(RobinHashTable_tests)

using Table = haliullin::RobinHashTable< std::string, int, haliullin::detail::MurMurHash, std::equal_to< std::string > >;

BOOST_AUTO_TEST_CASE(test_constructor)
{
  Table t1;
  BOOST_CHECK(t1.isEmpty());
  BOOST_CHECK_EQUAL(t1.getSize(), 0);
  BOOST_CHECK(t1.getCapacity() >= 16);

  Table t2(32, 0.5);
  BOOST_CHECK_EQUAL(t2.getCapacity(), 32);
}

BOOST_AUTO_TEST_CASE(test_copy_constructor)
{
  Table t1;
  t1.add("a", 1);
  Table t2(t1);
  BOOST_CHECK_EQUAL(t2.getSize(), 1);
  BOOST_CHECK(t2.has("a"));
  BOOST_CHECK_EQUAL(t2.get("a"), 1);

  Table empty1;
  Table empty2(empty1);
  BOOST_CHECK(empty2.isEmpty());
}

BOOST_AUTO_TEST_CASE(test_move_constructor)
{
  Table t1;
  t1.add("x", 10);
  Table t2(std::move(t1));
  BOOST_CHECK_EQUAL(t2.getSize(), 1);
  BOOST_CHECK(t2.has("x"));
  BOOST_CHECK(t1.isEmpty());
}

BOOST_AUTO_TEST_CASE(test_copy_assignment)
{
  Table t1;
  t1.add("a", 1);
  Table t2;
  t2.add("b", 2);
  t2 = t1;
  BOOST_CHECK_EQUAL(t2.getSize(), 1);
  BOOST_CHECK(t2.has("a"));
  BOOST_CHECK(!t2.has("b"));

  t2 = t2;
  BOOST_CHECK_EQUAL(t2.getSize(), 1);
}

BOOST_AUTO_TEST_CASE(test_move_assignment)
{
  Table t1;
  t1.add("a", 1);
  Table t2;
  t2 = std::move(t1);
  BOOST_CHECK_EQUAL(t2.getSize(), 1);
  BOOST_CHECK(t2.has("a"));
  BOOST_CHECK(t1.isEmpty());
}

BOOST_AUTO_TEST_CASE(test_swap)
{
  Table t1;
  t1.add("a", 1);
  Table t2;
  t2.add("b", 2);
  t2.add("c", 3);
  t1.swap(t2);
  BOOST_CHECK_EQUAL(t1.getSize(), 2);
  BOOST_CHECK(t1.has("b"));
  BOOST_CHECK(t1.has("c"));
  BOOST_CHECK_EQUAL(t2.getSize(), 1);
  BOOST_CHECK(t2.has("a"));
}

BOOST_AUTO_TEST_CASE(test_add)
{
  Table t;
  t.add("x", 10);
  BOOST_CHECK_EQUAL(t.getSize(), 1);
  BOOST_CHECK_EQUAL(t.get("x"), 10);

  t.add("x", 20);
  BOOST_CHECK_EQUAL(t.getSize(), 1);
  BOOST_CHECK_EQUAL(t.get("x"), 20);

  t.add("y", 30);
  BOOST_CHECK_EQUAL(t.getSize(), 2);
  BOOST_CHECK_EQUAL(t.get("y"), 30);
}

BOOST_AUTO_TEST_CASE(test_erase)
{
  Table t;
  t.add("a", 1);
  t.add("b", 2);
  t.add("c", 3);

  t.erase("b");
  BOOST_CHECK_EQUAL(t.getSize(), 2);
  BOOST_CHECK(!t.has("b"));
  BOOST_CHECK(t.has("a"));
  BOOST_CHECK(t.has("c"));

  BOOST_CHECK_THROW(t.erase("b"), std::out_of_range);
  BOOST_CHECK_THROW(t.erase("z"), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_has)
{
  Table t;
  t.add("a", 1);
  BOOST_CHECK(t.has("a"));
  BOOST_CHECK(!t.has("b"));
}

BOOST_AUTO_TEST_CASE(test_get)
{
  Table t;
  t.add("a", 1);
  t.add("b", 2);

  BOOST_CHECK_EQUAL(t.get("a"), 1);
  t.get("a") = 100;
  BOOST_CHECK_EQUAL(t.get("a"), 100);

  const Table& ct = t;
  BOOST_CHECK_EQUAL(ct.get("b"), 2);

  BOOST_CHECK_THROW(t.get("c"), std::out_of_range);
  BOOST_CHECK_THROW(ct.get("c"), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_find)
{
  Table t;
  t.add("x", 10);
  t.add("y", 20);

  auto it1 = t.find("x");
  BOOST_CHECK(it1 != t.end());
  BOOST_CHECK_EQUAL(it1->first, "x");
  BOOST_CHECK_EQUAL(it1->second, 10);

  it1->second = 99;
  BOOST_CHECK_EQUAL(t.get("x"), 99);

  auto it2 = t.find("z");
  BOOST_CHECK(it2 == t.end());

  const Table& ct = t;
  auto cit = ct.find("y");
  BOOST_CHECK(cit != ct.cend());
  BOOST_CHECK_EQUAL(cit->second, 20);

  auto cit2 = ct.find("missing");
  BOOST_CHECK(cit2 == ct.cend());
}

BOOST_AUTO_TEST_CASE(test_isEmpty)
{
  Table t;
  BOOST_CHECK(t.isEmpty());
  t.add("a", 1);
  BOOST_CHECK(!t.isEmpty());
  t.erase("a");
  BOOST_CHECK(t.isEmpty());
}

BOOST_AUTO_TEST_CASE(test_getSize)
{
  Table t;
  BOOST_CHECK_EQUAL(t.getSize(), 0);
  t.add("a", 1);
  BOOST_CHECK_EQUAL(t.getSize(), 1);
  t.add("b", 2);
  BOOST_CHECK_EQUAL(t.getSize(), 2);
  t.erase("a");
  BOOST_CHECK_EQUAL(t.getSize(), 1);
}

BOOST_AUTO_TEST_CASE(test_getCapacity)
{
  Table t;
  size_t initialCap = t.getCapacity();
  BOOST_CHECK(initialCap >= 16);

  t.add("k1", 1);
  t.add("k2", 2);
  t.add("k3", 3);
  t.add("k4", 4);
  t.add("k5", 5);
  t.add("k6", 6);
  t.add("k7", 7);
  t.add("k8", 8);
  t.add("k9", 9);
  t.add("k10", 10);
  t.add("k11", 11);
  t.add("k12", 12);
  t.add("k13", 13);
  t.add("k14", 14);
  t.add("k15", 15);

  BOOST_CHECK_EQUAL(t.getSize(), 15);

  t.add("k16", 16);
  BOOST_CHECK(t.getCapacity() > initialCap);
}

BOOST_AUTO_TEST_SUITE_END()
