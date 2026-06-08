#ifndef ROBINHASHTABLE_HPP
#define ROBINHASHTABLE_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <memory>
#include "Vector.hpp"
#include "Slot.hpp"
#include "RobinHash-iterators.hpp"

namespace haliullin
{
  template< class Key, class Value, class Hash, class Equal >
  class RobinHashTable
  {
  public:
    using slot_t = detail::Slot< Key, Value >;
    using iterator = RHTableIterator< Key, Value >;
    using const_iterator = RHTableConstIterator< Key, Value >;

    ~RobinHashTable() = default;
    RobinHashTable(size_t capacity = 16, double maxLoadFactor = 0.9);

    RobinHashTable(const RobinHashTable& other);
    RobinHashTable(RobinHashTable&& other) noexcept;

    RobinHashTable& operator=(const RobinHashTable& other);
    RobinHashTable& operator=(RobinHashTable&& other) noexcept;
    void swap(RobinHashTable& other) noexcept;

    void add(const Key& k, const Value& v);
    void erase(const Key& k);
    bool has(const Key& k) const noexcept;
    Value& get(const Key& k);
    const Value& get(const Key& k) const;
    iterator find(const Key& k) noexcept;
    const_iterator find(const Key& k) const noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

  private:
    Vector< slot_t > slots_;
    size_t size_;
    Hash hasher_;
    Equal equal_;
    double maxLoadFactor_;

    size_t findSlot(const Key& k) const noexcept;
    void rehash(size_t newCap);
    void insertInternal(const Key& k, const Value& v);
  };
}

template< class Key, class Value, class Hash, class Equal >
haliullin::RobinHashTable< Key, Value, Hash, Equal >::RobinHashTable(size_t capacity, double maxLoadFactor):
  slots_(capacity),
  size_(0),
  hasher_(),
  equal_(),
  maxLoadFactor_(maxLoadFactor)
{}

template< class Key, class Value, class Hash, class Equal >
haliullin::RobinHashTable< Key, Value, Hash, Equal >::RobinHashTable(const RobinHashTable& other):
  slots_(other.slots_),
  size_(other.size_),
  hasher_(other.hasher_),
  equal_(other.equal_),
  maxLoadFactor_(other.maxLoadFactor_)
{}

template< class Key, class Value, class Hash, class Equal >
haliullin::RobinHashTable< Key, Value, Hash, Equal >::RobinHashTable(RobinHashTable&& other) noexcept:
  slots_(),
  size_(0),
  hasher_(),
  equal_(),
  maxLoadFactor_(0.0)
{
  swap(other);
}

