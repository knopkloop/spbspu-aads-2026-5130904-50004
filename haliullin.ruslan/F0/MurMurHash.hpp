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

#endif
