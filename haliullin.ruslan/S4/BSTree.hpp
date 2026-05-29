#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>
#include <functional>
#include "TreeNode.hpp"
#include "tree-traverse.hpp"
#include "BSTree-iterators.hpp"

namespace haliullin
{
  template< class Key, class Value, class Compare = std::less< Key > >
  class BSTree
  {
  public:
    using Node = TreeNode< Key, Value >;
    using iterator = BSTIterator< Key, Value >;
    using const_iterator = BSTConstIterator< Key, Value >;

    ~BSTree();
    BSTree();

    BSTree(const BSTree& other);
    BSTree(BSTree&& other) noexcept;

    BSTree& operator=(const BSTree& other);
    BSTree& operator=(BSTree&& other) noexcept;
    void swap(BSTree& other) noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;

    void push(const Key& k, const Value& v);
    Value& get(const Key& k);
    const Value& get(const Key& k) const;
    iterator find(const Key& k);
    const_iterator find(const Key& k) const;
    void erase(const Key& k);
    void clear();

    size_t height(const_iterator it) const;
    size_t height() const;

    const_iterator rotateLeft(const_iterator it);
    const_iterator rotateRight(const_iterator it);
    const_iterator rotateLargeLeft(const_iterator it);
    const_iterator rotateLargeRight(const_iterator it);

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

  private:
    Node* root_;
    size_t size_;
    Compare cmp_;

    Node* findNode(const Key& k) const;
    Node* copyNodes(Node* node, Node* parent);
    size_t heightNode(const Node* node) const;
    void removeNode(Node* node);
    void clearNodes(Node* node);
  };
}

template< class Key, class Value, class Compare >
haliullin::BSTree< Key, Value, Compare >::~BSTree()
{
  clear();
}

template< class Key, class Value, class Compare >
haliullin::BSTree< Key, Value, Compare >::BSTree():
  root_(std::addressof(Node::fakeLeaf_)),
  size_(0)
{}

template< class Key, class Value, class Compare >
haliullin::BSTree< Key, Value, Compare >::BSTree(const BSTree& other):
  root_(copyNodes(other.root_, nullptr)),
  size_(other.size_),
  cmp_(other.cmp_)
{}

template< class Key, class Value, class Compare >
haliullin::BSTree< Key, Value, Compare >::BSTree(BSTree&& other) noexcept:
  BSTree()
{
  swap(other);
}

template< class Key, class Value, class Compare >
haliullin::BSTree< Key, Value, Compare >&
haliullin::BSTree< Key, Value, Compare >::operator=(const BSTree& other)
{
  if (this != std::addressof(other))
  {
    BSTree tmp(other);
    swap(tmp);
  }
  return *this;
}

template< class Key, class Value, class Compare >
haliullin::BSTree< Key, Value, Compare >&
haliullin::BSTree< Key, Value, Compare >::operator=(BSTree&& other) noexcept
{
  if (this != std::addressof(other))
  {
    BSTree tmp(std::move(other));
    swap(tmp);
  }
  return *this;
}

template< class Key, class Value, class Compare >
void haliullin::BSTree< Key, Value, Compare >::swap(BSTree& other) noexcept
{
  std::swap(root_, other.root_);
  std::swap(size_, other.size_);
  std::swap(cmp_, other.cmp_);
}

template< class Key, class Value, class Compare >
bool haliullin::BSTree< Key, Value, Compare >::isEmpty() const noexcept
{
  return root_->isFake();
}

template< class Key, class Value, class Compare >
size_t haliullin::BSTree< Key, Value, Compare >::getSize() const noexcept
{
  return size_;
}

template< class Key, class Value, class Compare >
void haliullin::BSTree< Key, Value, Compare >::push(const Key& k, const Value& v)
{
  if (root_->isFake())
  {
    root_ = new Node(k, v);
    ++size_;
    return;
  }

  Node* cur = root_;
  Node* parent = nullptr;

  while(!cur->isFake())
  {
    parent = cur;
    if (cmp_(k, cur->data_.first))
    {
      cur = cur->left_;
    }
    else if (cmp_(cur->data_.first, k))
    {
      cur = cur->right_;
    }
    else
    {
      Value temp(v);
      std::swap(cur->data_.second, temp);
      return;
    }
  }

  Node* newNode = new Node(k, v, parent);
  if (cmp_(k, parent->data_.first))
  {
    parent->left_ = newNode;
  }
  else
  {
    parent->right_ = newNode;
  }
  ++size_;
}

template< class Key, class Value, class Compare >
Value& haliullin::BSTree< Key, Value, Compare >::get(const Key& k)
{
  Node* node = findNode(k);
  if (node->isFake())
  {
    throw std::out_of_range("Key not found");
  }
  return node->data_.second;
}

template< class Key, class Value, class Compare >
const Value& haliullin::BSTree< Key, Value, Compare >::get(const Key& k) const
{
  Node* node = findNode(k);
  if (node->isFake())
  {
    throw std::out_of_range("Key not found");
  }
  return node->data_.second;
}

