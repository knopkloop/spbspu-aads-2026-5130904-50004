#include "CommandDispatcher.hpp"
#include <stdexcept>
#include <string>
#include <iostream>
#include <limits>
#include "AppCore.hpp"

haliullin::CommandDispatcher::CommandDispatcher():
  core_()
{
  commands_.add("create-phonebook", &CommandDispatcher::cmdCreatePhonebook);
  commands_.add("remove-phonebook", &CommandDispatcher::cmdRemovePhonebook);
  commands_.add("add-contact", &CommandDispatcher::cmdAddContact);
  commands_.add("remove-contact", &CommandDispatcher::cmdRemoveContact);
  commands_.add("show", &CommandDispatcher::cmdShow);
  commands_.add("merge", &CommandDispatcher::cmdMerge);
  commands_.add("copy-contact", &CommandDispatcher::cmdCopyContact);
  commands_.add("rename-book", &CommandDispatcher::cmdRenameBook);
  commands_.add("report", &CommandDispatcher::cmdReportSpam);
  commands_.add("grade", &CommandDispatcher::cmdGrade);
  commands_.add("disconnect", &CommandDispatcher::cmdDisconnect);
  commands_.add("show-connections", &CommandDispatcher::cmdShowConnections);
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
    require(handler != nullptr);

    try
    {
      (this->*handler)(in, out);
    }
    catch (const std::logic_error& e)
    {
      out << e.what() << '\n';
    }
    catch (const std::runtime_error& e)
    {
      out << e.what() << '\n';
    }
    catch (const std::exception&)
    {
      out << "<INVALID COMMAND>\n";
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

void haliullin::CommandDispatcher::cmdCreatePhonebook(std::istream& in, std::ostream& out)
{
  std::string name;
  in >> name;
  require(in);
  require(name != "global");

  core_.createPhonebook(name);
  out << "phonebook <" << name << "> created\n";
}

void haliullin::CommandDispatcher::cmdRemovePhonebook(std::istream& in, std::ostream& out)
{
  std::string name;
  in >> name;
  require(in);
  require(name != "global");

  core_.removePhonebook(name);
  out << "phonebook <" << name << "> removed\n";
}

void haliullin::CommandDispatcher::cmdAddContact(std::istream& in, std::ostream& out)
{
  std::string book, number, name;
  in >> book >> number;
  require(in);
  std::getline(in >> std::ws, name);
  require(!name.empty());
  require(isNumberValid(number));

  core_.addContact(book, number, name);
  out << "contact " << number << " added to <" << book << ">\n";
}

void haliullin::CommandDispatcher::cmdRemoveContact(std::istream& in, std::ostream& out)
{
  std::string book, number;
  in >> book >> number;
  require(in);
  require(isNumberValid(number));

  core_.removeContact(book, number);
  out << "contact " << number << " removed from <" << book << ">\n";
}

void haliullin::CommandDispatcher::cmdShow(std::istream& in, std::ostream& out)
{
  std::string book;
  in >> book;
  require(in);

  std::string nextToken;
  in >> nextToken;
  if (!in || nextToken.empty())
  {
    core_.showBook(book, out);
  }
  else
  {
    require(isNumberValid(nextToken));
    core_.showContact(book, nextToken, out);
  }
}
