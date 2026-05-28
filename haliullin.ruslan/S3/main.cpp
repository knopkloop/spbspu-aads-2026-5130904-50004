#include <iostream>
#include <fstream>
#include <limits>
#include "commands.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Invalid number of arguments";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Cannot open file\n";
    return 1;
  }

  haliullin::Cmd cmd;
  try
  {
    cmd.loadGraphs(file);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  file.close();

  std::string command;
  while (std::cin >> command)
  {
    haliullin::Cmd::func_t func;
    if (!cmd.getCommand(command, func))
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      continue;
    }
    (cmd.*func)(std::cin, std::cout);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  if (!std::cin.eof())
  {
    std::cerr << "Bad input\n";
    return 1;
  }
  return 0;
}
