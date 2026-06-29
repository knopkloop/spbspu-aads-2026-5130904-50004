#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>
#include <functional>
#include "HashTable.hpp"
#include "graph.hpp"
#include "SipHash.hpp"

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
    HashTable< std::string, Graph, SipHash, std::equal_to< std::string > > graphs_;
    HashTable< std::string, func_t, SipHash, std::equal_to< std::string > > commands_;

    void require(bool condition) const;
    void require(std::istream& in) const;

    void cmdGraphs(std::istream& in, std::ostream& out);
    void cmdVertexes(std::istream& in, std::ostream& out);
    void cmdOutbound(std::istream& in, std::ostream& out);
    void cmdInbound(std::istream& in, std::ostream& out);
    void cmdBind(std::istream& in, std::ostream&);
    void cmdCut(std::istream& in, std::ostream&);
    void cmdCreate(std::istream& in, std::ostream&);
    void cmdMerge(std::istream& in, std::ostream&);
    void cmdExtract(std::istream& in, std::ostream&);
  };
}

#endif
