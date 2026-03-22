#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>
#include "../common/BiList.hpp"

namespace haliullin
{
  template < class T >
  class Stack
  {
  private:
    BiList< T > data;

  public:
    void push(const T & rhs);
    T drop();
    T & top();
    const T & top() const;
    bool is_empty() const;
    size_t size() const;
    void clear();
  };
}

#endif
