#ifndef ROBINHASH_ITERATORS_HPP
#define ROBINHASH_ITERATORS_HPP

#include <utility>
#include "Vector-iterators.hpp"
#include "Slot.hpp"

namespace haliullin
{
  template< class Key, class Value >
  class RHTableConstIterator;

  template< class Key, class Value >
  class RHTableIterator
  {
  public:
    using slot_t = detail::Slot< Key, Value >;
    using pair_t = std::pair< Key, Value >;

    RHTableIterator() noexcept;

    pair_t& operator*() const noexcept;
    pair_t* operator->() const noexcept;

    RHTableIterator& operator++() noexcept;
    RHTableIterator operator++(int) noexcept;

    bool operator==(const RHTableIterator& other) const noexcept;
    bool operator!=(const RHTableIterator& other) const noexcept;

  private:
    VIter< slot_t > cur_;
    VIter< slot_t > end_;

    RHTableIterator(VIter< slot_t > cur, VIter< slot_t > end) noexcept;

    template< class K, class V, class H, class E >
    friend class RobinHashTable;
    friend class RHTableConstIterator< Key, Value >;
  };

  template< class Key, class Value >
  class RHTableConstIterator
  {
  public:
    using slot_t = detail::Slot<Key, Value>;
    using cpair_t = const std::pair<Key, Value>;

    RHTableConstIterator() noexcept;

    cpair_t& operator*() const noexcept;
    cpair_t* operator->() const noexcept;

    RHTableConstIterator& operator++() noexcept;
    RHTableConstIterator operator++(int) noexcept;

    bool operator==(const RHTableConstIterator& other) const noexcept;
    bool operator!=(const RHTableConstIterastor& other) const noexcept;

  private:
    VCIter< slot_t > cur_;
    VCIter< slot_t > end_;

    RHTableConstIterator(VCIter<slot_t> cur, VCIter< slot_t > end) noexcept;
    explicit RHTableConstIterator(const RHTableIterator< Key, Value >& it) noexcept;

    template< class K, class V, class H, class E >
    friend class RobinHashTable;
  };
}

#endif
