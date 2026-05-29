#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <fstream>
#include <string>
#include "BSTree.hpp"

namespace haliullin
{
  class Cmd
  {
  public:
    using SingleDataset = BSTree< int, std::string >;
    using DatasetStorage = BSTree< std::string, SingleDataset >;
    using func_t = void (Cmd::*)(std::istream&in, std::ostream& out);

    Cmd();

    void loadFromFile(const std::string& file);
    void processCmd(std::istream& in, std::ostream& out);

  private:
    DatasetStorage datasets_;
    BSTree< std::string, func_t > commands_;

    void require(bool condition) const;
    void require(std::istream& in) const;

    void cmdPrint(std::istream& in, std::ostream& out);
    void cmdComplement(std::istream& in, std::ostream&);
    void cmdIntersect(std::istream& in, std::ostream&);
    void cmdUnion(std::istream& in, std::ostream&);
  };
}

#endif
