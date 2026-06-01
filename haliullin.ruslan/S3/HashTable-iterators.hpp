#ifndef HASHTABLE_ITERATORS_HPP
#define HASHTABLE_ITERATORS_HPP

#include <cstddef>
#include <utility>
#include <iterator>
#include "vector.hpp"
#include "slot.hpp"

namespace haliullin
{
  template< class Key, class Value, class Hash, class Equal >
  class HashTable;

  template< class Key, class Value, class Hash, class Equal >
  class HtCIter;

  template< class Key, class Value, class Hash, class Equal >
  class HtIter: public std::iterator< std::bidirectional_iterator_tag, std::pair< const Key, Value >, std::ptrdiff_t, void, void >
  {
  public:
   ~HtIter() = default;
    HtIter() noexcept;

    std::pair< const Key, Value > operator*() const noexcept;
    Value& value() const noexcept;
    const Key& key() const noexcept;

    HtIter& operator++() noexcept;
    HtIter operator++(int) noexcept;
    HtIter& operator--() noexcept;
    HtIter operator--(int) noexcept;

    bool operator==(const HtIter& other) const noexcept;
    bool operator!=(const HtIter& other) const noexcept;

  private:
    Vector< detail::Slot< Key, Value > >* slots_;
    size_t idx_;

    HtIter(Vector< detail::Slot< Key, Value > >* slots, size_t idx) noexcept;
    friend class HashTable< Key, Value, Hash, Equal >;
    friend class HtCIter< Key, Value, Hash, Equal >;
  };

  template< class Key, class Value, class Hash, class Equal >
  class HtCIter: public std::iterator< std::bidirectional_iterator_tag, std::pair< const Key, Value >, std::ptrdiff_t, void, void >
  {
  public:
    ~HtCIter() = default;
    HtCIter() noexcept;

    const std::pair< const Key, Value > operator*() const noexcept;
    const Value& value() const noexcept;
    const Key& key() const noexcept;

    HtCIter& operator++() noexcept;
    HtCIter operator++(int) noexcept;
    HtCIter& operator--() noexcept;
    HtCIter operator--(int) noexcept;

    bool operator==(const HtCIter& other) const noexcept;
    bool operator!=(const HtCIter& other) const noexcept;

  private:
    const Vector< detail::Slot< Key, Value > >* slots_;
    size_t idx_;

