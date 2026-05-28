#include "graph.hpp"

haliullin::Graph::Graph():
  vertexes_(),
  edges_()
{}

haliullin::Graph::Graph(const Graph& other):
  vertexes_(other.vertexes_),
  edges_(other.edges_)
{}

haliullin::Graph::Graph(Graph&& other) noexcept:
  Graph()
{
  swap(other);
}

haliullin::Graph& haliullin::Graph::operator=(const Graph& other)
{
  if (this != std::addressof(other))
  {
    Graph tmp(other);
    swap(tmp);
  }
  return *this;
}

haliullin::Graph& haliullin::Graph::operator=(Graph&& other) noexcept
{
  if (this != std::addressof(other))
  {
    Graph tmp(std::move(other));
    swap(tmp);
  }
  return *this;
}

void haliullin::Graph::swap(Graph& other) noexcept
{
  vertexes_.swap(other.vertexes_);
  edges_.swap(other.edges_);
}

void haliullin::Graph::addVertex(const std::string& vert)
{
  if (hasVertex(vert))
  {
    return;
  }
  vertexes_.pushBack(vert);
  vertexes_.insSort();
}

bool haliullin::Graph::hasVertex(const std::string& vert) const noexcept
{
  for (size_t i = 0; i < vertexes_.getSize(); ++i)
  {
    if (vertexes_[i] == vert)
    {
      return true;
    }
  }
  return false;
}

void haliullin::Graph::addEdge(const std::string& fromVert, const std::string& toVert, unsigned long long weight)
{
  addVertex(fromVert);
  addVertex(toVert);

  std::pair< std::string, std::string > key{fromVert, toVert};
  if (!edges_.has(key))
  {
    Vector< unsigned long long > w;
    w.pushBack(weight);
    edges_.add(key, w);
  }
  else
  {
    Vector< unsigned long long >& w = edges_.get(key);
    size_t pos = 0;
    while (pos < w.getSize() && w[pos] < weight)
    {
      ++pos;
    }
    w.insert(pos, weight);
  }
}

bool haliullin::Graph::cutEdge(const std::string& fromVert, const std::string& toVert, unsigned long long weight)
{
  std::pair< std::string, std::string > key{fromVert, toVert};
  if (!edges_.has(key))
    return false;

  Vector< unsigned long long >& w = edges_.get(key);
  for (size_t i = 0; i < w.getSize(); ++i)
  {
    if (w[i] == weight)
    {
      w.erase(i);
      if (w.isEmpty())
      {
        edges_.erase(key);
      }
      return true;
    }
  }
  return false;
}

haliullin::Vector< std::string > haliullin::Graph::getVertexes() const
{
  return vertexes_;
}

haliullin::Vector< std::pair< std::string, haliullin::Vector< unsigned long long > > >
haliullin::Graph::getOutbound(const std::string& fromVert) const
{
  HashTable< std::string, Vector< unsigned long long >, SipHash, Equal > temp;
  for (auto it = edges_.cbegin(); it != edges_.cend(); ++it)
  {
    const auto& key = (*it).first;
    if (key.first == fromVert)
    {
      const std::string& to = key.second;
      const Vector< unsigned long long >& weights = (*it).second;
      if (!temp.has(to))
      {
        temp.add(to, weights);
      }
      else
      {
        Vector< unsigned long long >& existing = temp.get(to);
        for (size_t i = 0; i < weights.getSize(); ++i)
        {
          unsigned long long w = weights[i];
          size_t pos = 0;
          while (pos < existing.getSize() && existing[pos] < w)
          {
            ++pos;
          }
          existing.insert(pos, w);
        }
      }
    }
  }

  Vector< std::pair< std::string, Vector< unsigned long long > > > result;
  for (auto it = temp.cbegin(); it != temp.cend(); ++it)
  {
    result.pushBack(std::make_pair((*it).first, (*it).second));
  }
  result.insSort();
  return result;
}

haliullin::Vector< std::pair< std::string, haliullin::Vector< unsigned long long > > >
haliullin::Graph::getInbound(const std::string& toVert) const
{
  HashTable< std::string, Vector< unsigned long long >, SipHash, Equal > temp;
  for (auto it = edges_.cbegin(); it != edges_.cend(); ++it)
  {
    const auto& key = (*it).first;
    if (key.second == toVert)
    {
      const std::string& from = key.first;
      const Vector< unsigned long long >& weights = (*it).second;
      if (!temp.has(from))
      {
        temp.add(from, weights);
      }
      else
      {
        Vector< unsigned long long >& existing = temp.get(from);
        for (size_t i = 0; i < weights.getSize(); ++i)
        {
          unsigned long long w = weights[i];
          size_t pos = 0;
          while (pos < existing.getSize() && existing[pos] < w)
          {
            ++pos;
          }
          existing.insert(pos, w);
        }
      }
    }
  }

  Vector< std::pair< std::string, Vector< unsigned long long > > > result;
  for (auto it = temp.cbegin(); it != temp.cend(); ++it)
  {
    result.pushBack(std::make_pair((*it).first, (*it).second));
  }
  result.insSort();
  return result;
}

haliullin::Graph haliullin::Graph::merge(const Graph& other) const
{
  Graph result;

  for (size_t i = 0; i < vertexes_.getSize(); ++i)
  {
    result.addVertex(vertexes_[i]);
  }
  for (auto it = edges_.cbegin(); it != edges_.cend(); ++it)
  {
    const auto& key = (*it).first;
    const auto& weights = (*it).second;
    for (size_t j = 0; j < weights.getSize(); ++j)
    {
      result.addEdge(key.first, key.second, weights[j]);
    }
  }

  for (size_t i = 0; i < other.vertexes_.getSize(); ++i)
  {
    result.addVertex(other.vertexes_[i]);
  }
  for (auto it = other.edges_.cbegin(); it != other.edges_.cend(); ++it)
  {
    const auto& key = (*it).first;
    const auto& weights = (*it).second;
    for (size_t j = 0; j < weights.getSize(); ++j)
    {
      result.addEdge(key.first, key.second, weights[j]);
    }
  }

  return result;
}

haliullin::Graph haliullin::Graph::extract(const Vector< std::string >& verts) const
{
  for (size_t i = 0; i < verts.getSize(); ++i)
  {
    if (!hasVertex(verts[i]))
    {
      throw std::invalid_argument("Vertex not found in original graph");
    }
  }

  Graph result;
  for (size_t i = 0; i < verts.getSize(); ++i)
  {
    result.addVertex(verts[i]);
  }

  HashTable< std::string, bool, SipHash, Equal > vset;
  for (size_t i = 0; i < verts.getSize(); ++i)
  {
    vset.add(verts[i], true);
  }

  for (auto it = edges_.cbegin(); it != edges_.cend(); ++it)
  {
    const auto& key = (*it).first;
    if (vset.has(key.first) && vset.has(key.second))
    {
      const auto& weights = (*it).second;
      for (size_t j = 0; j < weights.getSize(); ++j)
      {
        result.addEdge(key.first, key.second, weights[j]);
      }
    }
  }

  return result;
}
