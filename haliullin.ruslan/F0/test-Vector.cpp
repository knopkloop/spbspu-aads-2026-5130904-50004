#include <boost/test/unit_test.hpp>
#include <string>
#include <stdexcept>
#include "Vector.hpp"

BOOST_AUTO_TEST_SUITE(Vector_tests)

using Vec = haliullin::Vector< int >;
using StrVec = haliullin::Vector< std::string >;

BOOST_AUTO_TEST_CASE(test_default_constructor)
{
  Vec v;
  BOOST_CHECK(v.isEmpty());
  BOOST_CHECK_EQUAL(v.getSize(), 0);
  BOOST_CHECK_EQUAL(v.getCapacity(), 0);
}

BOOST_AUTO_TEST_CASE(test_size_constructor)
{
  Vec v1(5);
  BOOST_CHECK_EQUAL(v1.getSize(), 5);
  BOOST_CHECK_EQUAL(v1.getCapacity(), 5);
  BOOST_CHECK_EQUAL(v1[0], 0);
  BOOST_CHECK_EQUAL(v1[4], 0);

  Vec v2(0);
  BOOST_CHECK(v2.isEmpty());
  BOOST_CHECK_EQUAL(v2.getSize(), 0);
  BOOST_CHECK_EQUAL(v2.getCapacity(), 0);
}

BOOST_AUTO_TEST_CASE(test_size_value_constructor)
{
  StrVec v(3, "test");
  BOOST_CHECK_EQUAL(v.getSize(), 3);
  BOOST_CHECK_EQUAL(v.getCapacity(), 3);
  BOOST_CHECK_EQUAL(v[0], "test");
  BOOST_CHECK_EQUAL(v[2], "test");
}

BOOST_AUTO_TEST_CASE(test_copy_constructor)
{
  Vec v1;
  v1.pushBack(1);
  v1.pushBack(2);
  Vec v2(v1);
  BOOST_CHECK_EQUAL(v2.getSize(), 2);
  BOOST_CHECK_EQUAL(v2[0], 1);
  BOOST_CHECK_EQUAL(v2[1], 2);
  BOOST_CHECK(v1 == v2);

  Vec empty1;
  Vec empty2(empty1);
  BOOST_CHECK(empty2.isEmpty());
}

BOOST_AUTO_TEST_CASE(test_move_constructor)
{
  Vec v1;
  v1.pushBack(10);
  v1.pushBack(20);
  Vec v2(std::move(v1));
  BOOST_CHECK_EQUAL(v2.getSize(), 2);
  BOOST_CHECK_EQUAL(v2[0], 10);
  BOOST_CHECK(v1.isEmpty());
  BOOST_CHECK_EQUAL(v1.getCapacity(), 0);
}

BOOST_AUTO_TEST_CASE(test_copy_assignment)
{
  Vec v1;
  v1.pushBack(1);
  Vec v2;
  v2.pushBack(99);
  v2 = v1;
  BOOST_CHECK_EQUAL(v2.getSize(), 1);
  BOOST_CHECK_EQUAL(v2[0], 1);
  BOOST_CHECK(v1 == v2);

  v2 = v2;
  BOOST_CHECK_EQUAL(v2.getSize(), 1);
}

BOOST_AUTO_TEST_CASE(test_move_assignment)
{
  Vec v1;
  v1.pushBack(10);
  Vec v2;
  v2.pushBack(99);
  v2 = std::move(v1);
  BOOST_CHECK_EQUAL(v2.getSize(), 1);
  BOOST_CHECK_EQUAL(v2[0], 10);
  BOOST_CHECK(v1.isEmpty());
}

BOOST_AUTO_TEST_CASE(test_swap)
{
  Vec v1;
  v1.pushBack(1);
  Vec v2;
  v2.pushBack(2);
  v2.pushBack(3);
  v1.swap(v2);
  BOOST_CHECK_EQUAL(v1.getSize(), 2);
  BOOST_CHECK_EQUAL(v1[0], 2);
  BOOST_CHECK_EQUAL(v2.getSize(), 1);
  BOOST_CHECK_EQUAL(v2[0], 1);
}

