#ifndef TREE_TRAVERSE_HPP
#define TREE_TRAVERSE_HPP

#include <memory>
#include "TreeNode.hpp"

namespace haliullin
{
  template< class Key, class Value >
  detail::TreeNode< Key, Value >* fallLeft(detail::TreeNode< Key, Value >* node) noexcept;

  template< class Key, class Value >
  detail::TreeNode< Key, Value >* fallRight(detail::TreeNode< Key, Value >* node) noexcept;

  template< class Key, class Value >
  detail::TreeNode< Key, Value >* next(detail::TreeNode< Key, Value >* node) noexcept;

  template< class Key, class Value >
  detail::TreeNode< Key, Value >* previous(detail::TreeNode< Key, Value >* node) noexcept;
}

template< class Key, class Value >
haliullin::detail::TreeNode< Key, Value >* haliullin::fallLeft(detail::TreeNode< Key, Value >* node) noexcept
{
  while (!node->left_->isFake())
  {
    node = node->left_;
  }
  return node;
}

template< class Key, class Value >
haliullin::detail::TreeNode< Key, Value >* haliullin::fallRight(detail::TreeNode< Key, Value >* node) noexcept
{
  while (!node->right_->isFake())
  {
    node = node->right_;
  }
  return node;
}

template< class Key, class Value >
haliullin::detail::TreeNode< Key, Value >* haliullin::next(detail::TreeNode< Key, Value >* node) noexcept
{
  if (!node->right_->isFake())
  {
    return fallLeft(node->right_);
  }

  detail::TreeNode< Key, Value >* parent = node->parent_;
  while (parent && (parent->right_ == node))
  {
    node = parent;
    parent = parent->parent_;
  }
  return parent ? parent : std::addressof(detail::TreeNode< Key, Value >::fakeLeaf_);
}

template< class Key, class Value >
haliullin::detail::TreeNode< Key, Value >* haliullin::previous(detail::TreeNode< Key, Value >* node) noexcept
{
  if (!node->left_->isFake())
  {
    return fallRight(node->left_);
  }

  detail::TreeNode< Key, Value >* parent = node->parent_;
  while (parent && (parent->left_ == node))
  {
    node = parent;
    parent = parent->parent_;
  }
  return parent ? parent : std::addressof(detail::TreeNode< Key, Value >::fakeLeaf_);
}

#endif
