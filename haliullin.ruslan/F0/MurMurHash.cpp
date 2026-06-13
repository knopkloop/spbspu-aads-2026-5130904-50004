#include "MurMurHash.hpp"
#include <memory>
#include <cstdint>
#include <cstring>

size_t haliullin::detail::MurMurHash::operator()(const std::string& key) const noexcept
{
  const uint64_t m = 0xc6a4a7935bd1e995ULL;
  const int r = 47;
  const uint64_t seed = 0x9e3779b97f4a7c15ULL;
  uint64_t h = seed ^ (key.size() * m);
  const unsigned char* data = reinterpret_cast< const unsigned char* >(key.data());
  size_t len = key.size();

  while (len >= 8)
  {
    uint64_t k = 0;
    std::memcpy(std::addressof(k), data, 8);
    k *= m;
    k ^= k >> r;
    k *= m;
    h ^= k;
    h *= m;
    data += 8;
    len -= 8;
  }

  switch (len)
  {
    case 7:
    {
      h^= static_cast< uint64_t >(data[6]) << 48;
      [[fallthrough]];
    }
    case 6:
    {
      h^= static_cast< uint64_t >(data[5]) << 40;
      [[fallthrough]];
    }
    case 5:
    {
      h^= static_cast< uint64_t >(data[4]) << 32;
      [[fallthrough]];
    }
    case 4:
    {
      h^= static_cast< uint64_t >(data[3]) << 24;
      [[fallthrough]];
    }
    case 3:
    {
      h^= static_cast< uint64_t >(data[2]) << 16;
      [[fallthrough]];
    }
    case 2:
    {
      h^= static_cast< uint64_t >(data[1]) << 8;
      [[fallthrough]];
    }
    case 1:
    {
      h^= static_cast< uint64_t >(data[0]);
      h *= m;
    }
  }

  h ^= h >> r;
  h *= m;
  h ^= h >> r;
  return static_cast< size_t >(h);
}

size_t haliullin::detail::MurMurHash::operator()(const std::pair< std::string, std::string >& key) const noexcept
{
  size_t h1 = (*this)(key.first);
  size_t h2 = (*this)(key.second);
  return h1 ^ ((h2 << 1) | (h2 >> (sizeof(size_t) * 8 - 1)));
}
