#include <iostream>
#include <string>
#include <utility>
#include "BiList.hpp"

using namespace haliullin;

int main()
{
   try
  {
    BiList<std::pair<std::string, BiList<unsigned long long>>> seq;
    std::string token;
    unsigned long long value = 0;

    while (std::cin >> token)
    {
      BiList<unsigned long long> numbers;

      while (std::cin >> value)
      {
        numbers.push_back(value);
      }

      seq.push_back(std::make_pair(token, std::move(numbers)));

      if (!std::cin.eof())
      {
        std::cin.clear();
      }
    }

    if (seq.is_empty())
    {
      std::cout << "0\n";
      return 0;
    }

    auto nameIter = seq.cbegin();
    std::cout << " " << nameIter->first;
    ++nameIter;

    while (nameIter != seq.cend())
    {
      std::cout << " " << nameIter->first;
      ++nameIter;
    }
    std::cout << "\n";

    BiList<std::pair<LIter<unsigned long long>, LIter<unsigned long long>>> posTrackers;

    for (auto elIter = seq.begin(); elIter != seq.end(); ++elIter)
    {
      if (!elIter->second.is_empty())
      {
        posTrackers.push_back(std::make_pair(elIter->second.begin(), elIter->second.end()));
      }
    }

    if (posTrackers.is_empty())
    {
      std::cout << "\n0\n";
      return 0;
    }
  }
  catch(const std::exception &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
