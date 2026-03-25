#ifndef BILIST_HPP
#define BILIST_HPP

#include "LCIter.hpp"
#include "LIter.hpp"
#include <iostream>
#include <utility>

namespace haliullin
{
  template < class T >
  class BiList
  {
  public:
    BiList();
    BiList(const BiList & other);
    BiList(BiList && other);
    ~BiList();

    BiList & operator=(const BiList & other);
    BiList & operator=(BiList && other) noexcept;

    bool is_empty() const noexcept;
    size_t get_size() const noexcept;

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

  private:
    Node< T > * head_;
    size_t size_;
  };
}

template < class T >
haliullin::BiList< T >::BiList():
  head_(nullptr),
  size_(0)
{}

template < class T >
haliullin::BiList< T >::BiList(const BiList & other):
  head_(nullptr),
  size_(0)
{
  if (other.is_empty())
  {
    return;
  }
  Node< T > * cur = other.head_;
  Node< T > * first = new Node< T >(cur->val_);
  head_ = first;
  size_ = 1;
  cur = cur->next_;
  Node< T > * prev = first;
  while (cur != other.head_)
  {
    Node< T > * newNode = new Node< T >(cur->val_);
    prev->next_ = newNode;
    newNode->prev_ = prev;
    prev = newNode;
    cur = cur->next_;
    ++size_;
  }
  prev->next_ = head_;
  head_->prev_ = prev;
}

template < class T >
haliullin::BiList< T >::BiList(BiList && other):
  head_(other.head_),
  size_(other.size_)
{
  other.head_ = nullptr;
  other.size_ = 0;
}

template < class T >
haliullin::BiList< T >::~BiList()
{
  clear();
}

template < class T >
haliullin::BiList< T > & haliullin::BiList< T >::operator=(const BiList & other)
{
  if (this != &other)
  {
    BiList tmp(other);
    swap(tmp);
  }
  return *this;
}

