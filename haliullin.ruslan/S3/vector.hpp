#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stdexcept>
#include <memory>
#include <new>
#include <utility>

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

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;
    void pushBack(const T& val);
    void insert(size_t id, const T& val);
    void erase(size_t id);
    void insSort();

    bool operator==(const Vector& rhs) const noexcept;
    bool operator!=(const Vector& rhs) const noexcept;
    bool operator<(const Vector& rhs) const noexcept;

  private:
    T* data_;
    size_t size_, capacity_;
    void clear() noexcept;
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
    Vector< T > cpy(rhs);
    swap(cpy);
  }
  return *this;
}

template< class T >
haliullin::Vector< T >& haliullin::Vector< T >::operator=(Vector&& rhs) noexcept
{
  if (this != std::addressof(rhs))
  {
    Vector< T > cpy(std::move(rhs));
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
void haliullin::Vector< T >::pushBack(const T& val)
{
  if (size_ == capacity_)
  {
    size_t new_cap = capacity_ ? capacity_ * 2 : 1;
    T* temp_data = static_cast< T* >(::operator new(new_cap * sizeof(T)));
    size_t constructed = 0;

    try
    {
      for (; constructed < size_; ++constructed)
      {
        new (temp_data + constructed) T(std::move(data_[constructed]));
      }
      new (temp_data + constructed) T(val);
      ++constructed;
    }
    catch (...)
    {
      for (size_t i = 0; i < constructed; ++i)
      {
        temp_data[i].~T();
      }
      ::operator delete(temp_data);
      throw;
    }

    clear();
    ::operator delete(data_);
    data_ = temp_data;
    capacity_ = new_cap;
    size_ = constructed;
  }
  else
  {
    new (data_ + size_) T(val);
    ++size_;
  }
}

template< class T >
void haliullin::Vector< T >::insert(size_t id, const T& val)
{
  if (id > size_)
  {
    throw std::out_of_range("id out of bound");
  }
  Vector< T > v;
  for (size_t i = 0; i < id; ++i)
  {
    v.pushBack((*this)[i]);
  }
  v.pushBack(val);
  for (size_t i = id; i < size_; ++i)
  {
    v.pushBack((*this)[i]);
  }
  swap(v);
}

template< class T >
void haliullin::Vector< T >::erase(size_t id)
{
  if (id >= size_)
  {
    throw std::out_of_range("id out of bound");
  }
  Vector< T > v;
  for (size_t i = 0; i < id; ++i)
  {
    v.pushBack((*this)[i]);
  }
  for (size_t i = id + 1; i < size_; ++i)
  {
    v.pushBack((*this)[i]);
  }
  swap(v);
}

template< class T >
void haliullin::Vector< T >::insSort()
{
  Vector< T > tmp(*this);
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

#endif