template< class Key, class Value, class Hash, class Equal >
haliullin::RobinHashTable< Key, Value, Hash, Equal >&
haliullin::RobinHashTable< Key, Value, Hash, Equal >::operator=(const RobinHashTable& other)
{
  if (this != std::addressof(other))
  {
    RobinHashTable tmp(other);
    swap(tmp);
  }
  return *this;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::RobinHashTable< Key, Value, Hash, Equal >&
haliullin::RobinHashTable< Key, Value, Hash, Equal >::operator=(RobinHashTable&& other) noexcept
{
  if (this != std::addressof(other))
  {
    RobinHashTable tmp(std::move(other));
    swap(tmp);
  }
  return *this;
}

template< class Key, class Value, class Hash, class Equal >
void haliullin::RobinHashTable< Key, Value, Hash, Equal >::swap(RobinHashTable& other) noexcept
{
  slots_.swap(other.slots_);
  std::swap(size_, other.size_);
  std::swap(hasher_, other.hasher_);
  std::swap(equal_, other.equal_);
  std::swap(maxLoadFactor_, other.maxLoadFactor_);
}

template< class Key, class Value, class Hash, class Equal >
void haliullin::RobinHashTable< Key, Value, Hash, Equal >::add(const Key& k, const Value& v)
{
  RobinHashTable tmp(*this);
  if (tmp.findSlot(k) != tmp.getCapacity())
  {
    size_t idx = tmp.findSlot(k);
    tmp.slots_[idx].kv_.second = v;
  }
  else
  {
    tmp.insertInternal(k, v);
  }
  swap(tmp);
}

template< class Key, class Value, class Hash, class Equal >
void haliullin::RobinHashTable< Key, Value, Hash, Equal >::erase(const Key& k)
{
  RobinHashTable tmp(*this);
  size_t idx = tmp.findSlot(k);
  if (idx == tmp.getCapacity())
  {
    throw std::out_of_range("Key not found");
  }
  tmp.slots_[idx].kv_.first = Key();
  tmp.slots_[idx].kv_.second = Value();
  tmp.slots_[idx].psl_ = -1;
  --tmp.size_;

  size_t next = (idx + 1) % tmp.getCapacity();
  while (tmp.slots_[next].psl_ > 0)
  {
    slot_t& from = tmp.slots_[next];
    slot_t& to = tmp.slots_[idx];

    to.kv_.first = std::move(from.kv_.first);
    to.kv_.second = std::move(from.kv_.second);
    to.psl_ = from.psl_ - 1;

    from.kv_.first = Key();
    from.kv_.second = Value();
    from.psl_ = -1;

    idx = next;
    next = (next + 1) % tmp.getCapacity();
  }
  swap(tmp);
}

template< class Key, class Value, class Hash, class Equal >
bool haliullin::RobinHashTable< Key, Value, Hash, Equal >::has(const Key& k) const noexcept
{
  return findSlot(k) != getCapacity();
}

template< class Key, class Value, class Hash, class Equal >
Value& haliullin::RobinHashTable< Key, Value, Hash, Equal >::get(const Key& k)
{
  size_t idx = findSlot(k);
  if (idx == getCapacity())
  {
    throw std::out_of_range("Key not found");
  }
  return slots_[idx].kv_.second;
}

template< class Key, class Value, class Hash, class Equal >
const Value& haliullin::RobinHashTable< Key, Value, Hash, Equal >::get(const Key& k) const
{
  size_t idx = findSlot(k);
  if (idx == getCapacity())
  {
    throw std::out_of_range("Key not found");
  }
  return slots_[idx].kv_.second;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::RHTableIterator< Key, Value > haliullin::RobinHashTable< Key, Value, Hash, Equal >::find(const Key& k) noexcept
{
  size_t idx = findSlot(k);
  if (idx == getCapacity())
  {
    return end();
  }
  VIter< slot_t > cur(std::addressof(slots_[idx]));
  return iterator(cur, slots_.end());
}

template< class Key, class Value, class Hash, class Equal >
haliullin::RHTableConstIterator< Key, Value > haliullin::RobinHashTable< Key, Value, Hash, Equal >::find(const Key& k) const noexcept
{
  size_t idx = findSlot(k);
  if (idx == getCapacity())
  {
    return cend();
  }
  VCIter< slot_t > cur(std::addressof(slots_[idx]));
  return const_iterator(cur, slots_.cend());
}

template< class Key, class Value, class Hash, class Equal >
bool haliullin::RobinHashTable< Key, Value, Hash, Equal >::isEmpty() const noexcept
{
  return !size_;
}

template< class Key, class Value, class Hash, class Equal >
size_t haliullin::RobinHashTable< Key, Value, Hash, Equal >::getSize() const noexcept
{
  return size_;
}

template< class Key, class Value, class Hash, class Equal >
size_t haliullin::RobinHashTable< Key, Value, Hash, Equal >::getCapacity() const noexcept
{
  return slots_.getSize();
}

template< class Key, class Value, class Hash, class Equal >
size_t haliullin::RobinHashTable< Key, Value, Hash, Equal >::findSlot(const Key& k) const noexcept
{
  size_t hash = hasher_(k);
  for (size_t i = 0; i < getCapacity(); ++i)
  {
    size_t idx = (hash + i) % getCapacity();
    const slot_t& slot = slots_[idx];
    if (slot.psl_ == -1)
    {
      return getCapacity();
    }
    if (slot.psl_ >= static_cast< int >(i) && equal_(slot.kv_.first, k))
    {
      return idx;
    }
  }
  return getCapacity();
}

template< class Key, class Value, class Hash, class Equal >
void haliullin::RobinHashTable< Key, Value, Hash, Equal >::insertInternal(const Key& k, const Value& v)
{
  if (findSlot(k) != getCapacity())
  {
    throw std::invalid_argument("Key already exists");
  }
  if (size_ + 1 > static_cast< size_t >(maxLoadFactor_ * getCapacity()))
  {
    size_t newCap = getCapacity() * 2;
    newCap = newCap < 16 ? 16 : newCap;
    rehash(newCap);
  }

  size_t hash = hasher_(k);
  slot_t curSlot(k, v);

  for (size_t i = 0; i < getCapacity(); ++i)
  {
    size_t idx = (hash + curSlot.psl_) % getCapacity();
    slot_t& slot = slots_[idx];

    if (slot.psl_ == -1)
    {
      slot.kv_.first = std::move(curSlot.kv_.first);
      slot.kv_.second = std::move(curSlot.kv_.second);
      slot.psl_ = curSlot.psl_;
      ++size_;
      return;
    }
    if (curSlot.psl_ > slot.psl_)
    {
      slot.swap(curSlot);
    }
    ++curSlot.psl_;
  }
  throw std::runtime_error("Unexpected full table");
}

template< class Key, class Value, class Hash, class Equal >
void haliullin::RobinHashTable< Key, Value, Hash, Equal >::rehash(size_t newCap)
{
  if (newCap < size_)
  {
    throw std::invalid_argument("New capacity too small");
  }

  RobinHashTable tmp(newCap, maxLoadFactor_);
  tmp.hasher_ = hasher_;
  tmp.equal_ = equal_;

  for (size_t i = 0; i < getCapacity(); ++i)
  {
    if (slots_[i].psl_ != -1)
    {
      const std::pair< Key, Value >& kv = slots_[i].kv_;
      tmp.insertInternal(kv.first, kv.second);
    }
  }
  swap(tmp);
}

template< class Key, class Value, class Hash, class Equal >
haliullin::RHTableIterator< Key, Value > haliullin::RobinHashTable< Key, Value, Hash, Equal >::begin() noexcept
{
  auto first = slots_.begin();
  auto last = slots_.end();
  while ((first != last) && (first->psl_ == -1))
  {
    ++first;
  }
  return iterator(first, last);
}

template< class Key, class Value, class Hash, class Equal >
haliullin::RHTableConstIterator< Key, Value > haliullin::RobinHashTable< Key, Value, Hash, Equal >::begin() const noexcept
{
  auto first = slots_.cbegin();
  auto last = slots_.cend();
  while ((first != last) && (first->psl_ == -1))
  {
    ++first;
  }
  return const_iterator(first, last);
}

template< class Key, class Value, class Hash, class Equal >
haliullin::RHTableConstIterator< Key, Value > haliullin::RobinHashTable< Key, Value, Hash, Equal >::cbegin() const noexcept
{
  return begin();
}

template< class Key, class Value, class Hash, class Equal >
haliullin::RHTableIterator< Key, Value > haliullin::RobinHashTable< Key, Value, Hash, Equal >::end() noexcept
{
  return iterator(slots_.end(), slots_.end());
}

template< class Key, class Value, class Hash, class Equal >
haliullin::RHTableConstIterator< Key, Value > haliullin::RobinHashTable< Key, Value, Hash, Equal >::end() const noexcept
{
  return const_iterator(slots_.cend(), slots_.cend());
}

template< class Key, class Value, class Hash, class Equal >
haliullin::RHTableConstIterator< Key, Value > haliullin::RobinHashTable< Key, Value, Hash, Equal >::cend() const noexcept
{
  return end();
}

#endif
