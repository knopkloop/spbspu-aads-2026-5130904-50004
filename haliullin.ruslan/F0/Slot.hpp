#ifndef SLOT_HPP
#define SLOT_HPP

#include <utility>

namespace haliullin
{
  template< class Key, class Value, class Hash, class Equal >
  class RobinHashTable;

  template< class Key, class Value >
  class RHTableIterator;

  template< class Key, class Value >
  class RHTableConstIterator;
}

namespace haliullin::detail
{
  template< class Key, class Value >
  struct Slot
  {
    Slot() noexcept;
    Slot(const Key& k, const Value& v);
    Slot(Key&& k, Value&& v);

  private:
    std::pair< Key, Value > kv_;
    int psl_;
    void swap(Slot& other) noexcept;

    template< class K, class V, class H, class E >
    friend class RobinHashTable;

    template< class K, class V >
    friend class RHTableIterator;

    template< class K, class V >
    friend class RHTableConstIterator;
  };
}

template< class Key, class Value >
haliullin::detail::Slot< Key, Value >::Slot() noexcept:
  kv_(),
  psl_(-1)
{}

template< class Key, class Value >
haliullin::detail::Slot< Key, Value >::Slot(const Key& k, const Value& v):
  kv_(k, v),
  psl_(0)
{}

template< class Key, class Value >
haliullin::detail::Slot< Key, Value >::Slot(Key&& k, Value&& v):
  kv_(std::move(k), std::move(v)),
  psl_(0)
{}

template< class Key, class Value >
void haliullin::detail::Slot< Key, Value >::swap(Slot& other) noexcept
{
  std::swap(kv_, other.kv_);
  std::swap(psl_, other.psl_);
}

#endif
