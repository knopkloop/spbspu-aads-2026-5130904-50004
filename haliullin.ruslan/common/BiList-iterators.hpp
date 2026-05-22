#ifndef BILIST_ITERATORS_HPP
#define BILIST_ITERATORS_HPP

#include "../common/node.hpp"
#include <iterator>

namespace haliullin
{
  template< class T >
  class LIter: public std::iterator< std::bidirectional_iterator_tag, T, std::ptrdiff_t, T*, T& >
  {
  public:
    LIter();
    ~LIter() = default;

    bool operator==(const LIter& other) const noexcept;
    bool operator!=(const LIter& other) const noexcept;

    T& operator*() const noexcept;
    T* operator->() const noexcept;

    LIter< T >& operator++() noexcept;
    LIter< T > operator++(int) noexcept;
    LIter< T >& operator--() noexcept;
    LIter< T > operator--(int) noexcept;

  private:
    friend class BiList< T >;
    Node< T >* cur_;
    Node< T >* head_;
    explicit LIter(Node< T >* node, Node< T >* head);
  };

  template< class T >
  class LCIter: public std::iterator< std::bidirectional_iterator_tag, T, std::ptrdiff_t, const T*, const T& >
  {
  public:
    LCIter();
    LCIter(const LIter< T >& other);
    ~LCIter() = default;

    bool operator==(const LCIter& other) const noexcept;
    bool operator!=(const LCIter& other) const noexcept;

    const T& operator*() const noexcept;
    const T* operator->() const noexcept;

    LCIter< T >& operator++() noexcept;
    LCIter< T > operator++(int) noexcept;
    LCIter< T >& operator--() noexcept;
    LCIter< T > operator--(int) noexcept;

  private:
    friend class BiList< T >;
    const Node< T >* cur_;
    const Node< T >* head_;
    explicit LCIter(const Node< T >* node, const Node< T >* head);
  };
}

template< class T >
haliullin::LIter< T >::LIter():
  cur_(nullptr),
  head_(nullptr)
{}

template< class T >
haliullin::LIter< T >::LIter(Node< T >* node, Node< T >* head):
  cur_(node),
  head_(head)
{}

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
T& haliullin::LIter< T >::operator*() const noexcept
{
  return cur_->val_;
}

template< class T >
T* haliullin::LIter< T >::operator->() const noexcept
{
  return &(cur_->val_);
}

template< class T >
haliullin::LIter< T >& haliullin::LIter< T >::operator++() noexcept
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

template< class T >
haliullin::LIter< T > haliullin::LIter< T >::operator--(int) noexcept
{
  LIter tmp(*this);
  --(*this);
  return tmp;
}

template< class T >
haliullin::LCIter< T >::LCIter():
  cur_(nullptr),
  head_(nullptr)
{}

template< class T >
haliullin::LCIter< T >::LCIter(const Node< T >* node, const Node< T >* head):
  cur_(node),
  head_(head)
{}

template< class T >
haliullin::LCIter< T >::LCIter(const LIter< T >& other):
  cur_(other.cur_),
  head_(other.head_)
{}

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

template< class T >
const T& haliullin::LCIter< T >::operator*() const noexcept
{
  return cur_->val_;
}

template< class T >
const T* haliullin::LCIter< T >::operator->() const noexcept
{
  return &(cur_->val_);
}

template< class T >
haliullin::LCIter< T >& haliullin::LCIter< T >::operator++() noexcept
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

template< class T >
haliullin::LCIter< T > haliullin::LCIter< T >::operator--(int) noexcept
{
  LCIter tmp(*this);
  --(*this);
  return tmp;
}

#endif
