#ifndef NODE_HPP
#define NODE_HPP

#include <utility>

namespace haliullin
{
  template< class T >
  class BiList;

  template< class T >
  class LIter;

  template< class T >
  class LCIter;

  template< class T >
  class Node
  {
  public:
    template< class U >
    explicit Node(U&& value, Node< T >* prev = nullptr, Node< T >* next = nullptr):
      val_(std::forward< U >(value)),
      prev_(prev),
      next_(next)
    {}

    T val_;
    Node< T >* prev_;
    Node< T >* next_;
  };
}

#endif
