#include <iostream>
#include "commands.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Invalid number of arguments\n";
    return 1;
  }

  haliullin::Cmd process;
  try
  {
    process.loadFromFile(argv[1]);
    process.processCmd(std::cin, std::cout);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}
