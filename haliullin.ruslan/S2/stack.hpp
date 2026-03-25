#ifndef STACK_HPP
#define STACK_HPP

#include "../common/BiList.hpp"
#include <stdexcept>

namespace haliullin
{
  template < class T >
  class Stack
  {
  public:
    void push(const T & rhs);
    T drop();
    T & top();
    const T & top() const;
    bool is_empty() const noexcept;
    size_t get_size() const noexcept;
    void clear();

  private:
    BiList< T > data_;
  };
}

template < class T >
void haliullin::Stack< T >::push(const T & rhs)
{
  data_.push_back(rhs);
}

template < class T >
T haliullin::Stack< T >::drop()
{
  if (data_.is_empty())
  {
    throw std::runtime_error("Stack is empty");
  }
  T val = data_.back();
  data_.pop_back();
  return val;
}

template < class T >
T & haliullin::Stack< T >::top()
{
  if (data_.is_empty())
  {
    throw std::runtime_error("Stack is empty");
  }
  return data_.back();
}

template < class T >
const T & haliullin::Stack< T >::top() const
{
  if (data_.is_empty())
  {
    throw std::runtime_error("Stack is empty");
  }
  return data_.back();
}

template < class T >
bool haliullin::Stack< T >::is_empty() const noexcept
{
  return data_.is_empty();
}

template < class T >
size_t haliullin::Stack< T >::get_size() const noexcept
{
  return data_.get_size();
}

template < class T >
void haliullin::Stack< T >::clear()
{
  data_.clear();
}

#endif
