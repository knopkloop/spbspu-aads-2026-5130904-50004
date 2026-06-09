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
    throw std::out_of_range("Edge not found");
  }
  tmp.edges_.erase(key);
  swap(tmp);
}

