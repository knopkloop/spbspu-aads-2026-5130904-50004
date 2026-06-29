#include <iostream>
#include <fstream>
#include "CommandDispatcher.hpp"

int main(int argc, char* argv[])
{
  if (argc > 2)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  using Disp = haliullin::CommandDispatcher;
  Disp dispatcher =
  {
    {"create-book", &Disp::cmdCreateBook},
    {"remove-book", &Disp::cmdRemoveBook},
    {"add-contact", &Disp::cmdAddContact},
    {"remove-contact", &Disp::cmdRemoveContact},
    {"rename-book", &Disp::cmdRenameBook},
    {"merge", &Disp::cmdMerge},
    {"copy-contact", &Disp::cmdCopyContact},
    {"show", &Disp::cmdShow},
    {"report", &Disp::cmdReportSpam},
    {"grade", &Disp::cmdGrade},
    {"show-connections", &Disp::cmdShowConnections},
    {"disconnect", &Disp::cmdDisconnect},
    {"recommend", &Disp::cmdRecommend},
    {"save", &Disp::cmdSave},
    {"load", &Disp::cmdLoad},
    {"exit", &Disp::cmdExit},
    {"help", &Disp::cmdHelp}
  };

  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
      std::cerr << "Cannot open file\n";
      return 1;
    }
    dispatcher.execute(file, std::cout);
  }
  else
  {
    dispatcher.execute(std::cin, std::cout);
  }
  return 0;
}
