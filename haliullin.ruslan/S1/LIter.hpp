#ifndef LITER_HPP
#define LITER_HPP

#include "node.hpp"

namespace haliullin
{
  template < class T >
  class LIter
  {
  public:
    LIter();
    LIter(const LIter & other) = default;
    LIter(LIter && other) = default;
    ~LIter() = default;

    LIter & operator=(const LIter & other) = default;
    LIter & operator=(LIter && other) = default;

    bool operator==(const LIter & other) const noexcept;
    bool operator!=(const LIter & other) const noexcept;

    T & operator*() const noexcept;
    T * operator->() const noexcept;

    LIter & operator++() noexcept;
    LIter operator++(int) noexcept;
    LIter & operator--() noexcept;
    LIter operator--(int) noexcept;

  private:
    friend class BiList< T >;
    Node< T > * cur_;
    Node< T > * head_;
    explicit LIter(Node< T > * node, Node< T > * head);
  };
}

template < class T >
haliullin::LIter< T >::LIter():
  cur_(nullptr),
  head_(nullptr)
{}

template < class T >
haliullin::LIter< T >::LIter(Node< T > * node, Node< T > * head):
  cur_(node),
  head_(head)
{}

template < class T >
bool haliullin::LIter< T >::operator==(const LIter & other) const noexcept
{
  return cur_ == other.cur_;
}

template < class T >
bool haliullin::LIter< T >::operator!=(const LIter & other) const noexcept
{
  return !(*this == other);
}

template < class T >
T & haliullin::LIter< T >::operator*() const noexcept
{
  return cur_->val_;
}

template < class T >
T * haliullin::LIter< T >::operator->() const noexcept
{
  return &(cur_->val_);
}

template < class T >
haliullin::LIter< T > & haliullin::LIter< T >::operator++() noexcept
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
haliullin::LIter< T > haliullin::LIter< T >::operator++(int) noexcept
{
  LIter tmp(*this);
  ++(*this);
  return tmp;
}

template < class T >
haliullin::LIter< T > & haliullin::LIter< T >::operator--() noexcept
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
haliullin::LIter< T > haliullin::LIter< T >::operator--(int) noexcept
{
  LIter tmp(*this);
  --(*this);
  return tmp;
}

#endif
