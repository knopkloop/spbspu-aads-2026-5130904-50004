#ifndef BILIST_HPP
#define BILIST_HPP
#include "iterators.hpp"
#include <iostream>
#include <utility>

namespace haliullin
{
  template< class T >
  class BiList
  {
  private:
    Node< T > *head;
    size_t size;

  public:
    BiList():
      head(nullptr),
      size(0)
    {}

    BiList(const BiList & other):
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

    BiList(BiList && other) noexcept:
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

    bool is_empty() const
    {
      return size == 0;
    }

    size_t getsize() const
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

    LIter<T> begin()
    {
      return LIter<T>(head, head);
    }

    LCIter<T> cbegin() const
    {
      return LCIter<T>(head, head);
    }

    LIter<T> end()
    {
      return LIter<T>(nullptr, head);
    }

    LCIter<T> cend() const
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

    LIter<T> insert(LIter<T> pos, const T & value)
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

    LIter<T> insert(LIter<T> pos, T && value)
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

    void clear()
    {
      while(!is_empty())
      {
        pop_front();
      }
    }
  };
}

#endif
