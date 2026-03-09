#ifndef BILIST_HPP
#define BILIST_HPP
#include <iostream>
#include <utility>
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
    Node(const T & value, Node * p, Node * n) :
      val(value),
      prev(p),
      next(n)
    {}
    Node(T && value, Node * p, Node * n) :
      val(std::move(value)),
      prev(p),
      next(n)
    {}
  };

  template< class T >
  class LIter
  {
    friend class BiList<T>;
    Node<T> * cur;
    Node<T> * head;
    explicit LIter(Node<T> * node, Node<T> * listHead) noexcept :
      cur(node),
      head(listHead)
    {}
  public:
    LIter() noexcept :
      cur(nullptr),
      head(nullptr)
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

    bool operator!=(const LIter & other) const noexcept
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

    LIter & operator++() noexcept
    {
      if (cur)
      {
        cur = cur->next;
        if (cur == head)
        {
          cur = nullptr;
        }
      }
      return *this;
    }

    LIter operator++(int) noexcept
    {
      LIter tmp(*this);
      ++(*this);
      return tmp;
    }

    LIter & operator--() noexcept
    {
      if (cur == head)
      {
        cur = nullptr;
      }
      else if (cur)
      {
        cur = cur->prev;
      }
      return *this;
    }

    LIter operator--(int) noexcept
    {
      LIter tmp(*this);
      --(*this);
      return tmp;
    }
  };

  template< class T >
  class LCIter
  {
    friend class BiList< T >;
    const Node< T > * cur;
    const Node< T > * head;
    explicit LCIter(const Node<T> * node, const Node<T> * listHead) noexcept :
      cur(node),
      head(listHead)
    {}
  public:
    LCIter() noexcept :
      cur(nullptr),
      head(nullptr)
    {}

    LCIter(const LIter<T> & other) noexcept :
      cur(other.cur),
      head(other.head)
    {}

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

    LCIter & operator++() noexcept
    {
      if (cur)
      {
        cur = cur->next;
        if (cur == head)
        {
          cur = nullptr;
        }
      }
      return *this;
    }

    LCIter operator++(int) noexcept
    {
      LCIter tmp(*this);
      ++(*this);
      return tmp;
    }

    LCIter & operator--() noexcept
    {
      if (cur == head)
      {
        cur = nullptr;
      }
      else if (cur)
      {
        cur = cur->prev;
      }
      return *this;
    }

    LCIter operator--(int) noexcept
    {
      LCIter tmp(*this);
      --(*this);
      return tmp;
    }
  };

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
      if (other.is_empty())
      {
        return;
      }
      Node<T> * current = other.head;
      Node<T> * first = new Node<T>(current->val);
      head = first;
      size = 1;
      current = current->next;
      Node<T> * prev = first;
      while (current != other.head)
      {
        Node<T> * newNode = new Node<T>(current->val);
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
      head(other.head),
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

    BiList & operator=(BiList && other) noexcept
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

    bool is_empty() const noexcept
    {
      return size == 0;
    }

    size_t getsize() const noexcept
    {
      return size;
    }

    T & front()
    {
      if (is_empty())
      {
        throw std::runtime_error("Empty list");
      }
      return head->val;
    }

    const T & front() const
    {
      if (is_empty())
      {
        throw std::runtime_error("Empty list");
      }
      return head->val;
    }

    T & back()
    {
      if (is_empty())
      {
        throw std::runtime_error("Empty list");
      }
      return head->prev->val;
    }

    const T & back() const
    {
      if (is_empty())
      {
        throw std::runtime_error("Empty list");
      }
      return head->prev->val;
    }

    LIter<T> begin() noexcept
    {
      return LIter<T>(head, head);
    }

    LCIter<T> cbegin() const noexcept
    {
      return LCIter<T>(head, head);
    }

    LIter<T> end() noexcept
    {
      return LIter<T>(nullptr, head);
    }

    LCIter<T> cend() const noexcept
    {
      return LCIter<T>(nullptr, head);
    }

    void push_front(const T & value)
    {
      Node<T> * newNode = new Node<T>(value);
      if(is_empty())
      {
        head = newNode;
        head->next = head;
        head->prev = head;
      }
      else
      {
        newNode->next = head;
        newNode->prev = head->prev;
        head->prev->next = newNode;
        head->prev = newNode;
        head = newNode;
      }
      ++size;
    }

    void push_front(T && value)
    {
      Node<T> * newNode = new Node<T>(std::move(value));
      if(is_empty())
      {
        head = newNode;
        head->next = head;
        head->prev = head;
      }
      else
      {
        newNode->next = head;
        newNode->prev = head->prev;
        head->prev->next = newNode;
        head->prev = newNode;
        head = newNode;
      }
      ++size;
    }

    void push_back(const T & value)
    {
      if(is_empty())
      {
        push_front(value);
      }
      else
      {
        Node<T> * newNode = new Node<T>(value);
        Node<T> * last = head->prev;
        newNode->next = head;
        newNode->prev = last;
        last->next = newNode;
        head->prev = newNode;
        ++size;
      }
    }

    void push_back(T && value)
    {
      if(is_empty())
      {
        push_front(std::move(value));
      }
      else
      {
        Node<T> * newNode = new Node<T>(std::move(value));
        Node<T> * last = head->prev;
        newNode->next = head;
        newNode->prev = last;
        last->next = newNode;
        head->prev = newNode;
        ++size;
      }
    }

    LIter<T> insert_after(LIter<T> pos, const T & value)
    {
      if (is_empty())
      {
        push_front(value);
        return begin();
      }
      if (pos.cur == nullptr)
      {
        push_front(value);
        return begin();
      }
      Node<T> * newNode = new Node<T>(value, pos.cur, pos.cur->next);
      pos.cur->next->prev = newNode;
      pos.cur->next = newNode;
      if (pos.cur == head->prev)
      {
        head->prev = newNode;
      }
      ++size;
      return LIter<T>(newNode, head);
    }

    LIter<T> insert_after(LIter<T> pos, T && value)
    {
      if (is_empty())
      {
        push_front(std::move(value));
        return begin();
      }
      if (pos.cur == nullptr)
      {
        push_front(std::move(value));
        return begin();
      }
      Node<T> * newNode = new Node<T>(std::move(value), pos.cur, pos.cur->next);
      pos.cur->next->prev = newNode;
      pos.cur->next = newNode;
      if (pos.cur == head->prev)
      {
        head->prev = newNode;
      }
      ++size;
      return LIter<T>(newNode, head);
    }

    LIter<T> insert_before(LIter<T> pos, const T & value)
    {
      if (pos.cur == nullptr)
      {
        push_back(value);
        return LIter<T>(head->prev, head);
      }
      LIter<T> prev(pos.cur->prev, head);
      return insert_after(prev, value);
    }

    LIter<T> insert_before(LIter<T> pos, T && value)
    {
      if (pos.cur == nullptr)
      {
        push_back(std::move(value));
        return LIter<T>(head->prev, head);
      }
      LIter<T> prev(pos.cur->prev, head);
      return insert_after(prev, std::move(value));
    }

    void pop_front()
    {
      if (is_empty())
      {
        throw std::runtime_error("Empty list");
      }
      else if (getsize() == 1)
      {
        delete head;
        head = nullptr;
        size = 0;
      }
      else
      {
        Node<T> * first = head;
        head->prev->next = head->next;
        head->next->prev = head->prev;
        head = head->next;
        delete first;
        --size;
      }
    }

    void pop_back()
    {
      if (is_empty())
      {
        throw std::runtime_error("Empty list");
      }
      else if (getsize() == 1)
      {
        delete head;
        head = nullptr;
        size = 0;
      }
      else
      {
        Node<T> * last = head->prev;
        last->prev->next = head;
        head->prev = last->prev;
        delete last;
        --size;
      }
    }

    LIter<T> erase(LIter<T> pos)
    {
      if (is_empty())
      {
        throw std::runtime_error("Empty list");
      }
      if (pos.cur == nullptr)
      {
        throw std::runtime_error("Cannot erase end iterator");
      }
      if (getsize() == 1)
      {
        delete pos.cur;
        head = nullptr;
        size = 0;
        return end();
      }
      Node<T> * toDelete = pos.cur;
      Node<T> * nextNode = toDelete->next;
      if (toDelete == head)
      {
        pop_front();
        return begin();
      }
      else if (toDelete == head->prev)
      {
        pop_back();
        return end();
      }
      else
      {
        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
        delete toDelete;
        --size;
        return LIter<T>(nextNode, head);
      }
    }

    void clear() noexcept
    {
      while(!is_empty())
      {
        pop_front();
      }
    }

    void swap(BiList & other) noexcept
    {
      Node<T> * tmp_head = head;
      size_t tmp_size = size;
      head = other.head;
      size = other.size;
      other.head = tmp_head;
      other.size = tmp_size;
    }
  };
}
#endif
