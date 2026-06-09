#include "AppCore.hpp"
#include <stdexcept>
#include <string>
#include <ostream>
#include <utility>

haliullin::AppCore::AppCore():
  books_(),
  spam_(),
  graph_()
{}

haliullin::AppCore::PhoneBook& haliullin::AppCore::getBook(const std::string& name)
{
  if (!books_.has(name))
  {
    throw std::out_of_range("Phonebook not found");
  }
  return books_.get(name);
}

const haliullin::AppCore::PhoneBook& haliullin::AppCore::getBook(const std::string& name) const
{
  if (!books_.has(name))
  {
    throw std::out_of_range("Phonebook not found");
  }
  return books_.get(name);
}

void haliullin::AppCore::createPhonebook(const std::string& name)
{
  if (books_.has(name))
  {
    throw std::logic_error("Phonebook already exists");
  }
  if (name == "global")
  {
    throw std::logic_error("Cannot create global phonebook");
  }
  PhoneBook emptyBook;
  books_.add(name, emptyBook);
}

void haliullin::AppCore::removePhonebook(const std::string& name)
{
  if (name == "global")
  {
    throw std::logic_error("Cannot remove global phonebook");
  }
  getBook(name);
  books_.erase(name);
}

void haliullin::AppCore::renameBook(const std::string& oldName, const std::string& newName)
{
  if (oldName == "global")
  {
    throw std::logic_error("Cannot rename global phonebook");
  }
  if (books_.has(newName))
  {
    throw std::logic_error("Target name already exists");
  }
  PhoneBook& book = getBook(oldName);
  PhoneBook temp(book);
  books_.erase(oldName);
  try
  {
    books_.add(newName, temp);
  }
  catch (...)
  {
    books_.add(oldName, temp);
    throw;
  }
}
