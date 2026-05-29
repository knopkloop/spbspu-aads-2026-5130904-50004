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
    template< class... Args >
    explicit Node(Node< T >* prev, Node< T >* next, Args&&... args):
      prev_(prev),
      next_(next),
      val_(std::forward< Args >(args)...)
    {}

    Node< T >* prev_;
    Node< T >* next_;
    T val_;
  };
}

#endif
