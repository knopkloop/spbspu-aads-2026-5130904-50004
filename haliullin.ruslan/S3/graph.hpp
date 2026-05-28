#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "HashTable.hpp"
#include "vector.hpp"
#include "SipHash.hpp"
#include "Equal.hpp"
#include <utility>
#include <string>

namespace haliullin
{
  class Graph
  {
  public:
    ~Graph() = default;
    Graph();

    Graph(const Graph& other);
    Graph(Graph&& other) noexcept;

    Graph& operator=(const Graph& other);
    Graph& operator=(Graph&& other) noexcept;

    void swap(Graph& other) noexcept;

    void addVertex(const std::string& vert);
    bool hasVertex(const std::string& vert) const noexcept;

    void addEdge(const std::string& fromVert, const std::string& toVert, unsigned long long weight);
    bool cutEdge(const std::string& fromVert, const std::string& toVert, unsigned long long weight);

    Vector< std::string > getVertexes() const;

    Vector< std::pair< std::string, Vector< unsigned long long > > >
    getOutbound(const std::string& fromVert) const;

    Vector< std::pair< std::string, Vector< unsigned long long > > >
    getInbound(const std::string& toVert) const;

    Graph merge(const Graph& other) const;
    Graph extract(const Vector< std::string >& vertices) const;

  private:
    Vector< std::string > vertexes_;
    HashTable< std::pair< std::string, std::string >, Vector< unsigned long long >, SipHash, Equal > edges_;
  };
}

#endif
