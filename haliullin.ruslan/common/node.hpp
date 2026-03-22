#ifndef NODE_HPP
#define NODE_HPP

#include <utility>

namespace haliullin
{
  template < class T > class BiList;
  template < class T > class LIter;
  template < class T > class LCIter;

  template< class T >
  struct Node
  {
    T val;
    Node * prev;
    Node * next;

    Node(const T & value, Node * p = nullptr, Node * n = nullptr):
      val(value),
      prev(p),
      next(n)
    {}

    Node(T && value, Node * p = nullptr, Node * n = nullptr):
      val(std::move(value)),
      prev(p),
      next(n)
    {}
  };
}

#endif
