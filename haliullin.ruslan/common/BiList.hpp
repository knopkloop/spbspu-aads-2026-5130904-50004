#ifndef BILIST_HPP
#define BILIST_HPP

#include <iostream>
#include <utility>
#include <stdexcept>
#include "BiList-iterators.hpp"

namespace haliullin
{
  template< class T >
  class BiList
  {
  public:
    BiList();
    BiList(const BiList< T >& other);
    BiList(BiList< T >&& other) noexcept;
    ~BiList();

    BiList< T >& operator=(const BiList< T >& other);
    BiList< T >& operator=(BiList< T >&& other) noexcept;
    void swap(BiList< T >& other) noexcept;

    bool is_empty() const noexcept;
    size_t get_size() const noexcept;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    void pop_front();
    void pop_back();
    LIter< T > erase(LIter< T > pos);
    void clear();

    template< class... Args >
    void emplace_front(Args&&... args);

    template< class... Args >
    void emplace_back(Args&&... args);

    template< class... Args >
    LIter< T > emplace(LIter< T > pos, Args&&... args);

    LIter< T > begin() noexcept;
    LCIter< T > begin() const noexcept;
    LCIter< T > cbegin() const noexcept;
    LIter< T > end() noexcept;
    LCIter< T > end() const noexcept;
    LCIter< T > cend() const noexcept;

  private:
    detail::Node< T >* head_;
    size_t size_;
  };
}

template< class T >
haliullin::BiList< T >::BiList():
  head_(nullptr),
  size_(0)
{}

template< class T >
haliullin::BiList< T >::BiList(const BiList< T >& other):
  head_(nullptr),
  size_(0)
{
  if (other.is_empty())
  {
    return;
  }
  detail::Node< T >* cur = other.head_;
  detail::Node< T >* first = new detail::Node< T >(nullptr, nullptr, cur->val_);
  head_ = first;
  size_ = 1;
  cur = cur->next_;
  detail::Node< T >* prev = first;
  while (cur != other.head_)
  {
    detail::Node< T >* newNode = new detail::Node< T >(nullptr, nullptr, cur->val_);
    prev->next_ = newNode;
    newNode->prev_ = prev;
    prev = newNode;
    cur = cur->next_;
    ++size_;
  }
  prev->next_ = head_;
  head_->prev_ = prev;
}

template< class T >
haliullin::BiList< T >::BiList(BiList< T >&& other) noexcept:
  BiList()
{
  swap(other);
}

template< class T >
haliullin::BiList< T >::~BiList()
{
  clear();
}

template< class T >
haliullin::BiList< T >& haliullin::BiList< T >::operator=(const BiList< T >& other)
{
  if (this != std::addressof(other))
  {
    BiList< T > tmp(other);
    swap(tmp);
  }
  return *this;
}

template< class T >
haliullin::BiList< T >& haliullin::BiList< T >::operator=(BiList< T >&& other) noexcept
{
  if (this != std::addressof(other))
  {
    BiList< T > tmp(std::move(other));
    swap(tmp);
  }
  return *this;
}

template< class T >
void haliullin::BiList< T >::swap(BiList< T >& other) noexcept
{
  std::swap(head_, other.head_);
  std::swap(size_, other.size_);
}

template< class T >
bool haliullin::BiList< T >::is_empty() const noexcept
{
  return !size_;
}

template< class T >
size_t haliullin::BiList< T >::get_size() const noexcept
{
  return size_;
}

template< class T >
T& haliullin::BiList< T >::front()
{
  if (is_empty())
  {
    throw std::runtime_error("Empty list");
  }
  return head_->val_;
}

template< class T >
const T& haliullin::BiList< T >::front() const
{
  if (is_empty())
  {
    throw std::runtime_error("Empty list");
  }
  return head_->val_;
}

template< class T >
T& haliullin::BiList< T >::back()
{
  if (is_empty())
  {
    throw std::runtime_error("Empty list");
  }
  return head_->prev_->val_;
}

template< class T >
const T& haliullin::BiList< T >::back() const
{
  if (is_empty())
  {
    throw std::runtime_error("Empty list");
  }
  return head_->prev_->val_;
}

template< class T >
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
    detail::Node< T >* first = head_;
    head_->prev_->next_ = head_->next_;
    head_->next_->prev_ = head_->prev_;
    head_ = head_->next_;
    delete first;
    --size_;
  }
}

template< class T >
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
    detail::Node< T >* last = head_->prev_;
    last->prev_->next_ = head_;
    head_->prev_ = last->prev_;
    delete last;
    --size_;
  }
}

template< class T >
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

  detail::Node< T >* toDelete = pos.cur_;
  detail::Node< T >* nextNode = toDelete->next_;
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

template< class T >
void haliullin::BiList< T >::clear()
{
  while (!is_empty())
  {
    pop_front();
  }
}

template< class T >
template< class... Args >
void haliullin::BiList< T >::emplace_front(Args&&... args)
{
  detail::Node< T >* newNode = new detail::Node< T >(nullptr, nullptr, std::forward< Args >(args)...);

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

template< class T >
template< class... Args >
void haliullin::BiList< T >::emplace_back(Args&&... args)
{
  if (is_empty())
  {
    emplace_front(std::forward< Args >(args)...);
    return;
  }

  detail::Node< T >* newNode = new detail::Node< T >(nullptr, nullptr, std::forward< Args >(args)...);
  detail::Node< T >* last = head_->prev_;
  newNode->next_ = head_;
  newNode->prev_ = last;
  last->next_ = newNode;
  head_->prev_ = newNode;
  ++size_;
}

template< class T >
template< class... Args >
haliullin::LIter< T > haliullin::BiList< T >::emplace(LIter< T > pos, Args&&... args)
{
  if (is_empty())
  {
    emplace_front(std::forward< Args >(args)...);
    return begin();
  }

  if (pos.cur_ == head_)
  {
    emplace_front(std::forward< Args >(args)...);
    return begin();
  }

  if (pos.cur_ == nullptr)
  {
    emplace_back(std::forward< Args >(args)...);
    return LIter< T >(head_->prev_, head_);
  }

  detail::Node< T >* prevNode = pos.cur_->prev_;
  detail::Node< T >* newNode = new detail::Node< T >(prevNode, pos.cur_, std::forward< Args >(args)...);

  prevNode->next_ = newNode;
  pos.cur_->prev_ = newNode;

  ++size_;
  return LIter< T >(newNode, head_);
}

template< class T >
haliullin::LIter< T > haliullin::BiList< T >::begin() noexcept
{
  return LIter< T >(head_, head_);
}

template< class T >
haliullin::LCIter< T > haliullin::BiList< T >::begin() const noexcept
{
  return LCIter< T >(head_, head_);
}

template< class T >
haliullin::LCIter< T > haliullin::BiList< T >::cbegin() const noexcept
{
  return begin();
}

template< class T >
haliullin::LIter< T > haliullin::BiList< T >::end() noexcept
{
  return LIter< T >(nullptr, head_);
}

template< class T >
haliullin::LCIter< T > haliullin::BiList< T >::end() const noexcept
{
  return LCIter< T >(nullptr, head_);
}

template< class T >
haliullin::LCIter< T > haliullin::BiList< T >::cend() const noexcept
{
  return end();
}

#endif
