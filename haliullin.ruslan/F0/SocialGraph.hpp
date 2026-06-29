#ifndef SOCIALGRAPH_HPP
#define SOCIALGRAPH_HPP

#include <utility>
#include <string>
#include <ostream>
#include <Vector.hpp>
#include "RobinHashTable.hpp"
#include "MurMurHash.hpp"

namespace haliullin
{
  class SocialGraph
  {
  public:
    using EdgeKey = std::pair< std::string, std::string >;
    using EdgeTable = RobinHashTable< EdgeKey, Vector< double >, MurMurHash, std::equal_to< EdgeKey > >;
    using EdgeVector = Vector< std::pair< EdgeKey, Vector< double > > >;
    using RatingVector = Vector< std::pair< std::string, double > >;

    SocialGraph();
    ~SocialGraph() = default;
    SocialGraph(const SocialGraph&) = default;
    SocialGraph(SocialGraph&&) noexcept = default;

    SocialGraph& operator=(const SocialGraph& other);
    SocialGraph& operator=(SocialGraph&& other) noexcept;
    void swap(SocialGraph& other) noexcept;

    void addEdge(const std::string& from, const std::string& to, double weight);
    void removeEdges(const std::string& from, const std::string& to);
    bool hasEdges(const std::string& from, const std::string& to) const;
    double getAverageWeight(const std::string& from, const std::string& to) const;
    EdgeVector getAllEdges() const;

    Vector< std::string > getVertexes() const;
    RatingVector getOutbound(const std::string& vert) const;
    RatingVector getInbound(const std::string& vert) const;

  private:
    EdgeTable edges_;
  };

  std::ostream& operator<<(std::ostream& os, const SocialGraph& graph);
}

#endif
