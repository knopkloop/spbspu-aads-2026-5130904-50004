#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>
#include "HashTable.hpp"
#include "graph.hpp"
#include "SipHash.hpp"
#include "Equal.hpp"

namespace haliullin
{
  class Cmd
  {
  public:
    using func_t = void (Cmd::*)(std::istream& in, std::ostream& out);

    Cmd();

    void loadGraphs(std::istream& file);
    bool getCommand(const std::string& name, func_t& out) const;

  private:
    HashTable< std::string, Graph, SipHash, Equal > graphs_;
    HashTable< std::string, func_t, SipHash, Equal > commands_;

    void require(bool condition) const;
    void require(std::istream& in) const;

    void cmdGraphs(std::istream& in, std::ostream& out);
    void cmdVertexes(std::istream& in, std::ostream& out);
    void cmdOutbound(std::istream& in, std::ostream& out);
    void cmdInbound(std::istream& in, std::ostream& out);
    void cmdBind(std::istream& in, std::ostream& out);
    void cmdCut(std::istream& in, std::ostream& out);
    void cmdCreate(std::istream& in, std::ostream& out);
    void cmdMerge(std::istream& in, std::ostream& out);
    void cmdExtract(std::istream& in, std::ostream& out);
  };
}

#endif
