#include <boost/test/unit_test.hpp>
#include <BiList.hpp>

using namespace haliullin;

BOOST_AUTO_TEST_SUITE(BiListTests)

BOOST_AUTO_TEST_CASE(copy_move)
{
  BiList< int > lst1;
  lst1.emplace_front(4);
  lst1.emplace_front(5);
  lst1.emplace_front(6);
  BiList< int > lst2(lst1);
  BOOST_CHECK_EQUAL(lst2.front(), 6);
  BiList< int > list3(std::move(lst1));
  BOOST_CHECK_EQUAL(list3.front(), 6);
  BOOST_CHECK(lst1.is_empty());
}

BOOST_AUTO_TEST_CASE(is_empty)
{
  BiList< int > lst;
  BOOST_CHECK(lst.is_empty());
  lst.emplace_back(1);
  BOOST_CHECK(!lst.is_empty());
}

BOOST_AUTO_TEST_CASE(get_size)
{
  BiList< int > lst;
  BOOST_CHECK_EQUAL(lst.get_size(), 0);
  lst.emplace_back(1);
  lst.emplace_back(2);
  BOOST_CHECK_EQUAL(lst.get_size(), 2);
}

BOOST_AUTO_TEST_CASE(front)
{
  BiList< int > lst;
  lst.emplace_back(10);
  lst.emplace_back(20);
  BOOST_CHECK_EQUAL(lst.front(), 10);
  lst.front() = 100;
  BOOST_CHECK_EQUAL(lst.front(), 100);
}

BOOST_AUTO_TEST_CASE(back)
{
  BiList< int > lst;
  lst.emplace_back(10);
  lst.emplace_back(20);
  BOOST_CHECK_EQUAL(lst.back(), 20);
  lst.back() = 200;
  BOOST_CHECK_EQUAL(lst.back(), 200);
}

BOOST_AUTO_TEST_CASE(emplace_front)
{
  BiList< int > lst;
  lst.emplace_front(5);
  lst.emplace_front(15);
  BOOST_CHECK_EQUAL(lst.front(), 15);
  BOOST_CHECK_EQUAL(lst.get_size(), 2);
}

BOOST_AUTO_TEST_CASE(emplace_back)
{
  BiList< int > lst;
  lst.emplace_back(10);
  lst.emplace_back(20);
  BOOST_CHECK_EQUAL(lst.back(), 20);
  BOOST_CHECK_EQUAL(lst.get_size(), 2);
}

BOOST_AUTO_TEST_CASE(emplace)
{
  BiList< int > lst;
  lst.emplace_back(1);
  lst.emplace_back(3);

  auto newIt = lst.emplace(lst.begin(), 2);

  BOOST_CHECK_EQUAL(lst.get_size(), 3);
  BOOST_CHECK_EQUAL(*newIt, 2);
  BOOST_CHECK_EQUAL(lst.front(), 2);
}

BOOST_AUTO_TEST_CASE(pop_front)
{
  BiList< int > lst;
  lst.emplace_back(1);
  lst.emplace_back(2);
  lst.pop_front();
  BOOST_CHECK_EQUAL(lst.front(), 2);
  BOOST_CHECK_EQUAL(lst.get_size(), 1);
}

BOOST_AUTO_TEST_CASE(pop_back)
{
  BiList< int > lst;
  lst.emplace_back(1);
  lst.emplace_back(2);
  lst.pop_back();
  BOOST_CHECK_EQUAL(lst.back(), 1);
  BOOST_CHECK_EQUAL(lst.get_size(), 1);
}

BOOST_AUTO_TEST_CASE(erase)
{
  BiList< int > lst;
  lst.emplace_back(1);
  lst.emplace_back(2);
  lst.emplace_back(3);
  auto it = lst.begin();
  ++it;
  lst.erase(it);
  BOOST_CHECK_EQUAL(lst.get_size(), 2);
  BOOST_CHECK_EQUAL(lst.front(), 1);
  BOOST_CHECK_EQUAL(lst.back(), 3);
}

BOOST_AUTO_TEST_CASE(clear)
{
  BiList< int > lst;
  lst.emplace_back(1);
  lst.emplace_back(2);
  lst.emplace_back(3);
  lst.clear();
  BOOST_CHECK(lst.is_empty());
  BOOST_CHECK_EQUAL(lst.get_size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
