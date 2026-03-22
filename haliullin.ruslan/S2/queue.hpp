#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "../common/BiList.hpp"

namespace haliullin
{
  template < class T >
  class Queue
  {
  private:
    BiList< T > data;

  public:
    void push(const T& rhs);
    T drop();
    T & front();
    const T & front() const;
    bool isEmpty() const;
    size_t size() const;
    void clear();
  };
}

#endif
