#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <utility>
#include <new>
#include <stdexcept>
#include <memory>
#include "Vector-iterators.hpp"

namespace haliullin
{
  template< class T >
  class Vector
  {
  public:
    ~Vector();
    Vector();
    explicit Vector(size_t size);
    Vector(size_t size, const T& value);

    Vector(const Vector& rhs);
    Vector(Vector&& rhs) noexcept;

    Vector& operator=(const Vector& rhs);
    Vector& operator=(Vector&& rhs) noexcept;
    void swap(Vector& rhs) noexcept;

    T& at(size_t id);
    const T& at(size_t id) const;
    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    template< class U >
    void pushBack(U&& val);
    void insert(size_t id, const T& val);
    void erase(size_t id);
    void insSort();

    void reserve(size_t newCap);
    void shrinkToFit();
    void resize(size_t newSize, const T& val = T());

    bool operator==(const Vector& rhs) const noexcept;
    bool operator!=(const Vector& rhs) const noexcept;
    bool operator<(const Vector& rhs) const noexcept;

    VIter< T > begin() noexcept;
    VCIter< T > begin() const noexcept;
    VCIter< T > cbegin() const noexcept;
    VIter< T > end() noexcept;
    VCIter< T > end() const noexcept;
    VCIter< T > cend() const noexcept;

  private:
    T* data_;
    size_t size_, capacity_;

    void clear() noexcept;
    void reallocate(size_t newCap);
  };
}

template< class T >
void haliullin::Vector< T >::clear() noexcept
{
  for (size_t i = 0; i < size_; ++i)
  {
    data_[i].~T();
  }
  size_ = 0;
}

template< class T >
haliullin::Vector< T >::~Vector()
{
  clear();
  ::operator delete(data_);
}

template< class T >
haliullin::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template< class T >
haliullin::Vector< T >::Vector(size_t size):
  data_(size ? static_cast< T* >(::operator new(size * sizeof(T))) : nullptr),
  size_(0),
  capacity_(size)
{
  try
  {
    for (; size_ < capacity_; ++size_)
    {
      new (data_ + size_) T();
    }
  }
  catch (...)
  {
    clear();
    ::operator delete(data_);
    data_ = nullptr;
    capacity_ = 0;
    throw;
  }
}

template< class T >
haliullin::Vector< T >::Vector(size_t size, const T& value):
  data_(size ? static_cast< T* >(::operator new(size * sizeof(T))) : nullptr),
  size_(0),
  capacity_(size)
{
  try
  {
    for (; size_ < capacity_; ++size_)
    {
      new (data_ + size_) T(value);
    }
  }
  catch (...)
  {
    clear();
    ::operator delete(data_);
    data_ = nullptr;
    capacity_ = 0;
    throw;
  }
}

template< class T>
haliullin::Vector< T >::Vector(const Vector& rhs):
  data_(rhs.size_ ? static_cast< T* >(::operator new(rhs.size_ * sizeof(T))) : nullptr),
  size_(0),
  capacity_(rhs.size_)
{
  try
  {
    for (; size_ < capacity_; ++size_)
    {
      new (data_ + size_) T(rhs.data_[size_]);
    }
  }
  catch (...)
  {
    clear();
    ::operator delete(data_);
    data_ = nullptr;
    capacity_ = 0;
    throw;
  }
}

template< class T >
haliullin::Vector< T >::Vector(Vector&& rhs) noexcept:
  Vector()
{
  swap(rhs);
}

template< class T >
haliullin::Vector< T >& haliullin::Vector<T>::operator=(const Vector& rhs)
{
  if (this != std::addressof(rhs))
  {
    Vector cpy(rhs);
    swap(cpy);
  }
  return *this;
}

template< class T >
haliullin::Vector< T >& haliullin::Vector< T >::operator=(Vector&& rhs) noexcept
{
  if (this != std::addressof(rhs))
  {
    Vector cpy(std::move(rhs));
    swap(cpy);
  }
  return *this;
}

template< class T >
void haliullin::Vector< T >::swap(Vector& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template< class T >
T& haliullin::Vector< T >::at(size_t id)
{
  return const_cast< T& >(static_cast< const Vector& >(*this).at(id));
}

template< class T >
const T& haliullin::Vector< T >::at(size_t id) const
{
  if (id < getSize())
  {
    return (*this)[id];
  }
  throw std::out_of_range("id out of bound");
}

template< class T >
T& haliullin::Vector< T >::operator[](size_t id) noexcept
{
  return data_[id];
}

template< class T >
const T& haliullin::Vector< T >::operator[](size_t id) const noexcept
{
  return data_[id];
}

template< class T >
bool haliullin::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

template< class T >
size_t haliullin::Vector< T >::getSize() const noexcept
{
  return size_;
}

template< class T >
size_t haliullin::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}

template< class T >
template< class U >
void haliullin::Vector< T >::pushBack(U&& val)
{
  Vector tmp(*this);
  if (tmp.size_ == tmp.capacity_)
  {
    tmp.reserve(tmp.capacity_ ? tmp.capacity_ * 2 : 1);
  }
  new (tmp.data_ + tmp.size_) T(std::forward< U >(val));
  ++tmp.size_;
  swap(tmp);
}

