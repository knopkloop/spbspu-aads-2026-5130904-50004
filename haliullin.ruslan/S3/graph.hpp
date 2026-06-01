#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "HashTable.hpp"
#include "vector.hpp"
#include "SipHash.hpp"
#include <utility>
#include <string>

namespace haliullin
{
  class Graph
  {
  public:
    using EdgeVec = Vector< std::pair< std::string, Vector< unsigned long long > > >;

    ~Graph() = default;
    Graph() = default;
    Graph(const Graph&) = default;
    Graph(Graph&&) noexcept = default;

    Graph& operator=(const Graph& other);
    Graph& operator=(Graph&& other) noexcept;
    void swap(Graph& other) noexcept;

    void addVertex(const std::string& vert);
    bool hasVertex(const std::string& vert) const;
    void addEdge(const std::string& fromVert, const std::string& toVert, unsigned long long weight);
    void cutEdge(const std::string& fromVert, const std::string& toVert, unsigned long long weight);

    Vector< std::string > getVertexes() const;
    EdgeVec getOutbound(const std::string& fromVert) const;
    EdgeVec getInbound(const std::string& toVert) const;

    Graph merge(const Graph& other) const;
    Graph extract(const Vector< std::string >& vertices) const;

  private:
    Vector< std::string > vertexes_;
    HashTable< std::pair< std::string, std::string >, Vector< unsigned long long >, detail::SipHash,
               std::equal_to< std::pair< std::string, std::string > > > edges_;
  };
}

#endif
