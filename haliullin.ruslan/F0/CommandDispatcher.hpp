#ifndef COMMANDDISPATCHER_HPP
#define COMMANDDISPATCHER_HPP

#include <iosfwd>
#include <string>
#include "RobinHashTable.hpp"
#include "MurMurHash.hpp"
#include "AppCore.hpp"

namespace haliullin
{
  class CommandDispatcher
  {
  public:
    using func_t = void (CommandDispatcher::*)(std::istream&, std::ostream&);
    using cmd_pair_t = std::pair< std::string, func_t >;

    CommandDispatcher(std::initializer_list< cmd_pair_t > cmds);
    void execute(std::istream& in, std::ostream& out);

    void cmdCreateBook(std::istream& in, std::ostream& out);
    void cmdRemoveBook(std::istream& in, std::ostream& out);
    void cmdAddContact(std::istream& in, std::ostream& out);
    void cmdRemoveContact(std::istream& in, std::ostream& out);
    void cmdRenameBook(std::istream& in, std::ostream& out);
    void cmdMerge(std::istream& in, std::ostream& out);
    void cmdCopyContact(std::istream& in, std::ostream& out);
    void cmdShow(std::istream& in, std::ostream& out);
    void cmdReportSpam(std::istream& in, std::ostream& out);
    void cmdGrade(std::istream& in, std::ostream& out);
    void cmdShowConnections(std::istream& in, std::ostream& out);
    void cmdDisconnect(std::istream& in, std::ostream& out);
    void cmdRecommend(std::istream& in, std::ostream& out);
    void cmdSave(std::istream& in, std::ostream& out);
    void cmdLoad(std::istream& in, std::ostream& out);
    void cmdExit(std::istream& in, std::ostream& out);
    void cmdHelp(std::istream&, std::ostream& out);

  private:
    AppCore core_;
    RobinHashTable< std::string, func_t, MurMurHash, std::equal_to< std::string > > commands_;

    void require(bool condition) const;
    void require(std::istream& in) const;
    bool isNumberValid(const std::string& number) const;
  };
}

#endif
