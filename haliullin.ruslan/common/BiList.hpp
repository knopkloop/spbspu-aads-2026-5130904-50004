#ifndef BILIST_HPP
#define BILIST_HPP

#include <iostream>
#include <utility>
#include <stdexcept>
#include <functional>
#include "BiList-iterators.hpp"

namespace haliullin
{
  template< class T >
  class BiList
  {
  public:
    using node = detail::Node< T >;
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
    LIter< T > emplace(LCIter< T > pos, Args&&... args);

    void splice(LCIter< T > pos, BiList< T >& other) noexcept;
    void splice(LCIter< T > pos, BiList< T >& other, LIter< T > it) noexcept;
    void splice(LCIter< T > pos, BiList< T >& other, LIter< T > first, LIter< T > last) noexcept;

    template< class Compare >
    void sort(Compare comp);
    void sort();

    template< class Compare >
    void merge(BiList< T >& other, Compare comp);
    void merge(BiList< T >& other);

    template< class Predicate >
    LIter< T > partition(Predicate pred);

    LIter< T > begin() noexcept;
    LCIter< T > begin() const noexcept;
    LCIter< T > cbegin() const noexcept;
    LIter< T > end() noexcept;
    LCIter< T > end() const noexcept;
    LCIter< T > cend() const noexcept;

  private:
    node* head_;
    size_t size_;
    void transfer(node* pos, BiList< T >& other, node* first, node* last, size_t count) noexcept;
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
  node* cur = other.head_;
  node* first = new node(nullptr, nullptr, cur->val_);
  head_ = first;
  size_ = 1;
  cur = cur->next_;
  node* prev = first;
  while (cur != other.head_)
  {
    node* newNode = new node(nullptr, nullptr, cur->val_);
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
    node* first = head_;
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
    node* last = head_->prev_;
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

  node* toDelete = pos.cur_;
  node* nextNode = toDelete->next_;
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
  node* newNode = new node(nullptr, nullptr, std::forward< Args >(args)...);

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

  node* newNode = new node(nullptr, nullptr, std::forward< Args >(args)...);
  node* last = head_->prev_;
  newNode->next_ = head_;
  newNode->prev_ = last;
  last->next_ = newNode;
  head_->prev_ = newNode;
  ++size_;
}

template< class T >
template< class... Args >
haliullin::LIter< T > haliullin::BiList< T >::emplace(LCIter< T > pos, Args&&... args)
{
  if (is_empty())
  {
    emplace_front(std::forward< Args >(args)...);
    return begin();
  }

  node* pos_node = const_cast< node* >(pos.cur_);
  if (pos_node == head_)
  {
    emplace_front(std::forward< Args >(args)...);
    return begin();
  }
  if (pos_node == nullptr)
  {
    emplace_back(std::forward< Args >(args)...);
    return LIter< T >(head_->prev_, head_);
  }

  node* prevNode = pos_node->prev_;
  node* newNode = new node(prevNode, pos_node, std::forward< Args >(args)...);

  prevNode->next_ = newNode;
  pos_node->prev_ = newNode;

  ++size_;
  return LIter< T >(newNode, head_);
}

template< class T >
void haliullin::BiList< T >::transfer(node* pos, BiList< T >& other, node* first, node* last, size_t count) noexcept
{
  if (count == 0)
  {
    return;
  }

  node* before_first = first->prev_;
  node* after_last = last->next_;

  before_first->next_ = after_last;
  after_last->prev_ = before_first;

  if (other.head_ == first)
  {
    if (count == other.size_)
    {
      other.head_ = nullptr;
    }
    else
    {
      other.head_ = after_last;
    }
  }

  if (is_empty())
  {
    head_ = first;
    first->prev_ = last;
    last->next_ = first;
  }
  else
  {
    node* before_pos = (pos == nullptr) ? head_->prev_ : pos->prev_;
    node* after_pos = (pos == nullptr) ? head_ : pos;

    before_pos->next_ = first;
    first->prev_ = before_pos;
    last->next_ = after_pos;
    after_pos->prev_ = last;

    if (pos == head_)
    {
      head_ = first;
    }
  }

  size_ += count;
  other.size_ -= count;
}

template< class T >
void haliullin::BiList< T >::splice(LCIter< T > pos, BiList< T >& other) noexcept
{
  if (std::addressof(other) == this || other.is_empty())
  {
    return;
  }
  node* pos_node = const_cast< node* >(pos.cur_);
  transfer(pos_node, other, other.head_, other.head_->prev_, other.size_);
}

template< class T >
void haliullin::BiList< T >::splice(LCIter< T > pos, BiList< T >& other, LIter< T > it) noexcept
{
  if (it.cur_ == nullptr)
  {
    return;
  }
  node* pos_node = const_cast< node* >(pos.cur_);
  transfer(pos_node, other, it.cur_, it.cur_, 1);
}

template< class T >
void haliullin::BiList< T >::splice(LCIter< T > pos, BiList< T >& other, LIter< T > first, LIter< T > last) noexcept
{
  if (first == last || first.cur_ == nullptr)
  {
    return;
  }
  if (first == other.begin() && last == other.end())
  {
    splice(pos, other);
    return;
  }
  size_t count = 0;
  for (auto it = first; it != last; ++it)
  {
    ++count;
  }
  node* last_node = (last.cur_ == nullptr) ? other.head_->prev_ : last.cur_->prev_;
  node* pos_node = const_cast< node* >(pos.cur_);
  transfer(pos_node, other, first.cur_, last_node, count);
}

template< class T >
template< class Compare >
void haliullin::BiList< T >::sort(Compare comp)
{
  if (size_ < 2)
  {
    return;
  }

  BiList< T > carry;
  BiList< T > counter[64];
  size_t fill = 0;

  while (!is_empty())
  {
    carry.splice(carry.begin(), *this, begin());
    size_t i = 0;
    while (i < fill && !counter[i].is_empty())
    {
      counter[i].merge(carry, comp);
      carry.swap(counter[i++]);
    }
    carry.swap(counter[i]);
    if (i == fill)
    {
      ++fill;
    }
  }

  for (size_t i = 1; i < fill; ++i)
  {
    counter[i].merge(counter[i - 1], comp);
  }
  swap(counter[fill - 1]);
}

template< class T >
void haliullin::BiList< T >::sort()
{
  sort(std::less< T >());
}

template< class T >
template< class Compare >
void haliullin::BiList< T >::merge(BiList< T >& other, Compare comp)
{
  if (std::addressof(other) == this)
  {
    return;
  }

  auto it1 = begin();
  while (!is_empty() && !other.is_empty())
  {
    if (comp(other.front(), *it1))
    {
      splice(it1, other, other.begin());
    }
    else
    {
      ++it1;
      if (it1 == end())
      {
        break;
      }
    }
  }

  if (!other.is_empty())
  {
    splice(end(), other);
  }
}

template< class T >
void haliullin::BiList< T >::merge(BiList< T >& other)
{
  merge(other, std::less< T >());
}

template< class T >
template< class Predicate >
haliullin::LIter< T > haliullin::BiList< T >::partition(Predicate pred)
{
  BiList< T > false_list;
  auto it = begin();

  while (it != end())
  {
    if (pred(*it))
    {
      ++it;
    }
    else
    {
      auto next = it;
      ++next;
      false_list.splice(false_list.end(), *this, it);
      it = next;
    }
  }

  LIter< T > partition_point = end();
  if (!false_list.is_empty())
  {
    node* first_false = false_list.head_;
    splice(end(), false_list);
    partition_point = LIter< T >(first_false, head_);
  }

  return partition_point;
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
