#include "MurMurHash.hpp"
#include <boost/functional/hash.hpp>
#include <cstdint>
#include <cstring>
#include <memory>

size_t haliullin::MurMurHash::operator()(const void* data, size_t len) const noexcept
{
  const uint64_t m = 0xc6a4a7935bd1e995ULL;
  const int r = 47;
  const uint64_t seed = 0x9e3779b97f4a7c15ULL;
  uint64_t h = seed ^ (len * m);
  const unsigned char* bytes = reinterpret_cast< const unsigned char* >(data);

  while (len >= 8)
  {
    uint64_t k = 0;
    std::memcpy(std::addressof(k), bytes, 8);
    k *= m;
    k ^= k >> r;
    k *= m;
    h ^= k;
    h *= m;
    bytes += 8;
    len -= 8;
  }

  switch (len)
  {
    case 7:
    {
      h^= static_cast< uint64_t >(bytes[6]) << 48;
      [[fallthrough]];
    }
    case 6:
    {
      h ^= static_cast< uint64_t >(bytes[5]) << 40;
      [[fallthrough]];
    }
    case 5:
    {
      h ^= static_cast< uint64_t >(bytes[4]) << 32;
      [[fallthrough]];
    }
    case 4:
    {
      h ^= static_cast< uint64_t >(bytes[3]) << 24;
      [[fallthrough]];
    }
    case 3:
    {
      h ^= static_cast< uint64_t >(bytes[2]) << 16;
      [[fallthrough]];
    }
    case 2:
    {
      h ^= static_cast< uint64_t >(bytes[1]) << 8;
      [[fallthrough]];
    }
    case 1:
    {
      h ^= static_cast< uint64_t >(bytes[0]);
      h *= m;
    }
  }

  h ^= h >> r;
  h *= m;
  h ^= h >> r;
  return static_cast< size_t >(h);
}

size_t haliullin::MurMurHash::operator()(const std::string& key) const noexcept
{
  return (*this)(key.data(), key.size());
}

size_t haliullin::MurMurHash::operator()(const std::pair< std::string, std::string >& key) const noexcept
{
  size_t seed = 0;
  size_t h1 = (*this)(key.first);
  size_t h2 = (*this)(key.second);
  boost::hash_combine(seed, h1);
  boost::hash_combine(seed, h2);
  return seed;
}
