#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <memory>
#include "vector.hpp"
#include "slot.hpp"
#include "HashTable-iterators.hpp"

namespace haliullin
{
  template< class Key, class Value, class Hash, class Equal >
  class HashTable
  {
  public:
    ~HashTable() = default;
    HashTable(size_t capacity = 16);

    HashTable(const HashTable& other);
    HashTable(HashTable&& other) noexcept;

    HashTable& operator=(const HashTable& other);
    HashTable& operator=(HashTable&& other) noexcept;
    void swap(HashTable& other) noexcept;

    void add(const Key& k, const Value& v);
    bool has(const Key& k) const noexcept;
    Value& get(const Key& k);
    const Value& get(const Key& k) const;
    HtIter< Key, Value, Hash, Equal > find(const Key& k) noexcept;
    HtCIter< Key, Value, Hash, Equal > find(const Key& k) const noexcept;
    void erase(const Key& k);
    void rehash(size_t newSize);

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    HtIter< Key, Value, Hash, Equal > begin() noexcept;
    HtCIter< Key, Value, Hash, Equal > begin() const noexcept;
    HtCIter< Key, Value, Hash, Equal > cbegin() const noexcept;
    HtIter< Key, Value, Hash, Equal > end() noexcept;
    HtCIter< Key, Value, Hash, Equal > end() const noexcept;
    HtCIter< Key, Value, Hash, Equal > cend() const noexcept;

  private:
    Vector< detail::Slot< Key, Value> > slots_;
    size_t size_;
    Hash hasher_;
    Equal equal_;

