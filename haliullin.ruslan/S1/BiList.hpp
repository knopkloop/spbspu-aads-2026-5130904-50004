#ifndef BILIST_HPP
#define BILIST_HPP

#include "iterators.hpp"
#include <iostream>
#include <utility>

namespace haliullin
{
  template < class T >
  class BiList
  {
  private:
    Node< T > *head;
    size_t size;

  public:
    BiList();
    BiList(const BiList & other);
    BiList(BiList && other) noexcept;
    ~BiList();

    BiList & operator=(const BiList & other);
    BiList & operator=(BiList && other) noexcept;

    bool is_empty() const;
    size_t getsize() const;

    T & front();
    const T & front() const;
    T & back();
    const T & back() const;

    LIter< T > begin();
    LCIter< T > cbegin() const;
    LIter< T > end();
    LCIter< T > cend() const;

    void push_front(const T & value);
    void push_front(T && value);
    void push_back(const T & value);
    void push_back(T && value);

    LIter< T > insert(LIter< T > pos, const T & value);
    LIter< T > insert(LIter< T > pos, T && value);

    void pop_front();
    void pop_back();

    LIter< T > erase(LIter< T > pos);

    void clear();
    void swap(BiList & other) noexcept;
  };

  template < class T >
  BiList< T >::BiList():
    head(nullptr),
    size(0)
  {}

  template < class T >
  BiList< T >::BiList(const BiList & other):
    head(nullptr),
    size(0)
  {
    if (other.is_empty())
    {
      return;
    }
    Node< T > * current = other.head;
    Node< T > * first = new Node< T >(current->val);
    head = first;
    size = 1;
    current = current->next;
    Node< T > * prev = first;
    while (current != other.head)
    {
      Node< T > * newNode = new Node< T >(current->val);
      prev->next = newNode;
      newNode->prev = prev;
      prev = newNode;
      current = current->next;
      ++size;
    }
    prev->next = head;
    head->prev = prev;
  }

  template < class T >
  BiList< T >::BiList(BiList && other) noexcept:
    head(other.head),
    size(other.size)
  {
    other.head = nullptr;
    other.size = 0;
  }

  template < class T >
  BiList< T >::~BiList()
  {
    clear();
  }

  template < class T >
  BiList< T > & BiList< T >::operator=(const BiList & other)
  {
    if (this != &other)
    {
      BiList tmp(other);
      swap(tmp);
    }
    return *this;
  }

  template < class T >
  BiList< T > & BiList< T >::operator=(BiList && other) noexcept
  {
    if (this != &other)
    {
      clear();
      head = other.head;
      size = other.size;
      other.head = nullptr;
      other.size = 0;
    }
    return *this;
  }

  template < class T >
  bool BiList< T >::is_empty() const
  {
    return size == 0;
  }

  template < class T >
  size_t BiList< T >::getsize() const
  {
    return size;
  }

  template < class T >
  T & BiList< T >::front()
  {
    if (is_empty())
    {
      throw std::runtime_error("Empty list");
    }
    return head->val;
  }

  template < class T >
  const T & BiList< T >::front() const
  {
    if (is_empty())
    {
      throw std::runtime_error("Empty list");
    }
    return head->val;
  }

  template < class T >
  T & BiList< T >::back()
  {
    if (is_empty())
    {
      throw std::runtime_error("Empty list");
    }
    return head->prev->val;
  }

  template < class T >
  const T & BiList< T >::back() const
  {
    if (is_empty())
    {
      throw std::runtime_error("Empty list");
    }
    return head->prev->val;
  }

  template < class T >
  LIter< T > BiList< T >::begin()
  {
    return LIter< T >(head, head);
  }

  template < class T >
  LCIter< T > BiList< T >::cbegin() const
  {
    return LCIter< T >(head, head);
  }

  template < class T >
  LIter< T > BiList< T >::end()
  {
    return LIter< T >(nullptr, head);
  }

  template < class T >
  LCIter< T > BiList< T >::cend() const
  {
    return LCIter< T >(nullptr, head);
  }

  template < class T >
  void BiList< T >::push_front(const T & value)
  {
    Node< T > * newNode = new Node< T >(value);
    if (is_empty())
    {
      head = newNode;
      head->next = head;
      head->prev = head;
    }
    else
    {
      newNode->next = head;
      newNode->prev = head->prev;
      head->prev->next = newNode;
      head->prev = newNode;
      head = newNode;
    }
    ++size;
  }

