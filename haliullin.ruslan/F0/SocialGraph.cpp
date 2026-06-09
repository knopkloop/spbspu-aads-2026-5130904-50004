#include "SocialGraph.hpp"
#include <memory>
#include <utility>
#include <string>

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
