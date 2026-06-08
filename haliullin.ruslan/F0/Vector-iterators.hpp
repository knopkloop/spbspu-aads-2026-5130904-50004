#ifndef VECTOR_ITERATORS_HPP
#define VECTOR_ITERATORS_HPP

#include <cstddef>
#include <memory>

namespace haliullin
{
  template< class T >
  class Vector;

  template< class T >
  class VCIter;

  template< class T >
  class VIter
  {
  public:
    VIter() noexcept;

    T& operator*() const noexcept;
    T* operator->() const noexcept;

    VIter& operator++() noexcept;
    VIter operator++(int) noexcept;

    bool operator==(const VIter& other) const noexcept;
    bool operator!=(const VIter& other) const noexcept;

  private:
    T* ptr_;

    VIter(T* ptr) noexcept;
    VIter(Vector< T >& vec, size_t idx) noexcept;

    friend class VCIter< T >;
    friend class Vector< T >;
  };

  template< class T >
  class VCIter
  {
  public:
    VCIter() noexcept;

    const T& operator*() const noexcept;
    const T* operator->() const noexcept;

    VCIter& operator++() noexcept;
    VCIter operator++(int) noexcept;

    bool operator==(const VCIter& other) const noexcept;
    bool operator!=(const VCIter& other) const noexcept;

  private:
    const T* cptr_;

    VCIter(const T* ptr) noexcept;
    VCIter(const Vector< T >& vec, size_t idx) noexcept;
    explicit VCIter(const VIter< T >& other) noexcept;

    friend class Vector< T >;
  };
}

template< class T >
haliullin::VIter< T >::VIter() noexcept:
  ptr_(nullptr)
{}

template< class T >
haliullin::VIter< T >::VIter(T* ptr) noexcept:
  ptr_(ptr)
{}

template< class T >
haliullin::VIter< T >::VIter(Vector< T >& vec, size_t idx) noexcept:
  ptr_(std::addressof(vec[idx]))
{}

template< class T >
T& haliullin::VIter< T >::operator*() const noexcept
{
  return *ptr_;
}

template< class T >
T* haliullin::VIter< T >::operator->() const noexcept
{
  return ptr_;
}

template< class T >
haliullin::VIter< T >& haliullin::VIter< T >::operator++() noexcept
{
  ++ptr_;
  return *this;
}

template< class T >
haliullin::VIter< T > haliullin::VIter< T >::operator++(int) noexcept
{
  VIter< T > tmp = *this;
  ++ptr_;
  return tmp;
}

template< class T >
bool haliullin::VIter< T >::operator==(const VIter& other) const noexcept
{
  return ptr_ == other.ptr_;
}

template< class T >
bool haliullin::VIter< T >::operator!=(const VIter& other) const noexcept
{
  return !(*this == other);
}

template< class T >
haliullin::VCIter< T >::VCIter() noexcept:
  cptr_(nullptr)
{}

template< class T >
haliullin::VCIter< T >::VCIter(const T* ptr) noexcept:
  cptr_(ptr)
{}

template< class T >
haliullin::VCIter< T >::VCIter(const Vector< T >& vec, size_t idx) noexcept:
  cptr_(std::addressof(vec[idx]))
{}

template< class T >
haliullin::VCIter< T >::VCIter(const VIter< T >& other) noexcept:
  cptr_(other.ptr_)
{}

template< class T >
const T& haliullin::VCIter< T >::operator*() const noexcept
{
  return *cptr_;
}

template< class T >
const T* haliullin::VCIter< T >::operator->() const noexcept
{
  return cptr_;
}

template< class T >
haliullin::VCIter< T >& haliullin::VCIter< T >::operator++() noexcept
{
  ++cptr_;
  return *this;
}

template< class T >
haliullin::VCIter< T > haliullin::VCIter< T >::operator++(int) noexcept
{
  VCIter< T > tmp = *this;
  ++cptr_;
  return tmp;
}

template< class T >
bool haliullin::VCIter< T >::operator==(const VCIter< T >& other) const noexcept
{
  return cptr_ == other.cptr_;
}

template< class T >
bool haliullin::VCIter< T >::operator!=(const VCIter< T >& other) const noexcept
{
  return !(*this == other);
}

#endif
