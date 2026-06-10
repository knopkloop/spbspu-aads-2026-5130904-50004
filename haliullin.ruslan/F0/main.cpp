#include <iostream>
#include "CommandDispatcher.hpp"

int main()
{
  haliullin::CommandDispatcher dispatcher;
  dispatcher.execute(std::cin, std::cout);
  return 0;
}
