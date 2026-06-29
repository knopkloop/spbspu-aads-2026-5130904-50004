#ifndef MURMURHASH_HPP
#define MURMURHASH_HPP

#include <cstddef>
#include <string>
#include <utility>

namespace haliullin
{
  struct MurMurHash
  {
    size_t operator()(const void* data, size_t len) const noexcept;
    size_t operator()(const std::string& key) const noexcept;
    size_t operator()(const std::pair< std::string, std::string >& key) const noexcept;
  };
}

#endif