template< class T >
void haliullin::Vector< T >::insert(size_t id, const T& val)
{
  if (id > size_)
  {
    throw std::out_of_range("id out of bound");
  }
  Vector tmp;
  for (size_t i = 0; i < id; ++i)
  {
    tmp.pushBack((*this)[i]);
  }
  tmp.pushBack(val);
  for (size_t i = id; i < size_; ++i)
  {
    tmp.pushBack((*this)[i]);
  }
  swap(tmp);
}

template< class T >
void haliullin::Vector< T >::erase(size_t id)
{
  if (id >= size_)
  {
    throw std::out_of_range("id out of bound");
  }
  Vector tmp;
  for (size_t i = 0; i < id; ++i)
  {
    tmp.pushBack((*this)[i]);
  }
  for (size_t i = id + 1; i < size_; ++i)
  {
    tmp.pushBack((*this)[i]);
  }
  swap(tmp);
}

template< class T >
void haliullin::Vector< T >::insSort()
{
  Vector tmp(*this);
  for (size_t i = 1; i < tmp.size_; ++i)
  {
    T key = std::move(tmp.data_[i]);
    size_t j = i;
    while (j > 0 && tmp.data_[j - 1] > key)
    {
      tmp.data_[j].~T();
      new (std::addressof(tmp.data_[j])) T(std::move(tmp.data_[j - 1]));
      --j;
    }
    tmp.data_[j].~T();
    new (std::addressof(tmp.data_[j])) T(std::move(key));
  }
  swap(tmp);
}

template< class T >
void haliullin::Vector< T >::reallocate(size_t newCap)
{
  T* newData = static_cast< T* >(::operator new(newCap * sizeof(T)));
  size_t constructed = 0;
  try
  {
    for (; constructed < size_; ++constructed)
    {
      new (newData + constructed) T(std::move(data_[constructed]));
    }
  }
  catch (...)
  {
    for (size_t i = 0; i < constructed; ++i)
    {
      newData[i].~T();
    }
    ::operator delete(newData);
    throw;
  }

  for (size_t i = 0; i < size_; ++i)
  {
    data_[i].~T();
  }
  ::operator delete(data_);
  data_ = newData;
  capacity_ = newCap;
}

template< class T >
void haliullin::Vector< T >::reserve(size_t newCap)
{
  if (newCap > capacity_)
  {
    reallocate(newCap);
  }
}

template< class T >
void haliullin::Vector< T >::shrinkToFit()
{
  if (capacity_ <= size_)
  {
    return;
  }
  if (size_ == 0)
  {
    ::operator delete(data_);
    data_ = nullptr;
    capacity_ = 0;
    return;
  }
  reallocate(size_);
}

template< class T >
void haliullin::Vector< T >::resize(size_t newSize, const T& val)
{
  Vector tmp(*this);
  if (newSize > tmp.capacity_)
  {
    tmp.reserve(newSize);
  }
  for (size_t i = tmp.size_; i < newSize; ++i)
  {
    new (tmp.data_ + i) T(val);
  }
  for (size_t i = newSize; i < tmp.size_; ++i)
  {
    tmp.data_[i].~T();
  }
  tmp.size_ = newSize;
  swap(tmp);
}

template< class T >
bool haliullin::Vector< T >::operator==(const Vector& rhs) const noexcept
{
  bool isEqual = (size_ == rhs.size_);
  for (size_t i = 0; i < size_ && isEqual; ++i)
  {
    isEqual = ((*this)[i] == rhs[i]);
  }
  return isEqual;
}

template< class T >
bool haliullin::Vector< T >::operator!=(const Vector& rhs) const noexcept
{
  return !(*this == rhs);
}

template< class T >
bool haliullin::Vector< T >::operator<(const Vector& rhs) const noexcept
{
  size_t minSize = (size_ < rhs.size_) ? size_ : rhs.size_;
  for (size_t i = 0; i < minSize; ++i)
  {
    if ((*this)[i] < rhs[i])
    {
      return true;
    }
    if (rhs[i] < (*this)[i])
    {
      return false;
    }
  }
  return size_ < rhs.size_;
}

template< class T >
haliullin::VIter< T > haliullin::Vector< T >::begin() noexcept
{
  return VIter< T >(data_);
}

template< class T >
haliullin::VCIter< T > haliullin::Vector< T >::begin() const noexcept
{
  return VCIter< T >(data_);
}

template< class T >
haliullin::VCIter< T > haliullin::Vector< T >::cbegin() const noexcept
{
  return begin();
}

template< class T >
haliullin::VIter< T > haliullin::Vector< T >::end() noexcept
{
  return VIter< T >(data_ + size_);
}

template< class T >
haliullin::VCIter< T > haliullin::Vector< T >::end() const noexcept
{
  return VCIter< T >(data_ + size_);
}

template< class T >
haliullin::VCIter< T > haliullin::Vector< T >::cend() const noexcept
{
  return end();
}

#endif
