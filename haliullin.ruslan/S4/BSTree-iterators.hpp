#ifndef BSTREE_ITERATORS_HPP
#define BSTREE_ITERATORS_HPP

#include <iterator>
#include <memory>
#include "TreeNode.hpp"
#include "tree-traverse.hpp"

namespace haliullin
{
  template< class Key, class Value, class Compare >
  class BSTree;

  template< class Key, class Value >
  class BSTConstIterator;

  template< class Key, class Value >
  class BSTIterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< const Key, Value >,
    std::ptrdiff_t, std::pair< const Key, Value >*, std::pair< const Key, Value >& >
  {
  public:
    using Node = detail::TreeNode< Key, Value >;
    using pair_t = std::pair< const Key, Value >;

    pair_t& operator*() const noexcept;
    pair_t* operator->() const noexcept;

    BSTIterator& operator++() noexcept;
    BSTIterator operator++(int) noexcept;
    BSTIterator& operator--() noexcept;
    BSTIterator operator--(int) noexcept;

    bool operator==(const BSTIterator& other) const noexcept;
    bool operator!=(const BSTIterator& other) const noexcept;

  private:
    Node* node_;

    BSTIterator(Node* node = nullptr) noexcept;
    friend class BSTConstIterator< Key, Value >;
    template< class K, class V, class C >
    friend class BSTree;
  };

  template< class Key, class Value >
  class BSTConstIterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< const Key, Value >,
    std::ptrdiff_t, const std::pair< const Key, Value >*, const std::pair< const Key, Value >& >
  {
  public:
    using Node = detail::TreeNode< Key, Value >;
    using c_pair_t = const std::pair< const Key, Value >;

    BSTConstIterator(const BSTIterator< Key, Value >& it) noexcept;

    c_pair_t& operator*() const noexcept;
    c_pair_t* operator->() const noexcept;

    BSTConstIterator& operator++() noexcept;
    BSTConstIterator operator++(int) noexcept;
    BSTConstIterator& operator--() noexcept;
    BSTConstIterator operator--(int) noexcept;

    bool operator==(const BSTConstIterator& other) const noexcept;
    bool operator!=(const BSTConstIterator& other) const noexcept;

  private:
    Node* node_;

    BSTConstIterator(Node* node = nullptr) noexcept;
    template < class K, class V, class C >
    friend class BSTree;
  };
}

template< class Key, class Value >
haliullin::BSTIterator< Key, Value >::BSTIterator(Node* node) noexcept:
  node_(node ? node : std::addressof(Node::fakeLeaf_))
{}

template< class Key, class Value >
std::pair< const Key, Value >& haliullin::BSTIterator< Key, Value >::operator*() const noexcept
{
  return node_->data_;
}

template< class Key, class Value >
std::pair< const Key, Value >* haliullin::BSTIterator< Key, Value >::operator->() const noexcept
{
  return std::addressof(node_->data_);
}

template< class Key, class Value >
haliullin::BSTIterator< Key, Value >& haliullin::BSTIterator< Key, Value >::operator++() noexcept
{
  node_ = next(node_);
  return *this;
}

template< class Key, class Value >
haliullin::BSTIterator< Key, Value > haliullin::BSTIterator< Key, Value >::operator++(int) noexcept
{
  BSTIterator tmp(*this);
  ++(*this);
  return tmp;
}

template< class Key, class Value >
haliullin::BSTIterator< Key, Value >& haliullin::BSTIterator< Key, Value >::operator--() noexcept
{
  node_ = previous(node_);
  return *this;
}

template< class Key, class Value >
haliullin::BSTIterator< Key, Value > haliullin::BSTIterator< Key, Value >::operator--(int) noexcept
{
  BSTIterator tmp(*this);
  --(*this);
  return tmp;
}

template< class Key, class Value >
bool haliullin::BSTIterator< Key, Value >::operator==(const BSTIterator& other) const noexcept
{
  return node_ == other.node_;
}

template< class Key, class Value >
bool haliullin::BSTIterator< Key, Value >::operator!=(const BSTIterator& other) const noexcept
{
  return !(*this == other);
}

template< class Key, class Value >
haliullin::BSTConstIterator< Key, Value >::BSTConstIterator(Node* node) noexcept:
  node_(node ? node : std::addressof(Node::fakeLeaf_))
{}

template< class Key, class Value >
haliullin::BSTConstIterator< Key, Value >::BSTConstIterator(const BSTIterator< Key, Value >& it) noexcept:
  node_(it.node_)
{}

template< class Key, class Value >
const std::pair< const Key, Value >& haliullin::BSTConstIterator< Key, Value >::operator*() const noexcept
{
  return node_->data_;
}

template< class Key, class Value >
const std::pair< const Key, Value >* haliullin::BSTConstIterator< Key, Value >::operator->() const noexcept
{
  return std::addressof(node_->data_);
}

template< class Key, class Value >
haliullin::BSTConstIterator< Key, Value >& haliullin::BSTConstIterator< Key, Value >::operator++() noexcept
{
  node_ = next(node_);
  return *this;
}

template< class Key, class Value >
haliullin::BSTConstIterator< Key, Value > haliullin::BSTConstIterator< Key, Value >::operator++(int) noexcept
{
  BSTConstIterator tmp(*this);
  ++(*this);
  return tmp;
}

template< class Key, class Value >
haliullin::BSTConstIterator< Key, Value >& haliullin::BSTConstIterator< Key, Value >::operator--() noexcept
{
  node_ = previous(node_);
  return *this;
}

template< class Key, class Value >
haliullin::BSTConstIterator< Key, Value > haliullin::BSTConstIterator< Key, Value >::operator--(int) noexcept
{
  BSTConstIterator tmp(*this);
  --(*this);
  return tmp;
}

template< class Key, class Value >
bool haliullin::BSTConstIterator< Key, Value >::operator==(const BSTConstIterator& other) const noexcept
{
  return node_ == other.node_;
}

template< class Key, class Value >
bool haliullin::BSTConstIterator< Key, Value >::operator!=(const BSTConstIterator& other) const noexcept
{
  return !(*this == other);
}

#endif