  template < class T >
  void BiList< T >::push_front(T && value)
  {
    Node< T > * newNode = new Node< T >(std::move(value));
    if (is_empty())
    {
      head = newNode;
      head->next = head;
      head->prev = head;
    }
    else
    {
      newNode->next = head;
      newNode->prev = head->prev;
      head->prev->next = newNode;
      head->prev = newNode;
      head = newNode;
    }
    ++size;
  }

  template < class T >
  void BiList< T >::push_back(const T & value)
  {
    if (is_empty())
    {
      push_front(value);
    }
    else
    {
      Node< T > * newNode = new Node< T >(value);
      Node< T > * last = head->prev;
      newNode->next = head;
      newNode->prev = last;
      last->next = newNode;
      head->prev = newNode;
      ++size;
    }
  }

  template < class T >
  void BiList< T >::push_back(T && value)
  {
    if (is_empty())
    {
      push_front(std::move(value));
    }
    else
    {
      Node< T > * newNode = new Node< T >(std::move(value));
      Node< T > * last = head->prev;
      newNode->next = head;
      newNode->prev = last;
      last->next = newNode;
      head->prev = newNode;
      ++size;
    }
  }

  template < class T >
  LIter< T > BiList< T >::insert(LIter< T > pos, const T & value)
  {
    if (is_empty())
    {
      push_front(value);
      return begin();
    }
    if (pos.cur == nullptr)
    {
      push_front(value);
      return begin();
    }
    Node< T > * newNode = new Node< T >(value, pos.cur, pos.cur->next);
    pos.cur->next->prev = newNode;
    pos.cur->next = newNode;
    if (pos.cur == head->prev)
    {
      head->prev = newNode;
    }
    ++size;
    return LIter< T >(newNode, head);
  }

  template < class T >
  LIter< T > BiList< T >::insert(LIter< T > pos, T && value)
  {
    if (is_empty())
    {
      push_front(std::move(value));
      return begin();
    }
    if (pos.cur == nullptr)
    {
      push_front(std::move(value));
      return begin();
    }
    Node< T > * newNode = new Node< T >(std::move(value), pos.cur, pos.cur->next);
    pos.cur->next->prev = newNode;
    pos.cur->next = newNode;
    if (pos.cur == head->prev)
    {
      head->prev = newNode;
    }
    ++size;
    return LIter< T >(newNode, head);
  }

  template < class T >
  void BiList< T >::pop_front()
  {
    if (is_empty())
    {
      throw std::runtime_error("Empty list");
    }
    else if (getsize() == 1)
    {
      delete head;
      head = nullptr;
      size = 0;
    }
    else
    {
      Node< T > * first = head;
      head->prev->next = head->next;
      head->next->prev = head->prev;
      head = head->next;
      delete first;
      --size;
    }
  }

  template < class T >
  void BiList< T >::pop_back()
  {
    if (is_empty())
    {
      throw std::runtime_error("Empty list");
    }
    else if (getsize() == 1)
    {
      delete head;
      head = nullptr;
      size = 0;
    }
    else
    {
      Node< T > * last = head->prev;
      last->prev->next = head;
      head->prev = last->prev;
      delete last;
      --size;
    }
  }

  template < class T >
  LIter< T > BiList< T >::erase(LIter< T > pos)
  {
    if (is_empty())
    {
      throw std::runtime_error("Empty list");
    }
    if (pos.cur == nullptr)
    {
      throw std::runtime_error("Cannot erase end iterator");
    }
    if (getsize() == 1)
    {
      delete pos.cur;
      head = nullptr;
      size = 0;
      return end();
    }
    Node< T > * toDelete = pos.cur;
    Node< T > * nextNode = toDelete->next;
    if (toDelete == head)
    {
      pop_front();
      return begin();
    }
    else if (toDelete == head->prev)
    {
      pop_back();
      return end();
    }
    else
    {
      toDelete->prev->next = toDelete->next;
      toDelete->next->prev = toDelete->prev;
      delete toDelete;
      --size;
      return LIter< T >(nextNode, head);
    }
  }

  template < class T >
  void BiList< T >::clear()
  {
    while (!is_empty())
    {
      pop_front();
    }
  }

  template < class T >
  void BiList< T >::swap(BiList & other) noexcept
  {
    Node< T > * tmp_head = head;
    size_t tmp_size = size;
    head = other.head;
    size = other.size;
    other.head = tmp_head;
    other.size = tmp_size;
  }
}

#endif
