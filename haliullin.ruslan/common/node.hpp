#ifndef NODE_HPP
#define NODE_HPP

#include <utility>

namespace haliullin
{
  template < class T > class BiList;
  template < class T > class LIter;
  template < class T > class LCIter;

  template< class T >
  class Node
  {
  public:
    explicit Node(const T & value, Node * prev = nullptr, Node * next = nullptr):
      val_(value),
      prev_(prev),
      next_(next)
    {}

    explicit Node(T && value, Node * prev = nullptr, Node * next = nullptr):
      val_(std::move(value)),
      prev_(prev),
      next_(next)
    {}

    T val_;
    Node * prev_;
    Node * next_;
  };
}

#endif
