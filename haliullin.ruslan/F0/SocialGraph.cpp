#include "SocialGraph.hpp"
#include <memory>
#include <utility>
#include <string>
#include <stdexcept>

haliullin::SocialGraph& haliullin::SocialGraph::operator=(const SocialGraph& other)
{
  if (this != std::addressof(other))
  {
    SocialGraph tmp(other);
    swap(tmp);
  }
  return *this;
}

haliullin::SocialGraph& haliullin::SocialGraph::operator=(SocialGraph&& other) noexcept
{
  if (this != std::addressof(other))
  {
    SocialGraph tmp(std::move(other));
    swap(tmp);
  }
  return *this;
}

void haliullin::SocialGraph::swap(SocialGraph& other) noexcept
{
  edges_.swap(other.edges_);
}

void haliullin::SocialGraph::addEdge(const std::string& from, const std::string& to, double weight)
{
  SocialGraph tmp(*this);
  EdgeKey key(from, to);
  if (tmp.edges_.has(key))
  {
    Vector< double >& ratings = tmp.edges_.get(key);
    ratings.pushBack(weight);
  }
  else
  {
    Vector< double > newRatings;
    newRatings.pushBack(weight);
    tmp.edges_.add(key, newRatings);
  }
  swap(tmp);
}

void haliullin::SocialGraph::removeEdges(const std::string& from, const std::string& to)
{
  SocialGraph tmp(*this);
  EdgeKey key(from, to);
  if (!tmp.edges_.has(key))
  {
    throw std::out_of_range("Edges not found");
  }
  tmp.edges_.erase(key);
  swap(tmp);
}

bool haliullin::SocialGraph::hasEdges(const std::string& from, const std::string& to) const
{
  EdgeKey key(from, to);
  return edges_.has(key);
}

double haliullin::SocialGraph::getAverageWeight(const std::string& from, const std::string& to) const
{
  EdgeKey key(from, to);
  if (!edges_.has(key))
  {
    throw std::out_of_range("Edges not found");
  }

  const Vector< double >& ratings = edges_.get(key);
  double sum = 0.0;
  for (size_t i = 0; i < ratings.getSize(); ++i)
  {
    sum += ratings[i];
  }
  return sum / ratings.getSize();
}

haliullin::SocialGraph::EdgeVector haliullin::SocialGraph::getAllEdges() const
{
  EdgeVector result;
  for (auto it = edges_.cbegin(); it != edges_.cend(); ++it)
  {
    result.pushBack(*it);
  }
  return result;
}

haliullin::Vector< std::string > haliullin::SocialGraph::getVertexes() const
{
  Vector< std::string > allNames;
  for (auto it = edges_.cbegin(); it != edges_.cend(); ++it)
  {
    allNames.pushBack((*it).first.first);
    allNames.pushBack((*it).first.second);
  }

  if (allNames.isEmpty())
  {
    return allNames;
  }
  allNames.insSort();

  Vector< std::string > unique;
  unique.pushBack(allNames[0]);
  for (size_t i = 1; i < allNames.getSize(); ++i)
  {
    if (allNames[i] != allNames[i - 1])
    {
      unique.pushBack(allNames[i]);
    }
  }
  return unique;
}
