#ifndef SLOT_HPP
#define SLOT_HPP

#include <utility>

namespace haliullin
{
  template< class Key, class Value, class Hash, class Equal >
  class HashTable;

  template< class Key, class Value, class Hash, class Equal >
  class HtIter;

  template< class Key, class Value, class Hash, class Equal >
  class HtCIter;

  namespace detail
  {
    enum class SlotState: char
    {
      EMPTY = 'e',
      OCCUPIED = 'o',
      TOMBSTONE = 't'
    };

    template< class Key, class Value >
    struct Slot
    {
      Slot() noexcept:
        kv_(),
        info_(SlotState::EMPTY)
      {}

    private:
      std::pair< Key, Value > kv_;
      SlotState info_;

      template< class K, class V, class H, class E >
      friend class haliullin::HashTable;

      template< class K, class V, class H, class E >
      friend class haliullin::HtIter;

      template< class K, class V, class H, class E >
      friend class haliullin::HtCIter;
    };
  }
}

#endif
