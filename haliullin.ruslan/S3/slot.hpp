#ifndef SLOT_HPP
#define SLOT_HPP

namespace haliullin
{
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
        key_(),
        value_(),
        info_(SlotState::EMPTY)
      {}

      Key key_;
      Value value_;
      SlotState info_;
    };
  }
}

#endif
