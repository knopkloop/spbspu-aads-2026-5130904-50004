#include <boost/test/unit_test.hpp>
#include <functional>
#include <BiList.hpp>

BOOST_AUTO_TEST_SUITE(BiList_tests)

BOOST_AUTO_TEST_CASE(copy_move)
{
  haliullin::BiList< int > lst1;
  lst1.emplace_front(4);
  lst1.emplace_front(5);
  lst1.emplace_front(6);
  haliullin::BiList< int > lst2(lst1);
  BOOST_CHECK_EQUAL(lst2.front(), 6);
  haliullin::BiList< int > list3(std::move(lst1));
  BOOST_CHECK_EQUAL(list3.front(), 6);
  BOOST_CHECK(lst1.is_empty());
}

BOOST_AUTO_TEST_CASE(is_empty)
{
  haliullin::BiList< int > lst;
  BOOST_CHECK(lst.is_empty());
  lst.emplace_back(1);
  BOOST_CHECK(!lst.is_empty());
}

BOOST_AUTO_TEST_CASE(get_size)
{
  haliullin::BiList< int > lst;
  BOOST_CHECK_EQUAL(lst.get_size(), 0);
  lst.emplace_back(1);
  lst.emplace_back(2);
  BOOST_CHECK_EQUAL(lst.get_size(), 2);
}

BOOST_AUTO_TEST_CASE(front)
{
  haliullin::BiList< int > lst;
  lst.emplace_back(10);
  lst.emplace_back(20);
  BOOST_CHECK_EQUAL(lst.front(), 10);
  lst.front() = 100;
  BOOST_CHECK_EQUAL(lst.front(), 100);
}

BOOST_AUTO_TEST_CASE(back)
{
  haliullin::BiList< int > lst;
  lst.emplace_back(10);
  lst.emplace_back(20);
  BOOST_CHECK_EQUAL(lst.back(), 20);
  lst.back() = 200;
  BOOST_CHECK_EQUAL(lst.back(), 200);
}

BOOST_AUTO_TEST_CASE(emplace_front)
{
  haliullin::BiList< int > lst;
  lst.emplace_front(5);
  lst.emplace_front(15);
  BOOST_CHECK_EQUAL(lst.front(), 15);
  BOOST_CHECK_EQUAL(lst.get_size(), 2);
}

BOOST_AUTO_TEST_CASE(emplace_back)
{
  haliullin::BiList< int > lst;
  lst.emplace_back(10);
  lst.emplace_back(20);
  BOOST_CHECK_EQUAL(lst.back(), 20);
  BOOST_CHECK_EQUAL(lst.get_size(), 2);
}

BOOST_AUTO_TEST_CASE(emplace)
{
  haliullin::BiList< int > lst;
  lst.emplace_back(1);
  lst.emplace_back(3);
  auto newIt = lst.emplace(lst.begin(), 2);
  BOOST_CHECK_EQUAL(lst.get_size(), 3);
  BOOST_CHECK_EQUAL(*newIt, 2);
  BOOST_CHECK_EQUAL(lst.front(), 2);
}

BOOST_AUTO_TEST_CASE(pop_front)
{
  haliullin::BiList< int > lst;
  lst.emplace_back(1);
  lst.emplace_back(2);
  lst.pop_front();
  BOOST_CHECK_EQUAL(lst.front(), 2);
  BOOST_CHECK_EQUAL(lst.get_size(), 1);
}

BOOST_AUTO_TEST_CASE(pop_back)
{
  haliullin::BiList< int > lst;
  lst.emplace_back(1);
  lst.emplace_back(2);
  lst.pop_back();
  BOOST_CHECK_EQUAL(lst.back(), 1);
  BOOST_CHECK_EQUAL(lst.get_size(), 1);
}

BOOST_AUTO_TEST_CASE(erase)
{
  haliullin::BiList< int > lst;
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
  haliullin::BiList< int > lst;
  lst.emplace_back(1);
  lst.emplace_back(2);
  lst.emplace_back(3);
  lst.clear();
  BOOST_CHECK(lst.is_empty());
  BOOST_CHECK_EQUAL(lst.get_size(), 0);
}

