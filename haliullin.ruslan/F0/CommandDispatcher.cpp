#include "CommandDispatcher.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>
#include "AppCore.hpp"
#include "FileManager.hpp"
#include "IOGuard.hpp"

haliullin::CommandDispatcher::CommandDispatcher():
  core_(),
  commands_()
{
  commands_.add("create-book", &CommandDispatcher::cmdCreateBook);
  commands_.add("remove-book", &CommandDispatcher::cmdRemoveBook);
  commands_.add("add-contact", &CommandDispatcher::cmdAddContact);
  commands_.add("remove-contact", &CommandDispatcher::cmdRemoveContact);
  commands_.add("rename-book", &CommandDispatcher::cmdRenameBook);
  commands_.add("merge", &CommandDispatcher::cmdMerge);
  commands_.add("copy-contact", &CommandDispatcher::cmdCopyContact);
  commands_.add("show", &CommandDispatcher::cmdShow);
  commands_.add("report", &CommandDispatcher::cmdReportSpam);
  commands_.add("grade", &CommandDispatcher::cmdGrade);
  commands_.add("show-connections", &CommandDispatcher::cmdShowConnections);
  commands_.add("disconnect", &CommandDispatcher::cmdDisconnect);
  commands_.add("recommend", &CommandDispatcher::cmdRecommend);
  commands_.add("save", &CommandDispatcher::cmdSave);
  commands_.add("load", &CommandDispatcher::cmdLoad);
  commands_.add("exit", &CommandDispatcher::cmdExit);
}

