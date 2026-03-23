#ifndef STACK_HPP
#define STACK_HPP

#include "../common/BiList.hpp"
#include <stdexcept>

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

  template < class T >
  void Stack< T >::push(const T & rhs)
  {
    data.push_back(rhs);
  }

  template < class T >
  T Stack< T >::drop()
  {
    if (data.is_empty())
    {
      throw std::runtime_error("Stack is empty");
    }
    T val = data.back();
    data.pop_back();
    return val;
  }

  template < class T >
  T & Stack< T >::top()
  {
    if (data.is_empty())
    {
      throw std::runtime_error("Stack is empty");
    }
    return data.back();
  }

  template < class T >
  const T & Stack< T >::top() const
  {
    if (data.is_empty())
    {
      throw std::runtime_error("Stack is empty");
    }
    return data.back();
  }

  template < class T >
  bool Stack< T >::is_empty() const noexcept
  {
    return data.is_empty();
  }

  template < class T >
  size_t Stack< T >::size() const noexcept
  {
    return data.getsize();
  }

  template < class T >
  void Stack< T >::clear()
  {
    data.clear();
  }
}

#endif
