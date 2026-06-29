#ifndef SIPHASH_HPP
#define SIPHASH_HPP

#include <boost/hash2/siphash.hpp>
#include <boost/hash2/hash_append.hpp>

namespace haliullin
{
  struct SipHash
  {
    template< class T >
    std::size_t operator()(const T& key) const noexcept
    {
      boost::hash2::siphash_64 hasher;
      boost::hash2::hash_append(hasher, {}, key);
      return hasher.result();
    }
  };
}

#endif