template< class Key, class Value, class Compare >
haliullin::BSTIterator< Key, Value > haliullin::BSTree< Key, Value, Compare >::find(const Key& k)
{
  return iterator(findNode(k));
}

template< class Key, class Value, class Compare >
haliullin::BSTConstIterator< Key, Value > haliullin::BSTree< Key, Value, Compare >::find(const Key& k) const
{
  return const_iterator(findNode(k));
}

template< class Key, class Value, class Compare >
void haliullin::BSTree< Key, Value, Compare >::erase(const Key& k)
{
  Node* node = findNode(k);
  if (node->isFake())
  {
    throw std::out_of_range("Key not found");
  }
  removeNode(node);
}

template< class Key, class Value, class Compare >
void haliullin::BSTree< Key, Value, Compare >::clear()
{
  clearNodes(root_);
  root_ = std::addressof(Node::fakeLeaf_);
  size_ = 0;
}

template< class Key, class Value, class Compare >
size_t haliullin::BSTree< Key, Value, Compare >::height(const_iterator it) const
{
  return heightNode(it.node_);
}

template< class Key, class Value, class Compare >
size_t haliullin::BSTree< Key, Value, Compare >::height() const
{
  return heightNode(root_);
}

template< class Key, class Value, class Compare >
haliullin::BSTConstIterator< Key, Value > haliullin::BSTree< Key, Value, Compare >::rotateLeft(const_iterator it)
{
  Node* cur = it.node_;
  if (!cur || cur->isFake())
  {
    throw std::logic_error("Invalid iterator");
  }
  Node* parent = cur->parent_;
  if (!parent || parent->isFake() || parent->right_ != cur)
  {
    throw std::logic_error("Cannot rotate left: node is not a right child");
  }

  Node* leftChild = cur->left_;
  Node* grand = parent->parent_;

  if (grand == nullptr)
  {
    root_ = cur;
  }
  else if (grand->left_ == parent)
  {
    grand->left_ = cur;
  }
  else
  {
    grand->right_ = cur;
  }
  cur->parent_ = grand;

  cur->left_ = parent;
  parent->parent_ = cur;

  parent->right_ = leftChild;
  if (!leftChild->isFake())
  {
    leftChild->parent_ = parent;
  }

  return const_iterator(leftChild);
}

template< class Key, class Value, class Compare >
haliullin::BSTConstIterator< Key, Value > haliullin::BSTree< Key, Value, Compare >::rotateRight(const_iterator it)
{
  Node* cur = it.node_;
  if (!cur || cur->isFake())
  {
    throw std::logic_error("Invalid iterator");
  }
  Node* parent = cur->parent_;
  if (!parent || parent->isFake() || parent->left_ != cur)
  {
    throw std::logic_error("Cannot rotate right: node is not a left child");
  }

  Node* rightChild = cur->right_;
  Node* grand = parent->parent_;

  if (grand == nullptr)
  {
    root_ = cur;
  }
  else if (grand->left_ == parent)
  {
    grand->left_ = cur;
  }
  else
  {
    grand->right_ = cur;
  }
  cur->parent_ = grand;

  cur->right_ = parent;
  parent->parent_ = cur;

  parent->left_ = rightChild;
  if (!rightChild->isFake())
  {
    rightChild->parent_ = parent;
  }

  return const_iterator(rightChild);
}

template< class Key, class Value, class Compare >
haliullin::BSTConstIterator< Key, Value >
haliullin::BSTree< Key, Value, Compare >::rotateLargeLeft(const_iterator it)
{
  Node* node = it.node_;
  if (!node || node->isFake())
  {
    throw std::logic_error("Invalid iterator");
  }
  Node* parent = node->parent_;
  if (!parent || parent->isFake() || parent->left_ != node)
  {
    throw std::logic_error("Cannot rotate large left: node must be left child of right child");
  }
  Node* grand = parent->parent_;
  if (!grand || grand->isFake() || grand->right_ != parent)
  {
    throw std::logic_error("Cannot rotate large left: parent must be right child");
  }

  Node* rightChild = node->right_;
  rotateRight(const_iterator(node));
  rotateLeft(const_iterator(node));
  return const_iterator(rightChild);
}

template< class Key, class Value, class Compare >
haliullin::BSTConstIterator< Key, Value >
haliullin::BSTree< Key, Value, Compare >::rotateLargeRight(const_iterator it)
{
  Node* node = it.node_;
  if (!node || node->isFake())
  {
    throw std::logic_error("Invalid iterator");
  }
  Node* parent = node->parent_;
  if (!parent || parent->isFake() || parent->right_ != node)
  {
    throw std::logic_error("Cannot rotate large right: node must be right child of left child");
  }
  Node* grand = parent->parent_;
  if (!grand || grand->isFake() || grand->left_ != parent)
  {
    throw std::logic_error("Cannot rotate large right: parent must be left child");
  }

  Node* leftChild = node->left_;
  rotateLeft(const_iterator(node));
  rotateRight(const_iterator(node));
  return const_iterator(leftChild);
}