BOOST_AUTO_TEST_CASE(test_at)
{
  Vec v;
  v.pushBack(10);
  v.pushBack(20);
  BOOST_CHECK_EQUAL(v.at(0), 10);
  v.at(1) = 30;
  BOOST_CHECK_EQUAL(v.at(1), 30);

  const Vec& cv = v;
  BOOST_CHECK_EQUAL(cv.at(0), 10);

  BOOST_CHECK_THROW(v.at(2), std::out_of_range);
  BOOST_CHECK_THROW(cv.at(5), std::out_of_range);

  Vec empty;
  BOOST_CHECK_THROW(empty.at(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_operator_bracket)
{
  Vec v;
  v.pushBack(5);
  v.pushBack(10);
  BOOST_CHECK_EQUAL(v[0], 5);
  v[1] = 42;
  BOOST_CHECK_EQUAL(v[1], 42);

  const Vec& cv = v;
  BOOST_CHECK_EQUAL(cv[0], 5);
  BOOST_CHECK_EQUAL(cv[1], 42);
}

BOOST_AUTO_TEST_CASE(test_isEmpty)
{
  Vec v;
  BOOST_CHECK(v.isEmpty());
  v.pushBack(1);
  BOOST_CHECK(!v.isEmpty());
  v.erase(0);
  BOOST_CHECK(v.isEmpty());
}

BOOST_AUTO_TEST_CASE(test_getSize)
{
  Vec v;
  BOOST_CHECK_EQUAL(v.getSize(), 0);
  v.pushBack(1);
  BOOST_CHECK_EQUAL(v.getSize(), 1);
  v.pushBack(2);
  BOOST_CHECK_EQUAL(v.getSize(), 2);
  v.erase(0);
  BOOST_CHECK_EQUAL(v.getSize(), 1);
}

BOOST_AUTO_TEST_CASE(test_getCapacity)
{
  Vec v;
  BOOST_CHECK_EQUAL(v.getCapacity(), 0);
  v.pushBack(1);
  BOOST_CHECK_EQUAL(v.getCapacity(), 1);
  v.pushBack(2);
  BOOST_CHECK_EQUAL(v.getCapacity(), 2);
  v.pushBack(3);
  BOOST_CHECK(v.getCapacity() >= 3);
}

BOOST_AUTO_TEST_CASE(test_pushBack)
{
  Vec v;
  v.pushBack(1);
  BOOST_CHECK_EQUAL(v.getSize(), 1);
  BOOST_CHECK_EQUAL(v[0], 1);

  v.pushBack(2);
  BOOST_CHECK_EQUAL(v.getSize(), 2);
  BOOST_CHECK_EQUAL(v[1], 2);

  StrVec sv;
  std::string s = "lvalue";
  sv.pushBack(s);
  sv.pushBack(std::string("rvalue"));
  BOOST_CHECK_EQUAL(sv.getSize(), 2);
  BOOST_CHECK_EQUAL(sv[0], "lvalue");
  BOOST_CHECK_EQUAL(sv[1], "rvalue");
}

BOOST_AUTO_TEST_CASE(test_insert)
{
  Vec v;
  v.pushBack(1);
  v.pushBack(3);
  v.insert(1, 2);
  BOOST_CHECK_EQUAL(v.getSize(), 3);
  BOOST_CHECK_EQUAL(v[0], 1);
  BOOST_CHECK_EQUAL(v[1], 2);
  BOOST_CHECK_EQUAL(v[2], 3);

  v.insert(0, 0);
  BOOST_CHECK_EQUAL(v[0], 0);

  v.insert(v.getSize(), 4);
  BOOST_CHECK_EQUAL(v[v.getSize() - 1], 4);

  Vec empty;
  empty.insert(0, 42);
  BOOST_CHECK_EQUAL(empty[0], 42);

  BOOST_CHECK_THROW(v.insert(100, 5), std::out_of_range);
  BOOST_CHECK_THROW(empty.insert(5, 1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_erase)
{
  Vec v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);

  v.erase(1);
  BOOST_CHECK_EQUAL(v.getSize(), 3);
  BOOST_CHECK_EQUAL(v[0], 1);
  BOOST_CHECK_EQUAL(v[1], 3);

  v.erase(0);
  BOOST_CHECK_EQUAL(v[0], 3);

  v.erase(v.getSize() - 1);
  BOOST_CHECK_EQUAL(v.getSize(), 1);

  v.erase(0);
  BOOST_CHECK(v.isEmpty());

  BOOST_CHECK_THROW(v.erase(0), std::out_of_range);

  Vec v2;
  v2.pushBack(1);
  BOOST_CHECK_THROW(v2.erase(1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_insSort)
{
  Vec v;
  v.insSort();
  BOOST_CHECK(v.isEmpty());

  v.pushBack(42);
  v.insSort();
  BOOST_CHECK_EQUAL(v[0], 42);

  v.pushBack(5);
  v.pushBack(2);
  v.pushBack(8);
  v.pushBack(1);
  v.pushBack(9);
  v.pushBack(3);
  v.insSort();

  BOOST_CHECK_EQUAL(v[0], 1);
  BOOST_CHECK_EQUAL(v[1], 2);
  BOOST_CHECK_EQUAL(v[2], 3);
  BOOST_CHECK_EQUAL(v[3], 5);
  BOOST_CHECK_EQUAL(v[4], 8);
  BOOST_CHECK_EQUAL(v[5], 9);
  BOOST_CHECK_EQUAL(v[6], 42);
}

BOOST_AUTO_TEST_CASE(test_reallocate)
{
  Vec v;
  v.pushBack(10);
  v.pushBack(20);
  v.pushBack(30);
  size_t oldCap = v.getCapacity();

  v.reserve(oldCap + 50);
  BOOST_CHECK(v.getCapacity() > oldCap);
  BOOST_CHECK_EQUAL(v.getSize(), 3);
  BOOST_CHECK_EQUAL(v[0], 10);
  BOOST_CHECK_EQUAL(v[1], 20);
  BOOST_CHECK_EQUAL(v[2], 30);

  v.pushBack(40);
  v.pushBack(50);
  BOOST_CHECK_EQUAL(v.getSize(), 5);
  BOOST_CHECK_EQUAL(v[3], 40);
  BOOST_CHECK_EQUAL(v[4], 50);

  StrVec sv;
  sv.pushBack("a");
  sv.pushBack("b");
  sv.reserve(100);
  BOOST_CHECK(sv.getCapacity() >= 100);
  BOOST_CHECK_EQUAL(sv[0], "a");
  BOOST_CHECK_EQUAL(sv[1], "b");
}

BOOST_AUTO_TEST_CASE(test_reserve)
{
  Vec v;
  v.reserve(100);
  BOOST_CHECK_EQUAL(v.getSize(), 0);
  BOOST_CHECK_EQUAL(v.getCapacity(), 100);

  v.pushBack(1);
  v.reserve(50);
  BOOST_CHECK_EQUAL(v.getCapacity(), 100);
}

BOOST_AUTO_TEST_CASE(test_shrinkToFit)
{
  Vec v;
  v.reserve(100);
  v.pushBack(1);
  v.pushBack(2);
  v.shrinkToFit();
  BOOST_CHECK_EQUAL(v.getSize(), 2);
  BOOST_CHECK_EQUAL(v.getCapacity(), 2);

  Vec empty;
  empty.reserve(50);
  empty.shrinkToFit();
  BOOST_CHECK_EQUAL(empty.getCapacity(), 0);

  Vec v2;
  v2.pushBack(1);
  v2.shrinkToFit();
  BOOST_CHECK_EQUAL(v2.getCapacity(), 1);
}

BOOST_AUTO_TEST_CASE(test_resize)
{
  Vec v;
  v.pushBack(1);
  v.pushBack(2);
  v.resize(5, 99);
  BOOST_CHECK_EQUAL(v.getSize(), 5);
  BOOST_CHECK_EQUAL(v[0], 1);
  BOOST_CHECK_EQUAL(v[2], 99);
  BOOST_CHECK_EQUAL(v[4], 99);

  v.resize(1);
  BOOST_CHECK_EQUAL(v.getSize(), 1);
  BOOST_CHECK_EQUAL(v[0], 1);

  v.resize(0);
  BOOST_CHECK(v.isEmpty());

  v.resize(3);
  BOOST_CHECK_EQUAL(v.getSize(), 3);
  BOOST_CHECK_EQUAL(v[0], 0);
}

BOOST_AUTO_TEST_CASE(test_operator_equal)
{
  Vec v1;
  v1.pushBack(1);
  v1.pushBack(2);
  Vec v2;
  v2.pushBack(1);
  v2.pushBack(2);
  Vec v3;
  v3.pushBack(1);
  Vec empty1, empty2;

  BOOST_CHECK(v1 == v2);
  BOOST_CHECK(!(v1 == v3));
  BOOST_CHECK(!(v1 == empty1));
  BOOST_CHECK(empty1 == empty2);
}

BOOST_AUTO_TEST_CASE(test_operator_not_equal)
{
  Vec v1;
  v1.pushBack(1);
  Vec v2;
  v2.pushBack(2);
  Vec v3;
  v3.pushBack(1);
  v3.pushBack(2);

  BOOST_CHECK(v1 != v2);
  BOOST_CHECK(!(v1 != v3));
}

BOOST_AUTO_TEST_CASE(test_operator_less)
{
  Vec v1;
  v1.pushBack(1);
  v1.pushBack(2);
  Vec v2;
  v2.pushBack(1);
  v2.pushBack(3);
  Vec v3;
  v3.pushBack(1);
  Vec empty1, empty2;

  BOOST_CHECK(v1 < v2);
  BOOST_CHECK(!(v2 < v1));
  BOOST_CHECK(v3 < v1);
  BOOST_CHECK(!(v1 < v3));
  BOOST_CHECK(!(v1 < v1));
  BOOST_CHECK(empty1 < v1);
  BOOST_CHECK(!(empty1 < empty2));
}

BOOST_AUTO_TEST_SUITE_END()