BOOST_AUTO_TEST_CASE(splice)
{
  haliullin::BiList< int > a;
  haliullin::BiList< int > b;
  a.emplace_back(1);
  a.emplace_back(2);
  b.emplace_back(3);
  b.emplace_back(4);

  a.splice(a.end(), b);
  BOOST_CHECK_EQUAL(a.get_size(), 4);
  BOOST_CHECK(b.is_empty());
  BOOST_CHECK_EQUAL(a.front(), 1);
  BOOST_CHECK_EQUAL(a.back(), 4);

  haliullin::BiList< int > c;
  haliullin::BiList< int > d;
  c.emplace_back(10);
  c.emplace_back(30);
  d.emplace_back(20);

  auto it = c.begin();
  ++it;
  c.splice(it, d, d.begin());

  BOOST_CHECK_EQUAL(c.get_size(), 3);
  BOOST_CHECK(d.is_empty());

  auto check_it = c.begin();
  BOOST_CHECK_EQUAL(*check_it++, 10);
  BOOST_CHECK_EQUAL(*check_it++, 20);
  BOOST_CHECK_EQUAL(*check_it, 30);

  haliullin::BiList< int > e;
  haliullin::BiList< int > f;
  e.emplace_back(1);
  e.emplace_back(5);
  f.emplace_back(2);
  f.emplace_back(3);
  f.emplace_back(4);

  auto pos = e.begin();
  ++pos;
  e.splice(pos, f, f.begin(), f.end());

  BOOST_CHECK_EQUAL(e.get_size(), 5);
  BOOST_CHECK(f.is_empty());

  int expected = 1;
  for (auto iter = e.begin(); iter != e.end(); ++iter)
  {
    BOOST_CHECK_EQUAL(*iter, expected++);
  }
}

BOOST_AUTO_TEST_CASE(merge)
{
  haliullin::BiList< int > a;
  haliullin::BiList< int > b;
  a.emplace_back(1);
  a.emplace_back(3);
  a.emplace_back(5);
  b.emplace_back(2);
  b.emplace_back(4);
  b.emplace_back(6);

  a.merge(b);
  BOOST_CHECK_EQUAL(a.get_size(), 6);
  BOOST_CHECK(b.is_empty());

  int expected = 1;
  for (auto it = a.begin(); it != a.end(); ++it)
  {
    BOOST_CHECK_EQUAL(*it, expected++);
  }

  haliullin::BiList< int > c;
  haliullin::BiList< int > empty;
  c.emplace_back(1);
  c.emplace_back(2);
  c.merge(empty);
  BOOST_CHECK_EQUAL(c.get_size(), 2);

  empty.merge(c);
  BOOST_CHECK_EQUAL(empty.get_size(), 2);
  BOOST_CHECK(c.is_empty());

  haliullin::BiList< int > d;
  haliullin::BiList< int > e;
  d.emplace_back(5);
  d.emplace_back(3);
  d.emplace_back(1);
  e.emplace_back(6);
  e.emplace_back(4);
  e.emplace_back(2);

  d.merge(e, std::greater< int >());
  BOOST_CHECK_EQUAL(d.get_size(), 6);
  BOOST_CHECK_EQUAL(d.front(), 6);
  BOOST_CHECK_EQUAL(d.back(), 1);
}

BOOST_AUTO_TEST_CASE(sort)
{
  haliullin::BiList< int > lst;
  lst.emplace_back(5);
  lst.emplace_back(2);
  lst.emplace_back(8);
  lst.emplace_back(1);
  lst.emplace_back(9);
  lst.emplace_back(3);

  lst.sort();

  int expected[] = {1, 2, 3, 5, 8, 9};
  int idx = 0;
  for (auto it = lst.begin(); it != lst.end(); ++it, ++idx)
  {
    BOOST_CHECK_EQUAL(*it, expected[idx]);
  }

  haliullin::BiList< int > empty;
  empty.sort();
  BOOST_CHECK(empty.is_empty());

  haliullin::BiList< int > single;
  single.emplace_back(42);
  single.sort();
  BOOST_CHECK_EQUAL(single.front(), 42);

  haliullin::BiList< int > desc;
  desc.emplace_back(5);
  desc.emplace_back(2);
  desc.emplace_back(8);
  desc.sort(std::greater< int >());
  BOOST_CHECK_EQUAL(desc.front(), 8);
  BOOST_CHECK_EQUAL(desc.back(), 2);
}

BOOST_AUTO_TEST_CASE(partition)
{
  auto is_even = [](int x)
  {
    return x % 2 == 0;
  };
  haliullin::BiList< int > lst;
  for (int i = 1; i <= 6; ++i)
  {
    lst.emplace_back(i);
  }
  auto pivot = lst.partition(is_even);
  BOOST_CHECK_EQUAL(lst.get_size(), 6);
  for (auto it = lst.begin(); it != pivot; ++it)
  {
    BOOST_CHECK(*it % 2 == 0);
  }
  for (auto it = pivot; it != lst.end(); ++it)
  {
    BOOST_CHECK(*it % 2 != 0);
  }
  haliullin::BiList< int > all_true;
  all_true.emplace_back(2);
  all_true.emplace_back(4);
  all_true.emplace_back(6);
  auto pivot2 = all_true.partition(is_even);
  BOOST_CHECK(pivot2 == all_true.end());

  haliullin::BiList< int > all_false;
  all_false.emplace_back(1);
  all_false.emplace_back(3);
  all_false.emplace_back(5);
  auto pivot3 = all_false.partition(is_even);
  BOOST_CHECK(pivot3 == all_false.begin());

  haliullin::BiList< int > empty;
  auto pivot4 = empty.partition(is_even);
  BOOST_CHECK(pivot4 == empty.end());
  BOOST_CHECK(empty.is_empty());
}

BOOST_AUTO_TEST_SUITE_END()
