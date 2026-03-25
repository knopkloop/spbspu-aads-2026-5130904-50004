#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "../common/BiList.hpp"
#include <stdexcept>

namespace haliullin
{
  template < class T >
  class Queue
  {
  public:
    void push(const T & rhs);
    T drop();
    T & front();
    const T & front() const;
    bool is_empty() const noexcept;
    size_t get_size() const noexcept;
    void clear();

  private:
    BiList< T > data_;
  };
}

template < class T >
void haliullin::Queue< T >::push(const T & rhs)
{
  data_.push_back(rhs);
}

template < class T >
T haliullin::Queue< T >::drop()
{
  if (data_.is_empty())
  {
    throw std::runtime_error("Queue is empty");
  }
  T val = data_.front();
  data_.pop_front();
  return val;
}

template < class T >
T & haliullin::Queue< T >::front()
{
  if (data_.is_empty())
  {
    throw std::runtime_error("Queue is empty");
  }
  return data_.front();
}

template < class T >
const T & haliullin::Queue< T >::front() const
{
  if (data_.is_empty())
  {
    throw std::runtime_error("Queue is empty");
  }
  return data_.front();
}

template < class T >
bool haliullin::Queue< T >::is_empty() const noexcept
{
  return data_.is_empty();
}

template < class T >
size_t haliullin::Queue< T >::get_size() const noexcept
{
  return data_.get_size();
}

template < class T >
void haliullin::Queue< T >::clear()
{
  data_.clear();
}

#endif
