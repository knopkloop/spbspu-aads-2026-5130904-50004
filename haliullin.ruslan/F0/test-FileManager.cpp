#include <boost/test/unit_test.hpp>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cstdio>
#include "FileManager.hpp"
#include "AppCore.hpp"

BOOST_AUTO_TEST_SUITE(FileManager_tests)

BOOST_AUTO_TEST_CASE(test_save_empty_core)
{
  haliullin::AppCore core;
  haliullin::FileManager::save("test_empty.txt", core);

  std::ifstream file("test_empty.txt");
  BOOST_CHECK(file.is_open());
  std::string content((std::istreambuf_iterator< char >(file)), std::istreambuf_iterator< char >());
  BOOST_CHECK(content.find("BOOK") == std::string::npos);
  BOOST_CHECK(content.find("CONTACT") == std::string::npos);
  file.close();
  std::remove("test_empty.txt");
}

BOOST_AUTO_TEST_CASE(test_save_and_load_state)
{
  haliullin::AppCore core1;
  core1.createBook("family");
  core1.addContact("family", "+71111111111", "Papa");
  core1.addContact("family", "+72222222222", "Mama Maria");
  core1.reportSpam("+79999999999");
  core1.reportSpam("+79999999999");
  core1.grade("+71111111111", "+72222222222", 5.0);
  core1.grade("+71111111111", "+72222222222", 3.0);

  haliullin::FileManager::save("test_state.txt", core1);
  haliullin::AppCore core2 = haliullin::FileManager::load("test_state.txt");

  const auto& books = core2.getBooks();
  bool hasFamily = false;
  size_t contactCount = 0;
  for (auto it = books.cbegin(); it != books.cend(); ++it)
  {
    if ((*it).first == "family")
    {
      hasFamily = true;
      const auto& pb = (*it).second;
      contactCount = pb.getSize();
      for (auto cit = pb.cbegin(); cit != pb.cend(); ++cit)
      {
        if ((*cit).first == "+72222222222")
        {
          BOOST_CHECK_EQUAL((*cit).second, "Mama Maria");
        }
      }
    }
  }
  BOOST_CHECK(hasFamily);
  BOOST_CHECK_EQUAL(contactCount, 2);

  const auto& spam = core2.getSpam();
  bool hasSpam = false;
  for (auto it = spam.cbegin(); it != spam.cend(); ++it)
  {
    if ((*it).first == "+79999999999")
    {
      hasSpam = true;
      BOOST_CHECK_EQUAL((*it).second, 2);
    }
  }
  BOOST_CHECK(hasSpam);

  const auto& graph = core2.getGraph();
  auto edges = graph.getAllEdges();
  bool hasEdge = false;
  for (size_t i = 0; i < edges.getSize(); ++i)
  {
    if (edges[i].first.first == "+71111111111" && edges[i].first.second == "+72222222222")
    {
      hasEdge = true;
      BOOST_CHECK_EQUAL(edges[i].second.getSize(), 2);
    }
  }
  BOOST_CHECK(hasEdge);

  std::remove("test_state.txt");
}

BOOST_AUTO_TEST_CASE(test_load_nonexistent)
{
  BOOST_CHECK_THROW(haliullin::FileManager::load("nonexistent_file.txt"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_load_invalid_format)
{
  std::ofstream bad_file("test_bad.txt");
  bad_file << "UNKNOWN_TOKEN some data\n";
  bad_file.close();

  BOOST_CHECK_THROW(haliullin::FileManager::load("test_bad.txt"), std::runtime_error);
  std::remove("test_bad.txt");
}

BOOST_AUTO_TEST_CASE(test_load_invalid_book)
{
  std::ofstream bad_file("test_bad_book.txt");
  bad_file << "BOOK\n";
  bad_file.close();

  BOOST_CHECK_THROW(haliullin::FileManager::load("test_bad_book.txt"), std::runtime_error);
  std::remove("test_bad_book.txt");
}

BOOST_AUTO_TEST_CASE(test_load_invalid_contact)
{
  std::ofstream bad_file("test_bad_contact.txt");
  bad_file << "CONTACT family\n";
  bad_file.close();

  BOOST_CHECK_THROW(haliullin::FileManager::load("test_bad_contact.txt"), std::runtime_error);
  std::remove("test_bad_contact.txt");
}

BOOST_AUTO_TEST_CASE(test_load_invalid_spam)
{
  std::ofstream bad_file("test_bad_spam.txt");
  bad_file << "SPAM +71111111111\n";
  bad_file.close();

  BOOST_CHECK_THROW(haliullin::FileManager::load("test_bad_spam.txt"), std::runtime_error);
  std::remove("test_bad_spam.txt");
}

BOOST_AUTO_TEST_CASE(test_load_invalid_edge)
{
  std::ofstream bad_file("test_bad_edge.txt");
  bad_file << "EDGE +71111111111\n";
  bad_file.close();

  BOOST_CHECK_THROW(haliullin::FileManager::load("test_bad_edge.txt"), std::runtime_error);
  std::remove("test_bad_edge.txt");
}

BOOST_AUTO_TEST_CASE(test_load_invalid_edge_weight)
{
  std::ofstream bad_file("test_bad_weight.txt");
  bad_file << "EDGE +71111111111 +72222222222 not_a_number\n";
  bad_file.close();

  BOOST_CHECK_THROW(haliullin::FileManager::load("test_bad_weight.txt"), std::runtime_error);
  std::remove("test_bad_weight.txt");
}

BOOST_AUTO_TEST_SUITE_END()
