#include "FileManager.hpp"
#include <fstream>
#include <stdexcept>
#include <string>

void haliullin::FileManager::save(const std::string& filename, const AppCore& core)
{
  std::ofstream file(filename);
  if (!file.is_open())
  {
    throw std::runtime_error("Cannot open file for writing");
  }

  const auto& books = core.getBooks();
  for (auto it = books.cbegin(); it != books.cend(); ++it)
  {
    const std::string& bookName = (*it).first;
    if (bookName == "global")
    {
      continue;
    }
    file << "BOOK " << bookName << "\n";
    const auto& phoneBook = (*it).second;
    for (auto cit = phoneBook.cbegin(); cit != phoneBook.cend(); ++cit)
    {
      file << "CONTACT " <<  bookName << " " << (*cit).first << " " << (*cit).second << "\n";
    }
  }

  const auto& spam = core.getSpam();
  for (auto it = spam.cbegin(); it != spam.cend(); ++it)
  {
    file << "SPAM " << (*it).first << " " << (*it).second << "\n";
  }

  const auto& graph = core.getGraph();
  auto allEdges = graph.getAllEdges();
  for (size_t i = 0; i < allEdges.getSize(); ++i)
  {
    const auto& key = allEdges[i].first;
    const auto& ratings = allEdges[i].second;
    file << "EDGE " << key.first << " " << key.second;
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

haliullin::AppCore haliullin::FileManager::load(const std::string& filename)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    throw std::runtime_error("Cannot open file for reading");
  }

  AppCore core;
  std::string token;
  while (file >> token)
  {
    if (token == "BOOK")
    {
      std::string bookName;
      if (!(file >> bookName))
      {
        throw std::runtime_error("Invalid BOOK format");
      }
      core.createPhonebook(bookName);
    }
    else if (token == "CONTACT")
    {
      std::string bookName, number, name;
      if (!(file >> bookName >> number))
      {
        throw std::runtime_error("Invalid CONTACT format");
      }
      std::getline(file >> std::ws, name);
      if (name.empty())
      {
        throw std::runtime_error("Empty contact name");
      }
      core.addContact(bookName, number, name);
    }
    else if (token == "SPAM")
    {
      std::string number;
      int count = 0;
      if (!(file >> number >> count))
      {
        throw std::runtime_error("Invalid SPAM format");
      }
      for (int i = 0; i < count; ++i)
      {
        core.reportSpam(number);
      }
    }
    else if (token == "EDGE")
    {
      std::string from, to;
      if (!(file >> from >> to))
      {
        throw std::runtime_error("Invalid EDGE format");
      }
      double weight;
      while (file >> weight)
      {
        core.grade(from, to, weight);
      }
      if (file.fail() && !file.eof())
      {
        throw std::runtime_error("Invalid weight in EDGE");
      }
      file.clear();
    }
    else
    {
      throw std::runtime_error("Unknown token: " + token);
    }
  }

  if (file.bad() || (file.fail() && !file.eof()))
  {
    throw std::runtime_error("Read error");
  }

  return core;
}