void haliullin::CommandDispatcher::execute(std::istream& in, std::ostream& out)
{
  std::string command;
  while (in >> command)
  {
    func_t handler = nullptr;
    if (commands_.has(command))
    {
      handler = commands_.get(command);
    }
    try
    {
      require(handler != nullptr);
      detail::IOGuard guard(out);
      (this->*handler)(in, out);
      out << std::flush;
    }
    catch (const std::exception&)
    {
      out << "<INVALID COMMAND>\n" << std::flush;
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}

void haliullin::CommandDispatcher::require(bool condition) const
{
  if (!condition)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void haliullin::CommandDispatcher::require(std::istream& in) const
{
  if (!in)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

bool haliullin::CommandDispatcher::isNumberValid(const std::string& number) const
{
  if (number.empty() || number[0] != '+')
  {
    return false;
  }
  for (size_t i = 1; i < number.size(); ++i)
  {
    if (!std::isdigit(number[i]))
    {
      return false;
    }
  }
  return number.size() == 12;
}

void haliullin::CommandDispatcher::cmdCreateBook(std::istream& in, std::ostream& out)
{
  std::string name;
  in >> name;
  require(in);
  require(name != "global");
  core_.createBook(name);
  out << "Phonebook <" << name << "> created\n";
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

void haliullin::CommandDispatcher::cmdRemoveBook(std::istream& in, std::ostream& out)
{
  std::string name;
  in >> name;
  require(in);
  require(name != "global");
  core_.removeBook(name);
  out << "Phonebook <" << name << "> removed\n";
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

void haliullin::CommandDispatcher::cmdAddContact(std::istream& in, std::ostream& out)
{
  std::string book, number, name;
  in >> book >> number;
  require(in);
  require(isNumberValid(number));
  while (in.peek() == ' ')
  {
    in.get();
  }
  while (in.peek() != '\n' && in.peek() != EOF)
  {
    name += static_cast< char >(in.get());
  }
  require(!name.empty());
  core_.addContact(book, number, name);
  out << "Contact " << number << " added to <" << book << ">\n";
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

void haliullin::CommandDispatcher::cmdRemoveContact(std::istream& in, std::ostream& out)
{
  std::string book, number;
  in >> book >> number;
  require(in);
  require(isNumberValid(number));
  core_.removeContact(book, number);
  out << "Contact " << number << " removed from <" << book << ">\n";
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

void haliullin::CommandDispatcher::cmdRenameBook(std::istream& in, std::ostream& out)
{
  std::string oldName, newName;
  in >> oldName >> newName;
  require(in);
  require(oldName != "global");
  core_.renameBook(oldName, newName);
  out << "Renamed phonebook <" << oldName << "> into <" << newName << ">\n";
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

void haliullin::CommandDispatcher::cmdMerge(std::istream& in, std::ostream& out)
{
  std::string newBook, book1, book2;
  in >> newBook >> book1 >> book2;
  require(in);
  core_.mergeBooks(newBook, book1, book2);
  out << "Merged <" << book1 << "> and <" << book2 << "> into <" << newBook << ">\n";
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

void haliullin::CommandDispatcher::cmdCopyContact(std::istream& in, std::ostream& out)
{
  std::string fromBook, toBook, number;
  in >> fromBook >> toBook >> number;
  require(in);
  require(isNumberValid(number));
  core_.copyContact(fromBook, toBook, number);
  out << "Contact " << number << " has been copied to <" << toBook << "> from <" << fromBook << ">\n";
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

void haliullin::CommandDispatcher::cmdShow(std::istream& in, std::ostream& out)
{
  std::string book;
  in >> book;
  require(in);
  while (in.peek() == ' ')
  {
    in.get();
  }
  if (in.peek() == '\n' || in.peek() == EOF)
  {
    core_.showBook(book, out);
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  else
  {
    std::string number;
    in >> number;
    require(isNumberValid(number));
    core_.showContact(book, number, out);
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}

void haliullin::CommandDispatcher::cmdReportSpam(std::istream& in, std::ostream& out)
{
  std::string number;
  in >> number;
  require(in);
  require(isNumberValid(number));
  core_.reportSpam(number);
  out << "Spam report recorded for " << number << "\n";
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

void haliullin::CommandDispatcher::cmdGrade(std::istream& in, std::ostream& out)
{
  std::string from, to;
  double value = 0.0;
  in >> from >> to >> value;
  require(in);
  require(isNumberValid(from) && isNumberValid(to));
  require(value >= 0.0 && value <= 5.0);
  while (in.peek() == ' ')
  {
    in.get();
  }
  require(in.peek() == '\n' || in.peek() == EOF);
  core_.grade(from, to, value);
  out << "Rating from " << from << " to " << to << " added (" << value << ")\n";
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

void haliullin::CommandDispatcher::cmdShowConnections(std::istream& in, std::ostream& out)
{
  std::string number;
  in >> number;
  require(in);
  require(isNumberValid(number));
  while (in.peek() == ' ')
  {
    in.get();
  }
  std::string mode = "all";
  if (in.peek() != '\n' && in.peek() != EOF)
  {
    in >> mode;
    require(in);
    require(mode == "in" || mode == "out");
  }
  core_.showConnections(number, mode, out);
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

void haliullin::CommandDispatcher::cmdDisconnect(std::istream& in, std::ostream& out)
{
  std::string from, to;
  in >> from >> to;
  require(in);
  require(isNumberValid(from) && isNumberValid(to));
  core_.disconnect(from, to);
  out << "Rating from " << from << " to " << to << " removed\n";
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

void haliullin::CommandDispatcher::cmdRecommend(std::istream& in, std::ostream& out)
{
  std::string book, number;
  double minRating = 4.0;
  int maxSpam = -1;
  size_t depth = 2;
  in >> book >> number;
  require(in);
  require(isNumberValid(number));

  auto skipSpaces = [&in]()
  {
    while (in.peek() == ' ')
    {
      in.get();
    }
  };

  skipSpaces();
  if (in.peek() != EOF && in.peek() != '\n')
  {
    in >> minRating;
    require(in);
  }
  skipSpaces();
  if (in.peek() != EOF && in.peek() != '\n')
  {
    in >> maxSpam;
    require(in);
  }
  skipSpaces();
  if (in.peek() != EOF && in.peek() != '\n')
  {
    in >> depth;
    require(in);
    require(depth >= 2);
  }

  auto result = core_.recommend(book, number, minRating, maxSpam, depth);
  auto& subgraph = result.first;
  auto& candidates = result.second;

  if (candidates.isEmpty())
  {
    out << "No recommendations found\n";
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    return;
  }

  for (size_t i = 1; i < candidates.getSize(); ++i)
  {
    auto key = candidates[i];
    size_t j = i;
    while (j > 0 && candidates[j - 1].second < key.second)
    {
      candidates[j] = candidates[j - 1];
      --j;
    }
    candidates[j] = key;
  }

  out << "Recommendations for " << number << " in <" << book << ">:\n";
  for (size_t i = 0; i < candidates.getSize(); ++i)
  {
    out << candidates[i].first << " (score: " << candidates[i].second << ")\n";
  }

  auto allEdges = subgraph.getAllEdges();
  out << "Recommendation subgraph:\n";
  for (size_t i = 0; i < allEdges.getSize(); ++i)
  {
    const auto& key = allEdges[i].first;
    double avgW = subgraph.getAverageWeight(key.first, key.second);
    out << "  " << key.first << " -> " << key.second << " : " << avgW << "\n";
  }
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

void haliullin::CommandDispatcher::cmdSave(std::istream& in, std::ostream& out)
{
  std::string filename;
  in >> filename;
  require(in);
  FileManager::save(filename, core_);
  out << "The current session is saved to " << filename << "\n";
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

void haliullin::CommandDispatcher::cmdLoad(std::istream& in, std::ostream& out)
{
  std::string filename;
  in >> filename;
  require(in);
  AppCore newCore = FileManager::load(filename);
  core_.swap(newCore);
  out << "Session loaded from " << filename << "\n";
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

void haliullin::CommandDispatcher::cmdExit(std::istream& in, std::ostream& out)
{
  out << "Do you want to save the current session? (y/n)\n" << std::flush;
  std::string answer;
  in >> answer;
  if (answer == "y" || answer == "Y")
  {
    out << "Enter the filename\n" << std::flush;
    std::string filename;
    in >> filename;
    FileManager::save(filename, core_);
    out << "The current session is saved to " << filename << "\n";
  }
  out << "Session ended, data cleared\n";
  in.setstate(std::ios_base::eofbit);
}
