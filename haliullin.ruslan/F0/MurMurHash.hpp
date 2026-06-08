#ifndef MURMURHASH_HPP
#define MURMURHASH_HPP

#include <cstddef>
#include <string>
#include <utility>

namespace haliullin::detail
{
  struct MurMurHash
  {
    size_t operator()(const std::string& key) const noexcept;
    size_t operator()(const std::pair< std::string, std::string >& key) const noexcept;
  };
}

inline size_t haliullin::detail::MurMurHash::operator()(const std::string& key) const noexcept
{
  const size_t seed = 0x9e3779b9;
  const size_t m = 0x5bd1e995;
  const int r = 24;
  size_t h = seed ^ key.size();
  const unsigned char* data = reinterpret_cast< const unsigned char* >(key.data());
  size_t len = key.size();

  while (len >= 4)
  {
    size_t k = *reinterpret_cast< const size_t* >(data);
    k *= m;
    k ^= k >> r;
    k *= m;
    h *= m;
    h ^= k;
    data += 4;
    len -= 4;
  }

  switch (len)
  {
    case 3:
    {
      h ^= static_cast< size_t >(data[2]) << 16;
      [[fallthrough]];
    }
    case 2:
    {
      h ^= static_cast< size_t >(data[1]) << 8;
      [[fallthrough]];
    }
    case 1:
    {
      h ^= data[0];
      h *= m;
    }
  }

  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;
  return h;
}

inline size_t haliullin::detail::MurMurHash::operator()(const std::pair< std::string, std::string >& key) const noexcept
{
  size_t h1 = (*this)(key.first);
  size_t h2 = (*this)(key.second);
  return h1 ^ (h2 << 1) ^ (h2 >> (sizeof(size_t) * 8 - 1));
}

#endif
