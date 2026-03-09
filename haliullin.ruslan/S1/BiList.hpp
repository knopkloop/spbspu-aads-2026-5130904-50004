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

//----------LIter----------
  template< class T >
  class LIter
  {
    friend class BiList< T >;
    Node< T > * cur;
    explicit LIter(Node<T> * node) noexcept :
      cur(node)
    {}

  public:
    LIter() noexcept :
      cur(nullptr)
    {}
    LIter(const LIter & other) noexcept = default;
    LIter(LIter && other) noexcept = default;
    ~LIter() = default;

    LIter & operator=(const LIter & other) noexcept = default;
    LIter & operator=(LIter && other) noexcept = default;

    bool operator==(const LIter & other) const noexcept;
    bool operator!=(const LIter & other) const noexcept;

    T & operator*() const noexcept;
    T * operator->() const noexcept;

    LIter & operator++() noexcept;
    LIter operator++(int) noexcept;
    LIter & operator--() noexcept;
    LIter operator--(int) noexcept;
  };

//----------LCIter----------
  template< class T >
  class LCIter
  {
    friend class BiList< T >;
    const Node< T > * cur;
    explicit LCIter(const Node<T> * node) noexcept :
      cur(node)
    {}

  public:
    LCIter() noexcept :
      cur(nullptr)
    {}

    LCIter(const LIter<T> & other) noexcept;
    LCIter(const LCIter & other) noexcept;
    LCIter(LCIter && other) noexcept;
    ~LCIter();

    LCIter & operator=(const LCIter & other) noexcept;
    LCIter & operator=(LCIter && other) noexcept;

    bool operator==(const LCIter & other) const noexcept;
    bool operator!=(const LCIter & other) const noexcept;
    bool operator==(const LIter<T> & other) const noexcept;
    bool operator!=(const LIter<T> & other) const noexcept;

    const T & operator*() const noexcept;
    const T * operator->() const noexcept;

    LCIter & operator++() noexcept;
    LCIter operator++(int) noexcept;
    LCIter & operator--() noexcept;
    LCIter operator--(int) noexcept;
  };

//----------BiList----------
  template< class T >
  class BiList
  {
  private:
    Node< T > *head;
    size_t size;

  public:
    BiList() noexcept;
    BiList(const BiList &other);
    BiList(BiList &&other) noexcept;
    ~BiList();

    BiList& operator=(const BiList& other);
    BiList& operator=(BiList&& other) noexcept;

    void clear() noexcept;

    bool is_empty() const noexcept;

    size_t getsize() const noexcept;

    T & front() noexcept;
    const T & front() const noexcept;

    T & back() noexcept;
    const T & back() const noexcept;

    LIter<T> begin() noexcept;
    LCIter<T> begin() const noexcept;
    LCIter<T> cbegin() const noexcept;

    LIter<T> end() noexcept;
    LCIter<T> end() const noexcept;
    LCIter<T> cend() const noexcept;

    void push_front(const T & value);
    void push_front(T && value);
    void push_back(const T & value);
    void push_back(T && value);

    LIter<T> insert_before(LIter<T> pos, const T & value);
    LIter<T> insert_before(LIter<T> pos, T && value);
    LIter<T> insert_after(LIter<T> pos, const T & value);
    LIter<T> insert_after(LIter<T> pos, T && value);

    void pop_front() noexcept;
    void pop_back() noexcept;

    LIter<T> erase(LIter<T> pos) noexcept;

    void swap(BiList & other) noexcept;
  };
}













#endif
