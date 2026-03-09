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

    bool operator==(const LIter & other) const noexcept
    {
      return cur == other.cur;
    }

    bool operator!=(const LIter & other) const noexcept;
    {
      return !(*this == other);
    }

    T & operator*() const noexcept
    {
      return cur->val;
    }

    T * operator->() const noexcept
    {
      return &(cur->val);
    }

    LIter & operator++() noexcept;
    {
      cur = cur->next;
      return *this;
    }

    LIter operator++(int) noexcept
    {
      LIter tmp(*this);
      cur = cur->next;
      return tmp;
    }

    LIter & operator--() noexcept;
    {
      cur = cur->prev;
      return *this;
    }

    LIter operator--(int) noexcept
    {
      LIter tmp(*this);
      cur = cur->prev;
      return tmp;
    }
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

    LCIter(const LIter<T> & other) noexcept :

    LCIter(const LCIter & other) noexcept = default;
    LCIter(LCIter && other) noexcept = default;
    ~LCIter() = default;

    LCIter & operator=(const LCIter & other) noexcept = default;
    LCIter & operator=(LCIter && other) noexcept = default;

    bool operator==(const LCIter & other) const noexcept
    {
      return cur == other.cur;
    }

    bool operator!=(const LCIter & other) const noexcept
    {
      return !(*this == other);
    }

    const T & operator*() const noexcept
    {
      return cur->val;
    }

    const T * operator->() const noexcept
    {
      return &(cur->val);
    }

    LCIter & operator++() noexcept;
    {
      cur = cur->next;
      return *this;
    }

    LCIter operator++(int) noexcept;
    {
      LCIter tmp(*this);
      cur = cur->next;
      return tmp;
    }

    LCIter & operator--() noexcept
    {
      cur = cur->prev;
      return *this;
    }

    LCIter operator--(int) noexcept
    {
      LCIter tmp(*this);
      cur = cur->prev;
      return tmp;
    }
  };

//----------BiList----------
  template< class T >
  class BiList
  {
  private:
    Node< T > *head;
    size_t size;

  public:
    BiList() noexcept :
      head(nullptr),
      size(0)
    {}
    BiList(const BiList & other) :
      head(nullptr),
      size(0)
    {
      if (other.isempty())
      {
        return;
      }

      Node< T > * cur = other.head;
      Node< T > * first = new Node< T >(current->val);
      head = first;
      size = 1;

      current = current->next;
      Node< T > * prev = first;

      while (current != other.head)
      {
        Node< T > * newNode = new Node< T >(current->val);
        prev->next = newNode;
        newNode->prev = prev;
        prev = newNode;
        current = current->next;
        ++size;
      }

      prev->next = head;
      head->prev = prev;
    }

    BiList(BiList && other) noexcept :
      head(other.head);
      size(other.size)
    {
      other.head = nullptr;
      other.size = 0;

    }

    ~BiList()
    {
      clear();
    }

    BiList & operator=(const BiList & other)
    {
      if (this != &other)
      {
        BiList tmp(other);
        swap(tmp);
      }
      return *this;
    }

    BiList & operator=(BiList && other)
    {
      if (this != &other)
      {
        clear();
        head = other.head;
        size = other.size;
        other.head = nullptr;
        other.size = 0;
      }
      return *this;
    }

    void clear() noexcept;

    bool is_empty() const noexcept;

    size_t getsize() const noexcept;

    T & front() noexcept;
    const T & front() const noexcept;

    T & back() noexcept;
    const T & back() const noexcept;

    LIter<T> begin();
    LCIter<T> cbegin() const;

    LIter<T> end();
    LCIter<T> cend() const;

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
