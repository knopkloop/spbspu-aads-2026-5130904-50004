#ifndef SLOT_HPP
#define SLOT_HPP

namespace haliullin
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
    Slot() noexcept;

    Key key_;
    Value value_;
    SlotState info_;
  };
}

template< class Key, class Value >
haliullin::Slot< Key, Value >::Slot() noexcept:
  key_(),
  value_(),
  info_(SlotState::EMPTY)
{}

#endif
