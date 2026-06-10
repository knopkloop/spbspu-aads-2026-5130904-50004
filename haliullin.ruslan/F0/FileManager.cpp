#include "FileManager.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

void haliullin::FileManager::save(const std::string& filename, const AppCore& core)
{
  std::ofstream file(filename);
  if (!file.is_open())
  {
    throw std::runtime_error("Cannot open file for writing");
  }

  const char* const BOOK_TOKEN = "BOOK";
  const char* const CONTACT_TOKEN = "CONTACT";
  const char* const SPAM_TOKEN = "SPAM";
  const char* const EDGE_TOKEN = "EDGE";

  const auto& books = core.getBooks();
  for (auto it = books.cbegin(); it != books.cend(); ++it)
  {
    const std::string& bookName = (*it).first;
    if (bookName == "global")
    {
      continue;
    }
    file << BOOK_TOKEN << " " << bookName << "\n";
    const auto& phoneBook = (*it).second;
    for (auto cit = phoneBook.cbegin(); cit != phoneBook.cend(); ++cit)
    {
      file << CONTACT_TOKEN << " " << bookName << " " << (*cit).first << " " << (*cit).second << "\n";
    }
  }

  const auto& spam = core.getSpam();
  for (auto it = spam.cbegin(); it != spam.cend(); ++it)
  {
    file << SPAM_TOKEN << " " << (*it).first << " " << (*it).second << "\n";
  }

  const auto& graph = core.getGraph();
  auto allEdges = graph.getAllEdges();
  for (size_t i = 0; i < allEdges.getSize(); ++i)
  {
    const auto& key = allEdges[i].first;
    const auto& ratings = allEdges[i].second;
    file << EDGE_TOKEN << " " << key.first << " " << key.second;
    for (size_t j = 0; j < ratings.getSize(); ++j)
    {
      file << " " << ratings[j];
    }
    file << "\n";
  }

  if (!file.good())
  {
    throw std::runtime_error("Write error");
  }
}
