#ifndef SLOT_HPP
#define SLOT_HPP

#include <utility>

namespace haliullin::detail
{
  template< class Key, class Value >
  struct Slot
  {
    Slot() noexcept:
      kv_(),
      psl_(-1)
    {}

  private:
    std::pair< Key, Value > kv_;
    int psl_;

    template< class K, class V, class H, class E >
    friend class RobinHoodHashTable;
  };
}

#endif
