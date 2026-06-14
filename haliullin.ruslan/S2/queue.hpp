#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <stdexcept>
#include <BiList.hpp>

namespace haliullin
{
  template< class T >
  class Queue
  {
  public:
    bool is_empty() const noexcept;
    size_t get_size() const noexcept;
    void push(const T& rhs);
    T& front();
    const T& front() const;
    void pop();
    void clear();

    template< class... Args >
    T& emplace(Args&&... args);

  private:
    BiList< T > data_;
  };
}

template< class T >
bool haliullin::Queue< T >::is_empty() const noexcept
{
  return data_.is_empty();
}

template< class T >
size_t haliullin::Queue< T >::get_size() const noexcept
{
  return data_.get_size();
}

template< class T >
void haliullin::Queue< T >::push(const T& rhs)
{
  data_.emplace_back(rhs);
}

template< class T >
T& haliullin::Queue< T >::front()
{
  if (data_.is_empty())
  {
    throw std::runtime_error("Queue is empty");
  }
  return data_.front();
}

template< class T >
const T& haliullin::Queue< T >::front() const
{
  if (data_.is_empty())
  {
    throw std::runtime_error("Queue is empty");
  }
  return data_.front();
}

template< class T >
void haliullin::Queue< T >::pop()
{
  if (data_.is_empty())
  {
    throw std::runtime_error("Queue is empty");
  }
  data_.pop_front();
}

template< class T >
void haliullin::Queue< T >::clear()
{
  data_.clear();
}

template< class T >
template< class... Args >
T& haliullin::Queue< T >::emplace(Args&&... args)
{
  return data_.emplace_back(std::forward< Args >(args)...);
}

#endif
