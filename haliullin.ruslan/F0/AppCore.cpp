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

void haliullin::AppCore::mergeBooks(const std::string& newName, const std::string& book1, const std::string& book2)
{
  if (books_.has(newName))
  {
    throw std::logic_error("Target phonebook already exists");
  }

  const PhoneBook& b1 = getBook(book1);
  const PhoneBook& b2 = getBook(book2);

  PhoneBook merged;
  for (auto it = b1.cbegin(); it != b1.cend(); ++it)
  {
    merged.add((*it).first, (*it).second);
  }
  for (auto it = b2.cbegin(); it != b2.cend(); ++it)
  {
    if (!merged.has((*it).first))
    {
      merged.add((*it).first, (*it).second);
    }
  }
  books_.add(newName, merged);
}

void haliullin::AppCore::addContact(const std::string& book, const std::string& number, const std::string& name)
{
  if (book == "global")
  {
    throw std::logic_error("Cannot add contacts to global phonebook");
  }
  PhoneBook& pb = getBook(book);
  if (pb.has(number))
  {
    throw std::logic_error("Number already exists in this phonebook");
  }
  pb.add(number, name);
}

void haliullin::AppCore::removeContact(const std::string& book, const std::string& number)
{
  if (book == "global")
  {
    throw std::logic_error("Cannot remove contacts from global phonebook");
  }
  PhoneBook& pb = getBook(book);
  if (!pb.has(number))
  {
    throw std::logic_error("Number not found in phonebook");
  }
  pb.erase(number);
}

void haliullin::AppCore::copyContact(const std::string& fromBook, const std::string& toBook, const std::string& number)
{
  if (fromBook == "global" || toBook == "global")
  {
    throw std::logic_error("Cannot copy to/from global phonebook");
  }
  PhoneBook& src = getBook(fromBook);
  PhoneBook& dst = getBook(toBook);
  if (!src.has(number))
  {
    throw std::logic_error("Number not found in source phonebook");
  }
  if (dst.has(number))
  {
    throw std::logic_error("Number already exists in target phonebook");
  }
  dst.add(number, src.get(number));
}

void haliullin::AppCore::showBook(const std::string& book, std::ostream& out) const
{
  const PhoneBook& pb = getBook(book);
  out << "Book <" << book << ">: " << pb.getSize() << " contacts\n";

  Vector< std::pair< std::string, std::string > > contacts;
  for (auto it = pb.cbegin(); it != pb.cend(); ++it)
  {
    contacts.pushBack(*it);
  }
  contacts.insSort();

  for (size_t i = 0; i < contacts.getSize(); ++i)
  {
    const auto& c = contacts[i];
    out << c.first << " " << c.second;
    int spamCount = spam_.has(c.first) ? spam_.get(c.first) : 0;
    out << " [spam: " << spamCount << "]\n";
  }
}

void haliullin::AppCore::showContact(const std::string& book, const std::string& number, std::ostream& out) const
{
  const PhoneBook& pb = getBook(book);
  if (!pb.has(number))
  {
    throw std::logic_error("Number not found in phonebook");
  }

  out << "Number: " << number << "\n";
  out << "Name: " << pb.get(number) << "\n";
  int spamCount = spam_.has(number) ? spam_.get(number) : 0;
  out << "Spam reports: " << spamCount << "\n";

  auto outbound = graph_.getOutbound(number);
  if (!outbound.isEmpty())
  {
    out << "Rated contacts:";
    for (size_t i = 0; i < outbound.getSize(); ++i)
    {
      out << " " << outbound[i].first << " (" << outbound[i].second << ")";
    }
    out << "\n";
  }
}

void haliullin::AppCore::reportSpam(const std::string& number)
{
  if (spam_.has(number))
  {
    spam_.get(number) += 1;
  }
  else
  {
    spam_.add(number, 1);
  }
}

void haliullin::AppCore::grade(const std::string& from, const std::string& to, double value)
{
  if (value < 0.0 || value > 5.0)
  {
    throw std::logic_error("Grade must be between 0 and 5");
  }
  graph_.addEdge(from, to, value);
}

