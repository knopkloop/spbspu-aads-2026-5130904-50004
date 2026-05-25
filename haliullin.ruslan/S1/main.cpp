#include <iostream>
#include <string>
#include <utility>
#include <limits>
#include <BiList.hpp>

int main()
{
  try
  {
    haliullin::BiList< std::pair< std::string, haliullin::BiList< unsigned long long > > > sequences;
    haliullin::BiList< unsigned long long > numbers;
    std::string name;
    unsigned long long num;

    while (std::cin >> name)
    {
      while (std::cin >> num)
      {
        numbers.emplace_back(num);
      }
      std::cin.clear();
      sequences.emplace_back(std::make_pair(name, std::move(numbers)));
    }

    if (sequences.is_empty())
    {
      std::cout << "0" << "\n";
      return 0;
    }

    auto nameIt = sequences.cbegin();
    std::cout << nameIt->first;
    ++nameIt;
    for (; nameIt != sequences.cend(); ++nameIt)
    {
      std::cout << " " << nameIt->first;
    }
    std::cout << "\n";

    size_t maxLen = 0;
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      if (it->second.get_size() > maxLen)
      {
        maxLen = it->second.get_size();
      }
    }

    haliullin::BiList< haliullin::BiList< unsigned long long > > transp;
    for (size_t i = 0; i < maxLen; ++i)
    {
      haliullin::BiList< unsigned long long > newList;
      for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
      {
        if (i < it->second.get_size())
        {
          auto elemIt = it->second.cbegin();
          for (size_t j = 0; j < i; ++j)
          {
            ++elemIt;
          }
          newList.emplace_back(*elemIt);
        }
      }
      if (!newList.is_empty())
      {
        transp.emplace_back(std::move(newList));
      }
    }

    for (auto it = transp.cbegin(); it != transp.cend(); ++it)
    {
      auto elemIt = it->cbegin();
      std::cout << *elemIt;
      ++elemIt;
      for (; elemIt != it->cend(); ++elemIt)
      {
        std::cout << " " << *elemIt;
      }
      std::cout << "\n";
    }

    haliullin::BiList< unsigned long long > sums;
    for (auto it = transp.cbegin(); it != transp.cend(); ++it)
    {
      unsigned long long total = 0;
      for (auto elemIt = it->cbegin(); elemIt != it->cend(); ++elemIt)
      {
        if (total > std::numeric_limits< unsigned long long >::max() - *elemIt)
        {
          throw std::overflow_error("Sum calculation overflow");
        }
        total += *elemIt;
      }
      sums.emplace_back(total);
    }

    if (sums.is_empty())
    {
      std::cout << "0" << "\n";
    }
    else
    {
      auto sumIt = sums.cbegin();
      std::cout << *sumIt;
      ++sumIt;
      for (; sumIt != sums.cend(); ++sumIt)
      {
        std::cout << " " << *sumIt;
      }
      std::cout << "\n";
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}
