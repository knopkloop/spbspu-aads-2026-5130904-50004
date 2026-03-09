#include <iostream>
#include <string>
#include <utility>
#include "BiList.hpp"

using namespace haliullin;

int main()
{
   try
  {
    BiList<std::pair<std::string, BiList<unsigned long long>>> stor;
    std::string token;
    unsigned long long value = 0;

    while (std::cin >> token)
    {
      BiList<unsigned long long> numbers;

      while (std::cin >> value)
      {
        numbers.push_back(value);
      }

      stor.push_back(std::make_pair(token, std::move(numbers)));

      if (!std::cin.eof())
      {
        std::cin.clear();
      }
    }
  }
  catch(const std::exception &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
