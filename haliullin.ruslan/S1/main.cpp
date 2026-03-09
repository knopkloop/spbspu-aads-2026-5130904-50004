#include "BiList.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <limits>

using namespace haliullin;

int main()
{
  try
  {
    BiList<std::pair<std::string, BiList<unsigned long long>>> sequences;
    std::string name;

    while (std::cin >> name)
    {
      BiList<unsigned long long> numbers;
      unsigned long long num;
      char peek;
      while (true)
      {
        peek = std::cin.peek();
        if (peek == '\n' || peek == EOF || peek == '\r')
        {
          break;
        }
        if (std::cin >> num)
        {
          numbers.push_back(num);
        }
        else
        {
          break;
        }
      }
      sequences.push_back(std::make_pair(name, std::move(numbers)));
    }

    if (sequences.is_empty())
    {
      std::cout << "0\n";
      return 0;
    }

    bool first = true;
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      if (!first)
      {
        std::cout << ' ';
      }
      std::cout << it->first;
      first = false;
    }
    std::cout << "\n";

    size_t maxLen = 0;
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      if (it->second.getsize() > maxLen)
      {
        maxLen = it->second.getsize();
      }
    }

    BiList<BiList<unsigned long long>> transposed;
    for (size_t i = 0; i < maxLen; ++i)
    {
      BiList<unsigned long long> newList;
      for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
      {
        if (i < it->second.getsize())
        {
          auto elemIt = it->second.cbegin();
          for (size_t j = 0; j < i; ++j)
          {
            ++elemIt;
          }
          newList.push_back(*elemIt);
        }
      }
      transposed.push_back(std::move(newList));
    }

    for (auto it = transposed.cbegin(); it != transposed.cend(); ++it)
    {
      if (it->is_empty())
      {
        continue;
      }

      bool firstInRow = true;
      for (auto elemIt = it->cbegin(); elemIt != it->cend(); ++elemIt)
      {
        if (!firstInRow)
        {
          std::cout << ' ';
        }
        std::cout << *elemIt;
        firstInRow = false;
      }
      std::cout << "\n";
    }

    BiList<unsigned long long> sums;
    for (auto it = transposed.cbegin(); it != transposed.cend(); ++it)
    {
      unsigned long long total = 0;
      for (auto elemIt = it->cbegin(); elemIt != it->cend(); ++elemIt)
      {
        if (total > std::numeric_limits<unsigned long long>::max() - *elemIt)
        {
          throw std::overflow_error("Sum calculation overflow");
        }
        total += *elemIt;
      }
      sums.push_back(total);
    }

    first = true;
    for (auto it = sums.cbegin(); it != sums.cend(); ++it)
    {
      if (!first)
      {
        std::cout << ' ';
      }
      std::cout << *it;
      first = false;
    }
    std::cout << "\n";

    return 0;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}
