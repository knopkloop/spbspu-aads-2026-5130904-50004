#ifndef SLOT_HPP
#define SLOT_HPP

#include <utility>

namespace haliullin::detail
{
  template< class Key, class Value >
  struct Slot
  {
    Slot() noexcept;

  private:
    std::pair< Key, Value > kv_;
    int psl_;

    void swap(Slot& other) noexcept;
    template< class K, class V, class H, class E >
    friend class RobinHoodHashTable;
  };
}

template< class Key, class Value >
haliullin::detail::Slot< Key, Value >::Slot() noexcept:
  kv_(),
  psl_(-1)
{}

template< class Key, class Value >
void haliullin::detail::Slot< Key, Value >::swap(Slot& other) noexcept
{
  std::swap(kv_, other.kv_);
  std::swap(psl_, other.psl_);
}

#endif
