#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include "node.hpp"

namespace haliullin
{
  template < class T >
  class LIter
  {
  private:
    friend class BiList< T >;
    Node< T > * cur;
    Node< T > * head;
    explicit LIter(Node< T > * node, Node< T > * listHead) noexcept;

  public:
    LIter() noexcept;
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
  };

  template < class T >
  class LCIter
  {
  private:
    friend class BiList< T >;
    const Node< T > * cur;
    const Node< T > * head;
    explicit LCIter(const Node< T > * node, const Node< T > * listHead) noexcept;

  public:
    LCIter() noexcept;
    LCIter(const LIter< T > & other) noexcept;
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
  };

  template < class T >
  LIter< T >::LIter(Node< T > * node, Node< T > * listHead) noexcept:
    cur(node),
    head(listHead)
  {}

  template < class T >
  LIter< T >::LIter() noexcept:
    cur(nullptr),
    head(nullptr)
  {}

  template < class T >
  bool LIter< T >::operator==(const LIter & other) const noexcept
  {
    return cur == other.cur;
  }

  template < class T >
  bool LIter< T >::operator!=(const LIter & other) const noexcept
  {
    return !(*this == other);
  }

  template < class T >
  T & LIter< T >::operator*() const noexcept
  {
    return cur->val;
  }

  template < class T >
  T * LIter< T >::operator->() const noexcept
  {
    return &(cur->val);
  }

  template < class T >
  LIter< T > & LIter< T >::operator++() noexcept
  {
    if (cur)
    {
      cur = cur->next;
      if (cur == head)
      {
        cur = nullptr;
      }
    }
    return *this;
  }

  template < class T >
  LIter< T > LIter< T >::operator++(int) noexcept
  {
    LIter tmp(*this);
    ++(*this);
    return tmp;
  }

  template < class T >
  LIter< T > & LIter< T >::operator--() noexcept
  {
    if (cur == head)
    {
      cur = nullptr;
    }
    else if (cur)
    {
      cur = cur->prev;
    }
    return *this;
  }

  template < class T >
  LIter< T > LIter< T >::operator--(int) noexcept
  {
    LIter tmp(*this);
    --(*this);
    return tmp;
  }

  template < class T >
  LCIter< T >::LCIter(const Node< T > * node, const Node< T > * listHead) noexcept:
    cur(node),
    head(listHead)
  {}

  template < class T >
  LCIter< T >::LCIter() noexcept:
    cur(nullptr),
    head(nullptr)
  {}

  template < class T >
  LCIter< T >::LCIter(const LIter< T > & other) noexcept:
    cur(other.cur),
    head(other.head)
  {}

  template < class T >
  bool LCIter< T >::operator==(const LCIter & other) const noexcept
  {
    return cur == other.cur;
  }

  template < class T >
  bool LCIter< T >::operator!=(const LCIter & other) const noexcept
  {
    return !(*this == other);
  }

  template < class T >
  const T & LCIter< T >::operator*() const noexcept
  {
    return cur->val;
  }

  template < class T >
  const T * LCIter< T >::operator->() const noexcept
  {
    return &(cur->val);
  }

  template < class T >
  LCIter< T > & LCIter< T >::operator++() noexcept
  {
    if (cur)
    {
      cur = cur->next;
      if (cur == head)
      {
        cur = nullptr;
      }
    }
    return *this;
  }

  template < class T >
  LCIter< T > LCIter< T >::operator++(int) noexcept
  {
    LCIter tmp(*this);
    ++(*this);
    return tmp;
  }

  template < class T >
  LCIter< T > & LCIter< T >::operator--() noexcept
  {
    if (cur == head)
    {
      cur = nullptr;
    }
    else if (cur)
    {
      cur = cur->prev;
    }
    return *this;
  }

  template < class T >
  LCIter< T > LCIter< T >::operator--(int) noexcept
  {
    LCIter tmp(*this);
    --(*this);
    return tmp;
  }
}

#endif
