#ifndef ITERATORS_HPP
#define ITERATORS_HPP
#include "node.hpp"

namespace haliullin
{
  template < class T >
  class LIter
  {
  private:
    friend class BiList<T>;
    Node<T> * cur;
    Node<T> * head;
    LIter(Node<T> * node, Node<T> * listHead):
      cur(node),
      head(listHead)
    {}

  public:
    LIter():
      cur(nullptr),
      head(nullptr)
    {}

    LIter(const LIter & other) = default;

    LIter(LIter && other) = default;

    ~LIter() = default;

    LIter & operator=(const LIter & other) = default;

    LIter & operator=(LIter && other) = default;

    bool operator==(const LIter & other) const
    {
      return cur == other.cur;
    }

    bool operator!=(const LIter & other) const
    {
      return !(*this == other);
    }

    T & operator*() const
    {
      return cur->val;
    }

    T * operator->() const
    {
      return &(cur->val);
    }

    LIter & operator++()
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

    LIter operator++(int)
    {
      LIter tmp(*this);
      ++(*this);
      return tmp;
    }

    LIter & operator--()
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

    LIter operator--(int)
    {
      LIter tmp(*this);
      --(*this);
      return tmp;
    }
  };

  template< class T >
  class LCIter
  {
  private:
    friend class BiList< T >;
    const Node< T > * cur;
    const Node< T > * head;
    LCIter(const Node<T> * node, const Node<T> * head):
      cur(node),
      head(head)
    {}

  public:
    LCIter():
      cur(nullptr),
      head(nullptr)
    {}

    LCIter(const LIter<T> & other):
      cur(other.cur),
      head(other.head)
    {}

    LCIter(const LCIter & other) = default;

    LCIter(LCIter && other) = default;

    ~LCIter() = default;

    LCIter & operator=(const LCIter & other) = default;

    LCIter & operator=(LCIter && other) = default;

    bool operator==(const LCIter & other) const
    {
      return cur == other.cur;
    }

    bool operator!=(const LCIter & other) const
    {
      return !(*this == other);
    }

    const T & operator*() const
    {
      return cur->val;
    }

    const T * operator->() const
    {
      return &(cur->val);
    }

    LCIter & operator++()
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

    LCIter operator++(int)
    {
      LCIter tmp(*this);
      ++(*this);
      return tmp;
    }

    LCIter & operator--()
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

    LCIter operator--(int)
    {
      LCIter tmp(*this);
      --(*this);
      return tmp;
    }
  };
}

#endif