template< class Key, class Value, class Compare >
haliullin::BSTIterator< Key, Value > haliullin::BSTree< Key, Value, Compare >::begin() noexcept
{
  if (root_->isFake())
  {
    return iterator(std::addressof(Node::fakeLeaf_));
  }
  return iterator(fallLeft(root_));
}

template< class Key, class Value, class Compare >
haliullin::BSTConstIterator< Key, Value > haliullin::BSTree< Key, Value, Compare >::begin() const noexcept
{
  if (root_->isFake())
  {
    return const_iterator(const_cast< Node* >(std::addressof(Node::fakeLeaf_)));
  }
  return const_iterator(fallLeft(root_));
}

template< class Key, class Value, class Compare >
haliullin::BSTConstIterator< Key, Value > haliullin::BSTree< Key, Value, Compare >::cbegin() const noexcept
{
  return begin();
}

template< class Key, class Value, class Compare >
haliullin::BSTIterator< Key, Value > haliullin::BSTree< Key, Value, Compare >::end() noexcept
{
  return iterator(std::addressof(Node::fakeLeaf_));
}

template< class Key, class Value, class Compare >
haliullin::BSTConstIterator< Key, Value > haliullin::BSTree< Key, Value, Compare >::end() const noexcept
{
  return const_iterator(std::addressof(Node::fakeLeaf_));
}

template< class Key, class Value, class Compare >
haliullin::BSTConstIterator< Key, Value > haliullin::BSTree< Key, Value, Compare >::cend() const noexcept
{
  return end();
}

template< class Key, class Value, class Compare >
haliullin::TreeNode< Key, Value >* haliullin::BSTree< Key, Value, Compare >::findNode(const Key& k) const
{
  Node* cur = root_;
  while (!cur->isFake())
  {
    if (cmp_(k, cur->data_.first))
    {
      cur = cur->left_;
    }
    else if (cmp_(cur->data_.first, k))
    {
      cur = cur->right_;
    }
    else
    {
      return cur;
    }
  }
  return std::addressof(Node::fakeLeaf_);
}

template< class Key, class Value, class Compare >
haliullin::TreeNode< Key, Value >* haliullin::BSTree< Key, Value, Compare >::copyNodes(Node* node, Node* parent)
{
  if (node->isFake())
  {
    return std::addressof(Node::fakeLeaf_);
  }
  Node* newNode = new Node(node->data_.first, node->data_.second, parent);
  try
  {
    newNode->left_ = copyNodes(node->left_, newNode);
    newNode->right_ = copyNodes(node->right_, newNode);
  }
  catch (...)
  {
    delete newNode;
    throw;
  }
  return newNode;
}

template< class Key, class Value, class Compare >
size_t haliullin::BSTree< Key, Value, Compare >::heightNode(const Node* node) const
{
  if (node->isFake())
  {
    return 0;
  }
  size_t leftH = heightNode(node->left_);
  size_t rightH = heightNode(node->right_);
  return 1 + (leftH > rightH ? leftH : rightH);
}

template< class Key, class Value, class Compare >
void haliullin::BSTree< Key, Value, Compare >::removeNode(Node* node)
{
  if (node->isFake()) return;

  if (node->left_->isFake() && node->right_->isFake())
  {
    if (node == root_)
    {
      root_ = std::addressof(Node::fakeLeaf_);
    }
    else if (node == node->parent_->left_)
    {
      node->parent_->left_ = std::addressof(Node::fakeLeaf_);
    }
    else
    {
      node->parent_->right_ = std::addressof(Node::fakeLeaf_);
    }
    delete node;
  }

  else if (node->left_->isFake() || node->right_->isFake())
  {
    Node* child = (node->right_->isFake() ? node->left_ : node->right_);
    child->parent_ = node->parent_;
    if (node == root_)
    {
      root_ = child;
    }
    else if (node == node->parent_->left_)
    {
      node->parent_->left_ = child;
    }
    else
    {
      node->parent_->right_ = child;
    }
    delete node;
  }

  else
  {
    Node* succ = fallLeft(node->right_);
    node->data_.second = succ->data_.second;
    const_cast< Key& >(node->data_.first) = succ->data_.first;

    if (succ == succ->parent_->left_)
    {
      succ->parent_->left_ = succ->right_;
    }
    else
    {
      succ->parent_->right_ = succ->right_;
    }

    if (!succ->right_->isFake())
    {
      succ->right_->parent_ = succ->parent_;
    }
    delete succ;
  }
  --size_;
}

template< class Key, class Value, class Compare >
void haliullin::BSTree< Key, Value, Compare >::clearNodes(Node* node)
{
  if (node->isFake()) return;
  clearNodes(node->left_);
  clearNodes(node->right_);
  delete node;
}

#endif
