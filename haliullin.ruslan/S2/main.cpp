#include "stack.hpp"
#include "evaluate.hpp"

#include <iostream>
#include <fstream>
#include <string>

using namespace haliullin;
int main(int argc, char * argv[])
{
  std::istream * input = &std::cin;
  std::ifstream file;

  if (argc == 2)
  {
    file.open(argv[1]);
    if (!file.is_open())
    {
      std::cerr << "Cannot open file" << "\n";
      return 1;
    }
    input = &file;
  }
  else if (argc > 2)
  {
    std::cerr << "Too many arguments" << "\n";
    return 1;
  }

  haliullin::Stack< long long > res;
  std::string line = "";

  try
  {
    while (std::getline(*input, line))
    {
      if (!line.empty())
      {
        res.push(evaluate(infixToPostfix(line)));
      }

    }
  }
  catch(const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  if (!res.is_empty())
  {
    std::cout << res.top();
    res.drop();
    while(!res.is_empty())
    {
      std::cout << " " << res.top();
      res.drop();
    }
  }
  std::cout << "\n";
  return 0;
}
