#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stdexcept>
#include <memory>

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

    Vector(const Vector< T >& rhs);
    Vector(Vector< T >&& rhs) noexcept;

    Vector< T >& operator=(const Vector< T >& rhs);
    Vector< T >& operator=(Vector< T >&& rhs) noexcept;
    void swap(Vector< T >& rhs) noexcept;

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;
    void pushBack(const T& val);
    void insert(size_t id, const T& val);
    void erase(size_t id);
    void insSort();

    bool operator==(const Vector< T >& rhs) const noexcept;
    bool operator!=(const Vector< T >& rhs) const noexcept;
    bool operator<(const Vector< T >& rhs) const noexcept;

  private:
    T* data_;
    size_t size_, capacity_;
  };
}

template< class T >
haliullin::Vector< T >::~Vector()
{
  delete[] data_;
}

template< class T >
haliullin::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template< class T>
haliullin::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}

template< class T >
haliullin::Vector< T >::Vector(size_t size, const T& value):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i)
  {
    data_[i] = value;
  }
}

template< class T>
haliullin::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i)
  {
    data_[i] = rhs.data_[i];
  }
}

template< class T >
haliullin::Vector< T >::Vector(Vector< T >&& rhs) noexcept:
  Vector()
{
  swap(rhs);
}

template< class T >
haliullin::Vector< T >& haliullin::Vector<T>::operator=(const Vector< T >& rhs)
{
  if (this != std::addressof(rhs))
  {
    Vector< T > cpy(rhs);
    swap(cpy);
  }
  return *this;
}

template< class T >
haliullin::Vector< T >& haliullin::Vector< T >::operator=(Vector< T >&& rhs) noexcept
{
  if (this != std::addressof(rhs))
  {
    Vector< T > cpy(std::move(rhs));
    swap(cpy);
  }
  return *this;
}

template< class T >
void haliullin::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template< class T >
T& haliullin::Vector< T >::operator[](size_t id) noexcept
{
  return const_cast< T& >((*static_cast< const Vector< T >* >(this))[id]);
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
    T* temp_data = new T[new_cap];

    try
    {
      for (size_t i = 0; i < size_; ++i)
      {
        temp_data[i] = data_[i];
      }

      temp_data[size_++] = val;
    }
    catch (...)
    {
      delete[] temp_data;
      throw;
    }

    delete[] data_;
    data_ = temp_data;
    capacity_ = new_cap;
  }
  else
  {
    data_[size_++] = val;
  }
}

template< class T >
void haliullin::Vector< T >::insert(size_t id, const T& val)
{
  if (id > getSize())
  {
    throw std::out_of_range("id out of bound");
  }
  Vector< T > v;
  for(size_t i = 0; i < id; ++i)
  {
    v.pushBack((*this)[i]);
  }
  v.pushBack(val);
  for(size_t i = id; i < getSize(); ++i)
  {
    v.pushBack((*this)[i]);
  }
  swap(v);
}

template< class T >
void haliullin::Vector< T >::erase(size_t id)
{
  if (id >= getSize())
  {
    throw std::out_of_range("id out of bound");
  }
  Vector< T > v(getSize() - 1);
  for (size_t i = 0; i < id; ++i)
  {
    v[i] = (*this)[i];
  }
  for (size_t i = id; i < v.getSize(); ++i)
  {
    v[i] = (*this)[i + 1];
  }
  swap(v);
}

template< class T >
void haliullin::Vector< T >::insSort()
{
  Vector< T > tmp(*this);
  try
  {
    for (size_t i = 1; i < tmp.size_; ++i)
    {
      T key = tmp.data_[i];
      size_t j = i;
      while (j > 0 && tmp.data_[j - 1] > key)
      {
        tmp.data_[j] = tmp.data_[j - 1];
        --j;
      }
      tmp.data_[j] = key;
    }
  }
  catch (...)
  {
    throw;
  }
  swap(tmp);
}

template< class T >
bool haliullin::Vector< T >::operator==(const Vector< T >& rhs) const noexcept
{
  bool isEqual = (getSize() == rhs.getSize());
  for (size_t i = 0; i < getSize() && isEqual; ++i)
  {
    isEqual = ((*this)[i] == rhs[i]);
  }
  return isEqual;
}

template< class T >
bool haliullin::Vector< T >::operator!=(const Vector< T >& rhs) const noexcept
{
  return !(*this == rhs);
}

template< class T >
bool haliullin::Vector< T >::operator<(const Vector< T >& rhs) const noexcept
{
  size_t minSize = getSize() < rhs.getSize() ? getSize() : rhs.getSize();
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
  return getSize() < rhs.getSize();
}

#endif
