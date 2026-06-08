#ifndef ROBINHASHTABLE_HPP
#define ROBINHASHTABLE_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <memory>
#include "Vector.hpp"
#include "Slot.hpp"
#include "Vector-iterators.hpp"

namespace haliullin
{
  template< class Key, class Value, class Hash, class Equal >
  class RobinHashTable
  {
  public:
    using slot_t = detail::Slot< Key, Value >;

    ~RobinHashTable() = default;
    RobinHashTable(size_t capacity = 16, double maxLoadFactor = 0.9);

    RobinHashTable(const RobinHashTable& other);
    RobinHashTable(RobinHashTable&& other) noexcept;

    RobinHashTable& operator=(const RobinHashTable& other);
    RobinHashTable& operator=(RobinHashTable&& other) noexcept;
    void swap(RobinHashTable& other) noexcept;

    void insert(const Key& k, const Value& v);
    void erase(const Key& k);
    bool has(const Key& k) const noexcept;
    Value& get(const Key& k);
    const Value& get(const Key& k) const;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

  private:
    Vector< slot_t > slots_;
    size_t size_;
    Hash hasher_;
    Equal equal_;
    double maxLoadFactor_;

    size_t findSlot(const Key& k) const noexcept;
    void rehash(size_t newCap);
    void insertInternal(const Key& k, const Value& v);
    void eraseInternal(const Key& k);
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
haliullin::RobinHashTable< Key, Value, Hash, Equal >& haliullin::RobinHashTable< Key, Value, Hash, Equal >::operator=(const RobinHashTable& other)
{
  if (this != std::addressof(other))
  {
    RobinHashTable tmp(other);
    swap(tmp);
  }
  return *this;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::RobinHashTable< Key, Value, Hash, Equal >& haliullin::RobinHashTable< Key, Value, Hash, Equal >::operator=(RobinHashTable&& other) noexcept
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

#endif