    size_t findIdx(const Key& k) const noexcept;
    size_t probe(size_t hash, size_t i) const noexcept;
  };
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HashTable< Key, Value, Hash, Equal >::HashTable(size_t capacity):
  slots_(capacity),
  size_(0),
  hasher_(),
  equal_()
{}

template< class Key, class Value, class Hash, class Equal >
haliullin::HashTable< Key, Value, Hash, Equal >::HashTable(const HashTable& other):
  slots_(other.slots_),
  size_(other.size_),
  hasher_(other.hasher_),
  equal_(other.equal_)
{}

template< class Key, class Value, class Hash, class Equal >
haliullin::HashTable< Key, Value, Hash, Equal >::HashTable(HashTable&& other) noexcept:
  slots_(),
  size_(0),
  hasher_(),
  equal_()
{
  swap(other);
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HashTable< Key, Value, Hash, Equal >& haliullin::HashTable< Key, Value, Hash, Equal >::operator=(const HashTable& other)
{
  if (this != std::addressof(other))
  {
    HashTable tmp(other);
    swap(tmp);
  }
  return *this;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HashTable< Key, Value, Hash, Equal >& haliullin::HashTable< Key, Value, Hash, Equal >::operator=(HashTable&& other) noexcept
{
  if (this != std::addressof(other))
  {
    HashTable tmp(std::move(other));
    swap(tmp);
  }
  return *this;
}

template< class Key, class Value, class Hash, class Equal >
void haliullin::HashTable< Key, Value, Hash, Equal >::swap(HashTable& other) noexcept
{
  slots_.swap(other.slots_);
  std::swap(size_, other.size_);
  std::swap(hasher_, other.hasher_);
  std::swap(equal_, other.equal_);
}

template< class Key, class Value, class Hash, class Equal >
void haliullin::HashTable< Key, Value, Hash, Equal >::add(const Key& k, const Value& v)
{
  size_t hash = hasher_(k);
  size_t insertIdx = slots_.getSize();

  for (size_t i = 0; i < slots_.getSize(); ++i)
  {
    size_t idx = probe(hash, i);
    detail::SlotState state = slots_[idx].info_;

    if (state == detail::SlotState::OCCUPIED && equal_(slots_[idx].kv_.first, k))
    {
      throw std::invalid_argument("Key already exists");
    }
    if (state != detail::SlotState::OCCUPIED && insertIdx == slots_.getSize())
    {
      insertIdx = idx;
      break;
    }
  }

  if (insertIdx == slots_.getSize())
  {
    throw std::runtime_error("Need to rehash hashtable");
  }

  Key keyCp(k);
  Value valCp(v);
  slots_[insertIdx].kv_.first = std::move(keyCp);
  slots_[insertIdx].kv_.second = std::move(valCp)
  slots_[insertIdx].info_ = detail::SlotState::OCCUPIED;
  ++size_;
}

template< class Key, class Value, class Hash, class Equal >
bool haliullin::HashTable< Key, Value, Hash, Equal >::has(const Key& k) const noexcept
{
  return findIdx(k) != slots_.getSize();
}

template< class Key, class Value, class Hash, class Equal >
Value& haliullin::HashTable< Key, Value, Hash, Equal >::get(const Key& k)
{
  size_t idx = findIdx(k);
  if (idx == slots_.getSize())
  {
    throw std::out_of_range("Key not found");
  }
  return slots_[idx].kv_.second;
}

template< class Key, class Value, class Hash, class Equal >
const Value& haliullin::HashTable< Key, Value, Hash, Equal >::get(const Key& k) const
{
  size_t idx = findIdx(k);
  if (idx == slots_.getSize())
  {
    throw std::out_of_range("Key not found");
  }
  return slots_[idx].kv_.second;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtIter< Key, Value, Hash, Equal > haliullin::HashTable< Key, Value, Hash, Equal >::find(const Key& k) noexcept
{
  size_t idx = findIdx(k);
  if (idx == slots_.getSize())
  {
    return end();
  }
  return HtIter< Key, Value, Hash, Equal >(std::addressof(slots_), idx);
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtCIter< Key, Value, Hash, Equal > haliullin::HashTable< Key, Value, Hash, Equal >::find(const Key& k) const noexcept
{
  size_t idx = findIdx(k);
  if (idx == slots_.getSize())
  {
    return end();
  }
  return HtCIter< Key, Value, Hash, Equal >(std::addressof(slots_), idx);
}

template< class Key, class Value, class Hash, class Equal >
void haliullin::HashTable< Key, Value, Hash, Equal >::erase(const Key& k)
{
  size_t idx = findIdx(k);
  if (idx == slots_.getSize())
  {
    throw std::out_of_range("Key not found");
  }
  slots_[idx].info_ = detail::SlotState::TOMBSTONE;
  --size_;
}

template< class Key, class Value, class Hash, class Equal >
void haliullin::HashTable< Key, Value, Hash, Equal >::rehash(size_t newSlots)
{
  if (newSlots < size_)
  {
    throw std::invalid_argument("Cannot rehash the table: new capacity is too small");
  }
  HashTable tmp(newSlots);
  for (size_t i = 0; i < slots_.getSize(); ++i)
  {
    if (slots_[i].info_ == detail::SlotState::OCCUPIED)
    {
      tmp.add(slots_[i].kv_.first, slots_[i].kv_.second);
    }
  }
  swap(tmp);
}

template< class Key, class Value, class Hash, class Equal >
bool haliullin::HashTable< Key, Value, Hash, Equal >::isEmpty() const noexcept
{
  return !size_;
}

template< class Key, class Value, class Hash, class Equal >
size_t haliullin::HashTable< Key, Value, Hash, Equal >::getSize() const noexcept
{
  return size_;
}

template< class Key, class Value, class Hash, class Equal >
size_t haliullin::HashTable< Key, Value, Hash, Equal >::getCapacity() const noexcept
{
  return slots_.getSize();
}

template< class Key, class Value, class Hash, class Equal >
size_t haliullin::HashTable< Key, Value, Hash, Equal >::findIdx(const Key& k) const noexcept
{
  size_t hash = hasher_(k);
  for (size_t i = 0; i < slots_.getSize(); ++i)
  {
    size_t idx = probe(hash, i);
    detail::SlotState state = slots_[idx].info_;

    if (state == detail::SlotState::EMPTY)
    {
      return slots_.getSize();
    }
    else if (state == detail::SlotState::OCCUPIED && equal_(slots_[idx].kv_.first, k))
    {
      return idx;
    }
  }
  return slots_.getSize();
}

template< class Key, class Value, class Hash, class Equal >
size_t haliullin::HashTable< Key, Value, Hash, Equal >::probe(size_t hash, size_t i) const noexcept
{
  return (hash + i * i) % getCapacity();
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtIter< Key, Value, Hash, Equal > haliullin::HashTable< Key, Value, Hash, Equal >::begin() noexcept
{
  for (size_t i = 0; i < slots_.getSize(); ++i)
  {
    if (slots_[i].info_ == detail::SlotState::OCCUPIED)
    {
      return HtIter< Key, Value, Hash, Equal >(std::addressof(slots_), i);
    }
  }
  return end();
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtCIter< Key, Value, Hash, Equal > haliullin::HashTable< Key, Value, Hash, Equal >::begin() const noexcept
{
  for (size_t i = 0; i < slots_.getSize(); ++i)
  {
    if (slots_[i].info_ == detail::SlotState::OCCUPIED)
    {
      return HtCIter< Key, Value, Hash, Equal >(std::addressof(slots_), i);
    }
  }
  return end();
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtCIter< Key, Value, Hash, Equal > haliullin::HashTable< Key, Value, Hash, Equal >::cbegin() const noexcept
{
  return begin();
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtIter< Key, Value, Hash, Equal > haliullin::HashTable< Key, Value, Hash, Equal >::end() noexcept
{
  return HtIter< Key, Value, Hash, Equal >(std::addressof(slots_), slots_.getSize());
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtCIter< Key, Value, Hash, Equal > haliullin::HashTable< Key, Value, Hash, Equal >::end() const noexcept
{
  return HtCIter< Key, Value, Hash, Equal >(std::addressof(slots_), slots_.getSize());
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HtCIter< Key, Value, Hash, Equal > haliullin::HashTable< Key, Value, Hash, Equal >::cend() const noexcept
{
  return end();
}

#endif
