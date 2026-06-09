#ifndef ROBINHASH_ITERATORS_HPP
#define ROBINHASH_ITERATORS_HPP

#include <utility>
#include <memory>
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
    using slot_t = detail::Slot< Key, Value >;
    using cpair_t = const std::pair< Key, Value >;

    RHTableConstIterator() noexcept;

    cpair_t& operator*() const noexcept;
    cpair_t* operator->() const noexcept;

    RHTableConstIterator& operator++() noexcept;
    RHTableConstIterator operator++(int) noexcept;

    bool operator==(const RHTableConstIterator& other) const noexcept;
    bool operator!=(const RHTableConstIterator& other) const noexcept;

  private:
    VCIter< slot_t > cur_;
    VCIter< slot_t > end_;

    RHTableConstIterator(VCIter< slot_t > cur, VCIter< slot_t > end) noexcept;
    explicit RHTableConstIterator(const RHTableIterator< Key, Value >& it) noexcept;

    template< class K, class V, class H, class E >
    friend class RobinHashTable;
  };
}

template< class Key, class Value >
haliullin::RHTableIterator< Key, Value >::RHTableIterator() noexcept:
  cur_(),
  end_()
{}

template< class Key, class Value >
haliullin::RHTableIterator< Key, Value >::RHTableIterator(VIter< slot_t > cur, VIter< slot_t > end) noexcept:
  cur_(cur),
  end_(end)
{}

template< class Key, class Value >
std::pair< Key, Value >& haliullin::RHTableIterator< Key, Value >::operator*() const noexcept
{
  return cur_->kv_;
}

template< class Key, class Value >
std::pair< Key, Value >* haliullin::RHTableIterator< Key, Value >::operator->() const noexcept
{
  return std::addressof(cur_->kv_);
}

template< class Key, class Value >
haliullin::RHTableIterator< Key, Value >& haliullin::RHTableIterator< Key, Value >::operator++() noexcept
{
  ++cur_;
  while ((cur_ != end_) && (cur_->psl_ == -1))
  {
    ++cur_;
  }
  return *this;
}

template< class Key, class Value >
haliullin::RHTableIterator< Key, Value > haliullin::RHTableIterator< Key, Value >::operator++(int) noexcept
{
  RHTableIterator tmp = *this;
  ++(*this);
  return tmp;
}

template< class Key, class Value >
bool haliullin::RHTableIterator< Key, Value >::operator==(const RHTableIterator& other) const noexcept
{
  return cur_ == other.cur_;
}

template< class Key, class Value >
bool haliullin::RHTableIterator< Key, Value >::operator!=(const RHTableIterator& other) const noexcept
{
  return !(*this == other);
}

template< class Key, class Value >
haliullin::RHTableConstIterator< Key, Value >::RHTableConstIterator() noexcept:
  cur_(),
  end_()
{}

template< class Key, class Value >
haliullin::RHTableConstIterator< Key, Value >::RHTableConstIterator(VCIter< slot_t > cur, VCIter< slot_t > end) noexcept:
  cur_(cur),
  end_(end)
{}

template< class Key, class Value >
haliullin::RHTableConstIterator< Key, Value >::RHTableConstIterator(const RHTableIterator< Key, Value >& it) noexcept:
  cur_(it.cur_),
  end_(it.end_)
{}

template< class Key, class Value >
const std::pair< Key, Value >& haliullin::RHTableConstIterator< Key, Value >::operator*() const noexcept
{
  return cur_->kv_;
}

template< class Key, class Value >
const std::pair< Key, Value >* haliullin::RHTableConstIterator< Key, Value >::operator->() const noexcept
{
  return std::addressof(cur_->kv_);
}

template< class Key, class Value >
haliullin::RHTableConstIterator< Key, Value >& haliullin::RHTableConstIterator< Key, Value >::operator++() noexcept
{
  ++cur_;
  while ((cur_ != end_) && (cur_->psl_ == -1))
  {
    ++cur_;
  }
  return *this;
}

template< class Key, class Value >
haliullin::RHTableConstIterator< Key, Value > haliullin::RHTableConstIterator< Key, Value >::operator++(int) noexcept
{
  RHTableConstIterator tmp = *this;
  ++(*this);
  return tmp;
}

template< class Key, class Value >
bool haliullin::RHTableConstIterator< Key, Value >::operator==(const RHTableConstIterator& other) const noexcept
{
  return cur_ == other.cur_;
}

template< class Key, class Value >
bool haliullin::RHTableConstIterator< Key, Value >::operator!=(const RHTableConstIterator& other) const noexcept
{
  return !(*this == other);
}

#endif
