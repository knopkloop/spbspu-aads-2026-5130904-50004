#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "../common/BiList.hpp"
#include <stdexcept>

namespace haliullin
{
  template < class T >
  class Queue
  {
  private:
    BiList< T > data;

  public:
    void push(const T & rhs);
    T drop();
    T & front();
    const T & front() const;
    bool is_empty() const noexcept;
    size_t size() const noexcept;
    void clear();
  };

  template < class T >
  void Queue< T >::push(const T & rhs)
  {
    data.push_back(rhs);
  }

  template < class T >
  T Queue< T >::drop()
  {
    if (data.is_empty())
    {
      throw std::runtime_error("Queue is empty");
    }
    T val = data.front();
    data.pop_front();
    return val;
  }

  template < class T >
  T & Queue< T >::front()
  {
    if (data.is_empty())
    {
      throw std::runtime_error("Queue is empty");
    }
    return data.front();
  }

  template < class T >
  const T & Queue< T >::front() const
  {
    if (data.is_empty())
    {
      throw std::runtime_error("Queue is empty");
    }
    return data.front();
  }

  template < class T >
  bool Queue< T >::is_empty() const noexcept
  {
    return data.is_empty();
  }

  template < class T >
  size_t Queue< T >::size() const noexcept
  {
    return data.getsize();
  }

  template < class T >
  void Queue< T >::clear()
  {
    data.clear();
  }
}

#endif