void haliullin::AppCore::disconnect(const std::string& from, const std::string& to)
{
  graph_.removeEdges(from, to);
}

void haliullin::AppCore::showConnections(const std::string& number, const std::string& mode, std::ostream& out) const
{
  if (mode == "out" || mode == "all")
  {
    auto outbound = graph_.getOutbound(number);
    out << "Outgoing ratings:\n";
    if (outbound.isEmpty())
    {
      out << "  none\n";
    }
    else
    {
      for (size_t i = 0; i < outbound.getSize(); ++i)
      {
        out << "  -> " << outbound[i].first << " : " << outbound[i].second << "\n";
      }
    }
  }
  if (mode == "in" || mode == "all")
  {
    auto inbound = graph_.getInbound(number);
    out << "Incoming ratings:\n";
    if (inbound.isEmpty())
    {
      out << "  none\n";
    }
    else
    {
      for (size_t i = 0; i < inbound.getSize(); ++i)
      {
        out << "  <- " << inbound[i].first << " : " << inbound[i].second << "\n";
      }
    }
  }
}

haliullin::AppCore::RecommendationResult haliullin::AppCore::recommend(const std::string& book, const std::string& number, double minRating,
int maxSpam, size_t depth) const
{
  const PhoneBook& pb = getBook(book);
  if (depth < 2)
  {
    throw std::logic_error("Depth must be at least 2");
  }

  RobinHashTable< std::string, std::pair< double, size_t >, detail::MurMurHash, std::equal_to< std::string > > candidates;
  SocialGraph subgraph;
  Vector< std::pair< std::string, double > > current;
  current.pushBack(std::make_pair(number, 0.0));
  RobinHashTable< std::string, bool, detail::MurMurHash, std::equal_to< std::string > > visited;

  for (size_t step = 0; step < depth; ++step)
  {
    Vector< std::pair< std::string, double > > nextLevel;
    for (size_t i = 0; i < current.getSize(); ++i)
    {
      const std::string& from = current[i].first;
      double curWeight = current[i].second;
      visited.add(from, true);
      auto outbound = graph_.getOutbound(from);
      for (size_t j = 0; j < outbound.getSize(); ++j)
      {
        const std::string& to = outbound[j].first;
        double edgeWeight = outbound[j].second;
        if (edgeWeight < minRating)
        {
          continue;
        }
        if (step == depth - 1)
        {
          if (to == number || !pb.has(to))
          {
            continue;
          }
          if (maxSpam >= 0 && spam_.has(to) && spam_.get(to) > maxSpam)
          {
            continue;
          }
          double newWeight = curWeight + edgeWeight;
          subgraph.addEdge(from, to, edgeWeight);

          if (candidates.has(to))
          {
            auto& pair = candidates.get(to);
            pair.first += newWeight;
            pair.second += 1;
          }
          else
          {
            candidates.add(to, std::make_pair(newWeight, 1));
          }
        }
        else
        {
          if (!pb.has(to) || to == number || visited.has(to))
          {
            continue;
          }
          if (maxSpam >= 0 && spam_.has(to) && spam_.get(to) > maxSpam)
          {
            continue;
          }
          subgraph.addEdge(from, to, edgeWeight);
          nextLevel.pushBack(std::make_pair(to, curWeight + edgeWeight));
        }
      }
    }
    current.swap(nextLevel);
  }

  Vector< std::pair< std::string, double > > result;
  for (auto it = candidates.cbegin(); it != candidates.cend(); ++it)
  {
    const std::string& candidate = (*it).first;
    double sum = (*it).second.first;
    size_t count = (*it).second.second;
    double avg = sum / count;
    result.pushBack(std::make_pair(candidate, avg));
  }

  return std::make_pair(std::move(subgraph), std::move(result));
}

const haliullin::AppCore::BookTable& haliullin::AppCore::getBooks() const
{
  return books_;
}

const haliullin::AppCore::SpamTable& haliullin::AppCore::getSpam() const
{
  return spam_;
}

const haliullin::SocialGraph& haliullin::AppCore::getGraph() const
{
  return graph_;
}