    HtCIter(const Vector< detail::Slot< Key, Value > >* slots, size_t idx) noexcept;
    HtCIter(const HtIter< Key, Value, Hash, Equal >& it) noexcept;
    friend class HashTable< Key, Value, Hash, Equal >;
  };
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtIter< Key, Value, Hash, Equal >::HtIter() noexcept:
  slots_(nullptr),
  idx_(0)
{}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtIter< Key, Value, Hash, Equal >::HtIter(Vector< detail::Slot< Key, Value > >* slots, size_t idx) noexcept:
  slots_(slots),
  idx_(idx)
{}

template< class Key, class Value, class Hash, class Equal >
std::pair< const Key, Value > haliullin::HtIter< Key, Value, Hash, Equal >::operator*() const noexcept
{
  return std::pair< const Key, Value >((*slots_)[idx_].key_, (*slots_)[idx_].value_);
}

template< class Key, class Value, class Hash, class Equal >
Value& haliullin::HtIter< Key, Value, Hash, Equal >::value() const noexcept
{
  return (*slots_)[idx_].value_;
}

template< class Key, class Value, class Hash, class Equal >
const Key& haliullin::HtIter< Key, Value, Hash, Equal >::key() const noexcept
{
  return (*slots_)[idx_].key_;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtIter< Key, Value, Hash, Equal >& haliullin::HtIter< Key, Value, Hash, Equal >::operator++() noexcept
{
  ++idx_;
  while (idx_ < slots_->getSize() && (*slots_)[idx_].info_ != detail::SlotState::OCCUPIED)
  {
    ++idx_;
  }
  return *this;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtIter< Key, Value, Hash, Equal > haliullin::HtIter< Key, Value, Hash, Equal >::operator++(int) noexcept
{
  HtIter tmp = *this;
  ++(*this);
  return tmp;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtIter< Key, Value, Hash, Equal >& haliullin::HtIter< Key, Value, Hash, Equal >::operator--() noexcept
{
  if (!idx_)
  {
    return *this;
  }
  --idx_;
  while (idx_ < slots_->getSize() && (*slots_)[idx_].info_ != SlotState::OCCUPIED)
  {
    --idx_;
  }
  return *this;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtIter< Key, Value, Hash, Equal > haliullin::HtIter< Key, Value, Hash, Equal >::operator--(int) noexcept
{
  HtIter tmp = *this;
  --(*this);
  return tmp;
}

template< class Key, class Value, class Hash, class Equal >
bool haliullin::HtIter< Key, Value, Hash, Equal >::operator==(const HtIter& other) const noexcept
{
  return slots_ == other.slots_ && idx_ == other.idx_;
}

template< class Key, class Value, class Hash, class Equal >
bool haliullin::HtIter< Key, Value, Hash, Equal >::operator!=(const HtIter& other) const noexcept
{
  return !(*this == other);
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtCIter< Key, Value, Hash, Equal >::HtCIter() noexcept:
  slots_(nullptr),
  idx_(0)
{}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtCIter< Key, Value, Hash, Equal >::HtCIter(const Vector< detail::Slot<Key, Value > >* slots, size_t idx) noexcept:
  slots_(slots),
  idx_(idx)
{}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtCIter< Key, Value, Hash, Equal >::HtCIter(const HtIter< Key, Value, Hash, Equal >& it) noexcept:
  slots_(it.slots_),
  idx_(it.idx_)
{}

template< class Key, class Value, class Hash, class Equal >
const std::pair< const Key, Value > haliullin::HtCIter< Key, Value, Hash, Equal >::operator*() const noexcept
{
  return std::pair< const Key, Value >((*slots_)[idx_].key_, (*slots_)[idx_].value_);
}

template< class Key, class Value, class Hash, class Equal >
const Value& haliullin::HtCIter< Key, Value, Hash, Equal >::value() const noexcept
{
  return (*slots_)[idx_].value_;
}

template< class Key, class Value, class Hash, class Equal >
const Key& haliullin::HtCIter< Key, Value, Hash, Equal >::key() const noexcept
{
  return (*slots_)[idx_].key_;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtCIter< Key, Value, Hash, Equal >& haliullin::HtCIter< Key, Value, Hash, Equal >::operator++() noexcept
{
  ++idx_;
  while (idx_ < slots_->getSize() && (*slots_)[idx_].info_ != detail::SlotState::OCCUPIED)
  {
    ++idx_;
  }
  return *this;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtCIter< Key, Value, Hash, Equal > haliullin::HtCIter< Key, Value, Hash, Equal >::operator++(int) noexcept
{
  HtCIter tmp = *this;
  ++(*this);
  return tmp;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtCIter< Key, Value, Hash, Equal >& haliullin::HtCIter< Key, Value, Hash, Equal >::operator--() noexcept
{
  if (!idx_)
  {
    return *this;
  }
  --idx_;
  while (idx_ < slots_->getSize() && (*slots_)[idx_].info_ != detail::SlotState::OCCUPIED)
  {
    --idx_;
  }
  return *this;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtCIter< Key, Value, Hash, Equal > haliullin::HtCIter< Key, Value, Hash, Equal >::operator--(int) noexcept
{
  HtCIter tmp = *this;
  --(*this);
  return tmp;
}

template< class Key, class Value, class Hash, class Equal >
bool haliullin::HtCIter< Key, Value, Hash, Equal >::operator==(const HtCIter& other) const noexcept
{
  return slots_ == other.slots_ && idx_ == other.idx_;
}

template< class Key, class Value, class Hash, class Equal >
bool haliullin::HtCIter< Key, Value, Hash, Equal >::operator!=(const HtCIter& other) const noexcept
{
  return !(*this == other);
}

#endif
