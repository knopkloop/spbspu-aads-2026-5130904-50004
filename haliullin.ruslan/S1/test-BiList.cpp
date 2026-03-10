#define BOOST_TEST_MODULE BiListTests
#include <boost/test/included/unit_test.hpp>
#include "BiList.hpp"

using namespace haliullin;

BOOST_AUTO_TEST_CASE(push_front_basic)
{
  BiList<int> lst;
  lst.push_front(5);
  BOOST_CHECK_EQUAL(lst.getsize(), 1);
  lst.push_front(15);
  BOOST_CHECK_EQUAL(lst.getsize(), 2);
  auto it = lst.begin();
  BOOST_CHECK_EQUAL(*it, 15);
  ++it;
  BOOST_CHECK_EQUAL(*it, 5);
}

BOOST_AUTO_TEST_CASE(push_back_basic)
{
  BiList<int> lst;
  lst.push_back(100);
  BOOST_CHECK_EQUAL(lst.getsize(), 1);
  lst.push_back(200);
  BOOST_CHECK_EQUAL(lst.getsize(), 2);
  auto it = lst.begin();
  BOOST_CHECK_EQUAL(*it, 100);
  ++it;
  BOOST_CHECK_EQUAL(*it, 200);
}

BOOST_AUTO_TEST_CASE(pop_front_test)
{
  BiList<int> lst;
  lst.push_back(7);
  lst.push_back(14);
  lst.push_back(21);
  lst.pop_front();
  BOOST_CHECK_EQUAL(lst.getsize(), 2);
  auto it = lst.begin();
  BOOST_CHECK_EQUAL(*it, 14);
  ++it;
  BOOST_CHECK_EQUAL(*it, 21);
  lst.pop_front();
  BOOST_CHECK_EQUAL(lst.getsize(), 1);
  BOOST_CHECK_EQUAL(*lst.begin(), 21);
  lst.pop_front();
  BOOST_CHECK(lst.getsize() == 0);
}

BOOST_AUTO_TEST_CASE(pop_back_test)
{
  BiList<int> lst;
  lst.push_back(5);
  lst.push_back(10);
  lst.push_back(15);
  lst.pop_back();
  BOOST_CHECK_EQUAL(lst.getsize(), 2);
  auto it = lst.begin();
  BOOST_CHECK_EQUAL(*it, 5);
  ++it;
  BOOST_CHECK_EQUAL(*it, 10);
  lst.pop_back();
  BOOST_CHECK_EQUAL(lst.getsize(), 1);
  BOOST_CHECK_EQUAL(*lst.begin(), 5);
  lst.pop_back();
  BOOST_CHECK(lst.getsize() == 0);
}

BOOST_AUTO_TEST_CASE(clear)
{
  BiList<int> lst;
  lst.push_back(3);
  lst.push_back(6);
  lst.push_back(9);
  lst.clear();
  BOOST_CHECK(lst.getsize() == 0);
  BOOST_CHECK(lst.begin() == lst.end());
}

BOOST_AUTO_TEST_CASE(copy_construction)
{
  BiList<int> lst1;
  lst1.push_back(8);
  lst1.push_back(16);
  BiList<int> lst2(lst1);
  BOOST_CHECK_EQUAL(lst2.front(), 8);
  BOOST_CHECK_EQUAL(lst2.back(), 16);
}

BOOST_AUTO_TEST_CASE(move_construction)
{
  BiList<int> lst1;
  lst1.push_back(8);
  lst1.push_back(16);
  BiList<int> lst2(std::move(lst1));
  BOOST_CHECK(lst1.is_empty());
  BOOST_CHECK_EQUAL(lst2.front(), 8);
}
