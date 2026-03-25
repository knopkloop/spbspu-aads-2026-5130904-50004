#ifndef LCITER_HPP
#define LCITER_HPP

#include "node.hpp"

namespace haliullin
{
  template < class T >
  class LCIter
  {
  public:
    LCIter();
    LCIter(const LIter< T > & other);
    LCIter(const LCIter & other) = default;
    LCIter(LCIter && other) = default;
    ~LCIter() = default;

    LCIter & operator=(const LCIter & other) = default;
    LCIter & operator=(LCIter && other) = default;

    bool operator==(const LCIter & other) const noexcept;
    bool operator!=(const LCIter & other) const noexcept;

    const T & operator*() const noexcept;
    const T * operator->() const noexcept;

    LCIter & operator++() noexcept;
    LCIter operator++(int) noexcept;
    LCIter & operator--() noexcept;
    LCIter operator--(int) noexcept;

  private:
    friend class BiList< T >;
    const Node< T > * cur_;
    const Node< T > * head_;
    explicit LCIter(const Node< T > * node, const Node< T > * head);
  };
}

template < class T >
haliullin::LCIter< T >::LCIter():
  cur_(nullptr),
  head_(nullptr)
{}

template < class T >
haliullin::LCIter< T >::LCIter(const Node< T > * node, const Node< T > * head):
  cur_(node),
  head_(head)
{}

template < class T >
haliullin::LCIter< T >::LCIter(const LIter< T > & other):
  cur_(other.cur_),
  head_(other.head_)
{}

template < class T >
bool haliullin::LCIter< T >::operator==(const LCIter & other) const noexcept
{
  return cur_ == other.cur_;
}

template < class T >
bool haliullin::LCIter< T >::operator!=(const LCIter & other) const noexcept
{
  return !(*this == other);
}

template < class T >
const T & haliullin::LCIter< T >::operator*() const noexcept
{
  return cur_->val_;
}

template < class T >
const T * haliullin::LCIter< T >::operator->() const noexcept
{
  return &(cur_->val_);
}

template < class T >
haliullin::LCIter< T > & haliullin::LCIter< T >::operator++() noexcept
{
  if (cur_)
  {
    cur_ = cur_->next_;
    if (cur_ == head_)
    {
      cur_ = nullptr;
    }
  }
  return *this;
}

template < class T >
haliullin::LCIter< T > haliullin::LCIter< T >::operator++(int) noexcept
{
  LCIter tmp(*this);
  ++(*this);
  return tmp;
}

template < class T >
haliullin::LCIter< T > & haliullin::LCIter< T >::operator--() noexcept
{
  if (cur_ == head_)
  {
    cur_ = nullptr;
  }
  else if (cur_)
  {
    cur_ = cur_->prev_;
  }
  return *this;
}

template < class T >
haliullin::LCIter< T > haliullin::LCIter< T >::operator--(int) noexcept
{
  LCIter tmp(*this);
  --(*this);
  return tmp;
}

#endif
