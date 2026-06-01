#ifndef BILIST_ITERATORS_HPP
#define BILIST_ITERATORS_HPP

#include <iterator>
#include "node.hpp"

namespace haliullin
{
  template< class T >
  class BiList;

  template< class T >
  class LIter: public std::iterator< std::bidirectional_iterator_tag, T, std::ptrdiff_t, T*, T& >
  {
  public:
    LIter();
    ~LIter() = default;

    T& operator*() const noexcept;
    T* operator->() const noexcept;

    LIter< T >& operator++() noexcept;
    LIter< T > operator++(int) noexcept;
    LIter< T >& operator--() noexcept;
    LIter< T > operator--(int) noexcept;

    bool operator==(const LIter& other) const noexcept;
    bool operator!=(const LIter& other) const noexcept;

  private:
    detail::Node< T >* cur_;
    detail::Node< T >* head_;

    explicit LIter(detail::Node< T >* node, detail::Node< T >* head);
    friend class BiList< T >;
  };

  template< class T >
  class LCIter: public std::iterator< std::bidirectional_iterator_tag, T, std::ptrdiff_t, const T*, const T& >
  {
  public:
    LCIter();
    ~LCIter() = default;

    const T& operator*() const noexcept;
    const T* operator->() const noexcept;

    LCIter< T >& operator++() noexcept;
    LCIter< T > operator++(int) noexcept;
    LCIter< T >& operator--() noexcept;
    LCIter< T > operator--(int) noexcept;

    bool operator==(const LCIter& other) const noexcept;
    bool operator!=(const LCIter& other) const noexcept;

  private:
    const detail::Node< T >* cur_;
    const detail::Node< T >* head_;

    explicit LCIter(const detail::Node< T >* node, const detail::Node< T >* head);
    LCIter(const LIter< T >& other);
    friend class BiList< T >;
  };
}

template< class T >
haliullin::LIter< T >::LIter():
  cur_(nullptr),
  head_(nullptr)
{}

template< class T >
haliullin::LIter< T >::LIter(detail::Node< T >* node, detail::Node< T >* head):
  cur_(node),
  head_(head)
{}

template< class T >
T& haliullin::LIter< T >::operator*() const noexcept
{
  return cur_->val_;
}

template< class T >
T* haliullin::LIter< T >::operator->() const noexcept
{
  return std::addressof(cur_->val_);
}

template< class T >
haliullin::LIter< T >& haliullin::LIter< T >::operator++() noexcept
{
  cur_ = cur_->next_;
  if (cur_ == head_)
  {
    cur_ = nullptr;
  }
  return *this;
}

template< class T >
haliullin::LIter< T > haliullin::LIter< T >::operator++(int) noexcept
{
  LIter tmp(*this);
  ++(*this);
  return tmp;
}

template< class T >
haliullin::LIter< T >& haliullin::LIter< T >::operator--() noexcept
{
  if (cur_ == nullptr)
  {
    cur_ = head_->prev_;
  }
  else if (cur_ == head_)
  {
    cur_ = nullptr;
  }
  else
  {
    cur_ = cur_->prev_;
  }
  return *this;
}

template< class T >
haliullin::LIter< T > haliullin::LIter< T >::operator--(int) noexcept
{
  LIter tmp(*this);
  --(*this);
  return tmp;
}

template< class T >
bool haliullin::LIter< T >::operator==(const LIter& other) const noexcept
{
  return cur_ == other.cur_;
}

template< class T >
bool haliullin::LIter< T >::operator!=(const LIter& other) const noexcept
{
  return !(*this == other);
}

template< class T >
haliullin::LCIter< T >::LCIter():
  cur_(nullptr),
  head_(nullptr)
{}

template< class T >
haliullin::LCIter< T >::LCIter(const detail::Node< T >* node, const detail::Node< T >* head):
  cur_(node),
  head_(head)
{}

template< class T >
haliullin::LCIter< T >::LCIter(const LIter< T >& other):
  cur_(other.cur_),
  head_(other.head_)
{}

template< class T >
const T& haliullin::LCIter< T >::operator*() const noexcept
{
  return cur_->val_;
}

template< class T >
const T* haliullin::LCIter< T >::operator->() const noexcept
{
  return std::addressof(cur_->val_);
}

template< class T >
haliullin::LCIter< T >& haliullin::LCIter< T >::operator++() noexcept
{
  cur_ = cur_->next_;
  if (cur_ == head_)
  {
    cur_ = nullptr;
  }
  return *this;
}

template< class T >
haliullin::LCIter< T > haliullin::LCIter< T >::operator++(int) noexcept
{
  LCIter tmp(*this);
  ++(*this);
  return tmp;
}

template< class T >
haliullin::LCIter< T >& haliullin::LCIter< T >::operator--() noexcept
{
  if (cur_ == nullptr)
  {
    cur_ = head_->prev_;
  }
  else if (cur_ == head_)
  {
    cur_ = nullptr;
  }
  else
  {
    cur_ = cur_->prev_;
  }
  return *this;
}

template< class T >
haliullin::LCIter< T > haliullin::LCIter< T >::operator--(int) noexcept
{
  LCIter tmp(*this);
  --(*this);
  return tmp;
}

template< class T >
bool haliullin::LCIter< T >::operator==(const LCIter& other) const noexcept
{
  return cur_ == other.cur_;
}

template< class T >
bool haliullin::LCIter< T >::operator!=(const LCIter& other) const noexcept
{
  return !(*this == other);
}

#endif
