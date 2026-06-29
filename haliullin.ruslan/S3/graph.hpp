#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <utility>
#include <string>
#include <Vector.hpp>
#include "HashTable.hpp"
#include "SipHash.hpp"

namespace haliullin
{
  class Graph
  {
  public:
    using EdgeVec = Vector< std::pair< std::string, Vector< unsigned long long > > >;
    using pair_str = std::pair< std::string, std::string >;

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
    HashTable< pair_str, Vector< unsigned long long >, SipHash, std::equal_to< pair_str > > edges_;
  };
}

#endif
