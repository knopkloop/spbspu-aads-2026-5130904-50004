#include <boost/test/unit_test.hpp>
#include <string>
#include <stdexcept>
#include "HashTable.hpp"
#include "SipHash.hpp"
#include "Equal.hpp"

BOOST_AUTO_TEST_SUITE(HashTableTests)

using Table = haliullin::HashTable< std::string, int, haliullin::SipHash, haliullin::Equal >;

BOOST_AUTO_TEST_CASE(test_default_constructor)
{
  Table ht;
  BOOST_CHECK(ht.isEmpty());
  BOOST_CHECK_EQUAL(ht.getSize(), 0);
  BOOST_CHECK(ht.getCapacity() >= 16);
}

BOOST_AUTO_TEST_CASE(test_constructor_with_capacity)
{
  Table ht(37);
  BOOST_CHECK(ht.isEmpty());
  BOOST_CHECK_EQUAL(ht.getSize(), 0);
  BOOST_CHECK_EQUAL(ht.getCapacity(), 37);
}

BOOST_AUTO_TEST_CASE(test_add_and_size)
{
  Table ht(31);
  ht.add("a", 5);
  BOOST_CHECK_EQUAL(ht.getSize(), 1);
  BOOST_CHECK(!ht.isEmpty());

  ht.add("b", 7);
  BOOST_CHECK_EQUAL(ht.getSize(), 2);
}

BOOST_AUTO_TEST_CASE(test_has)
{
  Table ht(47);
  ht.add("c", 10);
  ht.add("d", 20);

  BOOST_CHECK(ht.has("c"));
  BOOST_CHECK(ht.has("d"));
  BOOST_CHECK(!ht.has("e"));
}

BOOST_AUTO_TEST_CASE(test_get)
{
  Table ht(61);
  ht.add("f", 15);
  ht.add("g", 25);

  BOOST_CHECK_EQUAL(ht.get("f"), 15);
  BOOST_CHECK_EQUAL(ht.get("g"), 25);

  ht.get("f") = 99;
  BOOST_CHECK_EQUAL(ht.get("f"), 99);
}

BOOST_AUTO_TEST_CASE(test_erase)
{
  Table ht(73);
  ht.add("first", 111);
  ht.add("second", 222);

  ht.erase("first");
  BOOST_CHECK_EQUAL(ht.getSize(), 1);
  BOOST_CHECK(!ht.has("first"));
  BOOST_CHECK(ht.has("second"));
}

BOOST_AUTO_TEST_CASE(test_add_update_existing)
{
  Table ht(83);
  ht.add("x", 33);
  BOOST_CHECK_THROW(ht.add("x", 44), std::invalid_argument);
  BOOST_CHECK_EQUAL(ht.getSize(), 1);
  BOOST_CHECK_EQUAL(ht.get("x"), 33);
}

BOOST_AUTO_TEST_CASE(test_copy_constructor)
{
  Table ht1(67);
  ht1.add("m", 7);
  ht1.add("n", 14);

  Table ht2 = ht1;

  BOOST_CHECK_EQUAL(ht2.getSize(), 2);
  BOOST_CHECK(ht2.has("m"));
  BOOST_CHECK(ht2.has("n"));
  BOOST_CHECK_EQUAL(ht2.get("m"), 7);
  BOOST_CHECK_EQUAL(ht1.getSize(), 2);
}

BOOST_AUTO_TEST_CASE(test_move_constructor)
{
  Table ht1(79);
  ht1.add("first", 50);
  ht1.add("second", 60);

  Table ht2 = std::move(ht1);

  BOOST_CHECK_EQUAL(ht2.getSize(), 2);
  BOOST_CHECK(ht2.has("first"));
  BOOST_CHECK(ht2.has("second"));
  BOOST_CHECK(ht1.isEmpty());
}

BOOST_AUTO_TEST_CASE(test_rehash)
{
  Table ht(11);
  ht.add("q", 1);
  ht.add("w", 2);
  ht.add("e", 3);
  ht.add("r", 4);
  ht.add("t", 5);
  ht.add("y", 6);

  ht.rehash(37);
  BOOST_CHECK_EQUAL(ht.getSize(), 6);
  BOOST_CHECK(ht.has("q"));
  BOOST_CHECK(ht.has("w"));
  BOOST_CHECK(ht.has("e"));
  BOOST_CHECK(ht.has("r"));
  BOOST_CHECK(ht.has("t"));
  BOOST_CHECK(ht.has("y"));
}

BOOST_AUTO_TEST_SUITE_END()