template < class T >
haliullin::BiList< T > & haliullin::BiList< T >::operator=(BiList && other) noexcept
{
  if (this != &other)
  {
    clear();
    head_ = other.head_;
    size_ = other.size_;
    other.head_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template < class T >
bool haliullin::BiList< T >::is_empty() const noexcept
{
  return !size_;
}

template < class T >
size_t haliullin::BiList< T >::get_size() const noexcept
{
  return size_;
}

template < class T >
T & haliullin::BiList< T >::front()
{
  if (is_empty())
  {
    throw std::runtime_error("Empty list");
  }
  return head_->val_;
}

template < class T >
const T & haliullin::BiList< T >::front() const
{
  if (is_empty())
  {
    throw std::runtime_error("Empty list");
  }
  return head_->val_;
}

template < class T >
T & haliullin::BiList< T >::back()
{
  if (is_empty())
  {
    throw std::runtime_error("Empty list");
  }
  return head_->prev_->val_;
}

template < class T >
const T & haliullin::BiList< T >::back() const
{
  if (is_empty())
  {
    throw std::runtime_error("Empty list");
  }
  return head_->prev_->val_;
}

template < class T >
haliullin::LIter< T > haliullin::BiList< T >::begin()
{
  return LIter< T >(head_, head_);
}

template < class T >
haliullin::LCIter< T > haliullin::BiList< T >::cbegin() const
{
  return LCIter< T >(head_, head_);
}

template < class T >
haliullin::LIter< T > haliullin::BiList< T >::end()
{
  return LIter< T >(nullptr, head_);
}

template < class T >
haliullin::LCIter< T > haliullin::BiList< T >::cend() const
{
  return LCIter< T >(nullptr, head_);
}

template < class T >
void haliullin::BiList< T >::push_front(const T & value)
{
  Node< T > * newNode = new Node< T >(value);
  if (is_empty())
  {
    head_ = newNode;
    head_->next_ = head_;
    head_->prev_ = head_;
  }
  else
  {
    newNode->next_ = head_;
    newNode->prev_ = head_->prev_;
    head_->prev_->next_ = newNode;
    head_->prev_ = newNode;
    head_ = newNode;
  }
  ++size_;
}

template < class T >
void haliullin::BiList< T >::push_front(T && value)
{
  Node< T > * newNode = new Node< T >(std::move(value));
  if (is_empty())
  {
    head_ = newNode;
    head_->next_ = head_;
    head_->prev_ = head_;
  }
  else
  {
    newNode->next_ = head_;
    newNode->prev_ = head_->prev_;
    head_->prev_->next_ = newNode;
    head_->prev_ = newNode;
    head_ = newNode;
  }
  ++size_;
}

template < class T >
void haliullin::BiList< T >::push_back(const T & value)
{
  if (is_empty())
  {
    push_front(value);
  }
  else
  {
    Node< T > * newNode = new Node< T >(value);
    Node< T > * last = head_->prev_;
    newNode->next_ = head_;
    newNode->prev_ = last;
    last->next_ = newNode;
    head_->prev_ = newNode;
    ++size_;
  }
}

template < class T >
void haliullin::BiList< T >::push_back(T && value)
{
  if (is_empty())
  {
    push_front(std::move(value));
  }
  else
  {
    Node< T > * newNode = new Node< T >(std::move(value));
    Node< T > * last = head_->prev_;
    newNode->next_ = head_;
    newNode->prev_ = last;
    last->next_ = newNode;
    head_->prev_ = newNode;
    ++size_;
  }
}

template < class T >
haliullin::LIter< T > haliullin::BiList< T >::insert(LIter< T > pos, const T & value)
{
  if (is_empty())
  {
    push_front(value);
    return begin();
  }
  if (pos.cur_ == nullptr)
  {
    push_front(value);
    return begin();
  }
  Node< T > * newNode = new Node< T >(value, pos.cur_, pos.cur_->next_);
  pos.cur_->next_->prev_ = newNode;
  pos.cur_->next_ = newNode;
  if (pos.cur_ == head_->prev_)
  {
    head_->prev_ = newNode;
  }
  ++size_;
  return LIter< T >(newNode, head_);
}

template < class T >
haliullin::LIter< T > haliullin::BiList< T >::insert(LIter< T > pos, T && value)
{
  if (is_empty())
  {
    push_front(std::move(value));
    return begin();
  }
  if (pos.cur_ == nullptr)
  {
    push_front(std::move(value));
    return begin();
  }
  Node< T > * newNode = new Node< T >(std::move(value), pos.cur_, pos.cur_->next_);
  pos.cur_->next_->prev_ = newNode;
  pos.cur_->next_ = newNode;
  if (pos.cur_ == head_->prev_)
  {
    head_->prev_ = newNode;
  }
  ++size_;
  return LIter< T >(newNode, head_);
}

template < class T >
void haliullin::BiList< T >::pop_front()
{
  if (is_empty())
  {
    throw std::runtime_error("Empty list");
  }
  else if (get_size() == 1)
  {
    delete head_;
    head_ = nullptr;
    size_ = 0;
  }
  else
  {
    Node< T > * first = head_;
    head_->prev_->next_ = head_->next_;
    head_->next_->prev_ = head_->prev_;
    head_ = head_->next_;
    delete first;
    --size_;
  }
}

template < class T >
void haliullin::BiList< T >::pop_back()
{
  if (is_empty())
  {
    throw std::runtime_error("Empty list");
  }
  else if (get_size() == 1)
  {
    delete head_;
    head_ = nullptr;
    size_ = 0;
  }
  else
  {
    Node< T > * last = head_->prev_;
    last->prev_->next_ = head_;
    head_->prev_ = last->prev_;
    delete last;
    --size_;
  }
}

template < class T >
haliullin::LIter< T > haliullin::BiList< T >::erase(LIter< T > pos)
{
  if (is_empty())
  {
    throw std::runtime_error("Empty list");
  }
  if (pos.cur_ == nullptr)
  {
    throw std::runtime_error("Cannot erase end iterator");
  }
  if (get_size() == 1)
  {
    delete pos.cur_;
    head_ = nullptr;
    size_ = 0;
    return end();
  }

  Node< T > * toDelete = pos.cur_;
  Node< T > * nextNode = toDelete->next_;
  if (toDelete == head_)
  {
    pop_front();
    return begin();
  }
  else if (toDelete == head_->prev_)
  {
    pop_back();
    return end();
  }
  else
  {
    toDelete->prev_->next_ = toDelete->next_;
    toDelete->next_->prev_ = toDelete->prev_;
    delete toDelete;
    --size_;
    return LIter< T >(nextNode, head_);
  }
}

template < class T >
void haliullin::BiList< T >::clear()
{
  while (!is_empty())
  {
    pop_front();
  }
}

template < class T >
void haliullin::BiList< T >::swap(BiList & other) noexcept
{
  Node< T > * tmp_head = head_;
  size_t tmp_size = size_;
  head_ = other.head;
  size_ = other.size;
  other.head = tmp_head;
  other.size = tmp_size;
}

#endif
