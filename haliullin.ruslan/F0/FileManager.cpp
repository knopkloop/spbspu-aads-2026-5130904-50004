#include "FileManager.hpp"
#include <fstream>
#include <stdexcept>
#include <cstdio>
#include <limits>
#include <string>
#include "AppCore.hpp"
#include "RobinHashTable.hpp"
#include "MurMurHash.hpp"

namespace
{
  using ParseFunc = void(*)(std::ifstream&, haliullin::AppCore&);

  void parseBook(std::ifstream& file, haliullin::AppCore& core)
  {
    std::string bookName;
    if (!(file >> bookName))
    {
      throw std::runtime_error("Invalid BOOK format");
    }
    core.createBook(bookName);
  }

  void parseContact(std::ifstream& file, haliullin::AppCore& core)
  {
    std::string bookName;
    std::string number;
    std::string name;
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

  void parseSpam(std::ifstream& file, haliullin::AppCore& core)
  {
    std::string number;
    size_t count = 0;
    if (!(file >> number >> count))
    {
      throw std::runtime_error("Invalid SPAM format");
    }
    for (size_t i = 0; i < count; ++i)
    {
      core.reportSpam(number);
    }
  }

  void parseEdge(std::ifstream& file, haliullin::AppCore& core)
  {
    std::string from;
    std::string to;
    if (!(file >> from >> to))
    {
      throw std::runtime_error("Invalid EDGE format");
    }

    while (file.peek() != '\n' && file.peek() != EOF)
    {
      double weight = 0.0;
      if (file >> weight)
      {
        core.grade(from, to, weight);
      }
      else
      {
        file.clear();
        file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        throw std::runtime_error("Invalid weight in EDGE");
      }
    }
    file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}

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
      file << "CONTACT " << bookName << " " << (*cit).first << " " << (*cit).second << "\n";
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

  RobinHashTable< std::string, ParseFunc, MurMurHash, std::equal_to< std::string > > loadDisp;
  loadDisp.add("BOOK", &parseBook);
  loadDisp.add("CONTACT", &parseContact);
  loadDisp.add("SPAM", &parseSpam);
  loadDisp.add("EDGE", &parseEdge);

  AppCore core;
  std::string token;
  while (file >> token)
  {
    if (loadDisp.has(token))
    {
      ParseFunc func = loadDisp.get(token);
      func(file, core);
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
