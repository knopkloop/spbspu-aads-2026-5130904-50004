#ifndef ROBINHOODHASHTABLE_HPP
#define ROBINHOODHASHTABLE_HPP

#include <cstddef>
#include <utility>
#include "Vector.hpp"
#include "Slot.hpp"
#include "Vector-iterators.hpp"

namespace haliullin
{
  template< class Key, class Value, class Hash, class Equal >
  class RobinHoodHashTable;

  template< class Key, class Value, class Hash, class Equal >
  class RobinHoodHashTable
  {
  public:
    using SlotType = detail::Slot<Key, Value>;

    RobinHoodHashTable(size_t capacity = 16, double maxLoadFactor = 0.9);
    ~RobinHoodHashTable() = default;

    RobinHoodHashTable(const RobinHoodHashTable& other);
    RobinHoodHashTable(RobinHoodHashTable&& other) noexcept;

    RobinHoodHashTable& operator=(const RobinHoodHashTable& other);
    RobinHoodHashTable& operator=(RobinHoodHashTable&& other) noexcept;
    void swap(RobinHoodHashTable& other) noexcept;

    void insert(const Key& k, const Value& v);
    void erase(const Key& k);
    bool has(const Key& k) const noexcept;
    Value& get(const Key& k);
    const Value& get(const Key& k) const;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

  private:
    Vector< SlotType > slots_;
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

#endif
