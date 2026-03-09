#ifndef BILIST_HPP
#define BILIST_HPP

namespace haliullin
{
  template< class T > class BiList;

  template< class T >
  struct Node
  {
    T val;
    Node *prev;
    Node *next;

    explicit Node(const T & value) :
      val(value),
      prev(nullptr),
      next(nullptr)
    {}

    explicit Node(T && value) :
      val(std::move(value)),
      prev(nullptr),
      next(nullptr)
    {}
  };

  template< class T >
  class LIter
  {
    friend class BiList< T >;
    Node< T > * cur;
    explicit LIter(Node<T> * node) noexcept;

  public:
    LIter() noexcept;
    LIter(const LIter & other) noexcept;
    LIter(LIter && other) noexcept;
    ~LIter();

    LIter & operator=(const LIter & other) noexcept;
    LIter & operator=(LIter && other) noexcept;

    bool operator==(const LIter & other) const noexcept;
    bool operator!=(const LIter & other) const noexcept;

    T & operator*() const noexcept;
    T * operator->() const noexcept;

    LIter & operator++() noexcept;
    LIter operator++(int) noexcept;
    LIter & operator--() noexcept;
    LIter operator--(int) noexcept;

    operator LCIter<T>() const noexcept;
  };
}













#endif
